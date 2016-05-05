// The TupleReader class contains data members that store three attributes
// of each variable: its name, type, and length (if it is an array type).
//
// The purpose of the class is to load the variables specified by
// the ColumnConfigParser class into the memory so that the PostgresConnector
// can insert them into the database one row at a time.
//
// The following briefly describes how the data members are orgainzed:
//
// var_types_: A vector summarizing the valid data types present 
// in the config file.  Valid types are: int, float, int[], and float[].
// Example: {"int", "float[]"}
//
// var_names_: A map that associates each types in var_types_ with a vector
// containing the names of variables of that type.
// Example: {{"int", {"mcLen", "nY"}}, {"float[]", {"mcenergyCM"}}} 
//
// var_lengths_: A map that associates an array variable (int or float) with
// the integer variable representing its length.  The latter must be specified
// in the config file.
// Example: {{"mcenergyCM", "mcLen"}}

#include <iostream>
#include <utility>
#include <exception>
#include "TupleReader.h"

//ROOT Headers
#include <TBranch.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::make_pair;

// Constructor definition

TupleReader::TupleReader(vector<string> var_types,
                         map<string, vector<string>> var_names, 
                         map<string, string> var_lengths, 
                         string root_filename,
                         string root_treename)
    : var_types_(var_types), var_names_(var_names), var_lengths_(var_lengths) {
  root_file_ = new TFile(root_filename.c_str());
  root_tree_ = (TTree*) root_file_->Get(root_treename.c_str());
  current_event_idx_ = 0;
  num_events_ = root_tree_->GetEntries();
  SetAddresses();
}

// Destructor definition

TupleReader::~TupleReader() {
  root_file_->Close();
  delete root_file_;
}

// SetAddresses() performs type checking of the variable and allocates
// memory for the variable.  Then, it associates that location with
// a branch in the ROOT file through TBranch::SetBranchAddress.
// If no such branch exists, SetBranchAddress will return
// TTree::ESetBranchAddressStatus::kMissingBranch.

void TupleReader::SetAddresses() {
  for (auto t : var_types_) {
    if (t != "int" && t != "float" && t != "int[]" && t != "float[]")
      throw std::invalid_argument("SetAddresses error: "
                                  "var_types Must be one of" 
                                  "int, float, int[], or float[].");

    for (auto v : var_names_[t]) {
      if (t == "int") {
        var_values_int_.insert(make_pair(v, 0));
        if (root_tree_->SetBranchAddress(v.c_str(), &var_values_int_[v])
            == TTree::ESetBranchAddressStatus::kMissingBranch) {
          throw std::invalid_argument("TupleReader error: no corresponding "
                                   "branch in the ROOT file. ");
        }
      } else if (t == "float") {
        var_values_float_.insert(make_pair(v, 0.));
        if (root_tree_->SetBranchAddress(v.c_str(), &var_values_float_[v])
            == TTree::ESetBranchAddressStatus::kMissingBranch) {
          throw std::invalid_argument("TupleReader error: no corresponding "
                                   "branch in the ROOT file. ");
        }
      } else if (t == "int[]") {
        var_values_vec_ints_.insert(make_pair(v, vector<int>(500)));
        if (root_tree_->SetBranchAddress(v.c_str(), &var_values_vec_ints_[v][0])
            == TTree::ESetBranchAddressStatus::kMissingBranch) {
          throw std::invalid_argument("TupleReader error: no corresponding "
                                   "branch in the ROOT file. ");
        }
      } else if (t == "float[]") {
        var_values_vec_floats_.insert(make_pair(v, vector<float>(500)));
        if (root_tree_->SetBranchAddress(v.c_str(), &var_values_vec_floats_[v][0])
            == TTree::ESetBranchAddressStatus::kMissingBranch) {
          throw std::invalid_argument("TupleReader error: no corresponding "
                                   "branch in the ROOT file. ");
        }
      } 
    }
  }
}

// next_record() populates the specified locations in the memory with the 
// appropriate values from the ROOT file. It starts from the first row and
// returns true until EOF. 

bool TupleReader::next_record() {
  if (current_event_idx_ < num_events_) {
    if (root_tree_->GetEntry(current_event_idx_) > 0) {
      ++current_event_idx_;
      return true;
    } else
      throw std::out_of_range("GetEntry error: either entry doesn't exist or"
                              "I/O error.");
  }
  return false;
}


// Accessors and their helper function, which performs checks to make sure that
// the variable being accessed exists and is of the right type.

int TupleReader::GetVarInt(const string &var_name) const {
  if (var_values_int_.count(var_name) == 0)
    throw std::domain_error("GetVarInt error: "
                            "No such variable, only those in var_names are allowed.");
  return var_values_int_.at(var_name);
}

float TupleReader::GetVarFloat(const string &var_name) const {
  if (var_values_float_.count(var_name) == 0)
    throw std::domain_error("GetVarFloat error: "
                            "No such variable, only those in var_names are allowed.");
  return var_values_float_.at(var_name);
}

vector<int> TupleReader::GetVarVectorInts(const string &var_name) const {
  if (var_values_vec_ints_.count(var_name) == 0)
    throw std::domain_error("GetVarVectorInts error: "
                            "No such variable, only those in var_names are allowed.");
  vector<int> var_vector = var_values_vec_ints_.at(var_name);
  var_vector.resize(get_array_length(var_name));
  return var_vector;
}

vector<float> TupleReader::GetVarVectorFloats(const string &var_name) const {
  if (var_values_vec_floats_.count(var_name) == 0)
    throw std::domain_error("GetVarVectorFloats error: "
                            "No such variable, only those in var_names are allowed.");
  vector<float> var_vector = var_values_vec_floats_.at(var_name);
  var_vector.resize(get_array_length(var_name));
  return var_vector;
}

size_t TupleReader::get_array_length(const string &var_name) const {
  if (var_lengths_.count(var_name) == 0)
    throw std::domain_error("get_array_length error: "
                            "No such array variable, it must exist in var_lengths.");
  int var_length = GetVarInt(var_lengths_.at(var_name));
  if (var_length < 0)
    throw std::length_error("get_array_length error: "
                            "The variable has negative length.");
  return (size_t) var_length; 
}
