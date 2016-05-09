// The purpose of this class is to translate the column specification
// file into a format requested by the TupleReader class. You can read
// more about the format in TupleReader.cc.
//
// While this class checks for the correct format of the columns and 
// the consistency of array variable lengths, it does not check whether
// such variables exist in the ROOT file, it is handled by ROOT as
// described in TupleReader.cc. 

#include <ColumnConfigParser.h>
#include <fstream>
#include <exception>
#include <set>
#include <utility>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using std::string;
using std::vector;
using boost::regex;
using boost::smatch;
using boost::regex_search;
using boost::regex_match;

ColumnConfigParser::ColumnConfigParser(const string &column_spec_fname) {

  // Read in the column specification file
  std::ifstream fs(column_spec_fname);
  string line;

  if (!fs) {
    throw std::invalid_argument("Error in opening column_spec_fname. ");
  }

  std::set<string> var_types_set;
  vector<string> contents;
  string var_type;
  string var_name;

  while (std::getline(fs, line)) {

    // Tokenize each line and validiate the 2-column format
    boost::split(contents, line, boost::is_any_of(" \t"), boost::token_compress_on);
    if (contents.size() != 2)
      throw std::domain_error("Column spec file does not contain "
                              "exactly 2 columns. ");
    var_name = contents[0];
    var_type = contents[1];

    // Regex search patterns to determine name and type
    // Currently type can be one of {int, float, int[], float[]}
    const string name_pattern = "[[:alpha:]_][[:alnum:]_]*";
    const string type_scalar_pattern = "^(int|float)$";
    const string type_array_prefix_pattern = "^(int|float)";
    const string type_array_length_pattern = "\\[" + name_pattern + "\\]$";
    const string type_array_pattern = type_array_prefix_pattern + type_array_length_pattern;
   
    // Smatch objects to hold the regex search result
    smatch result_prefix, result_suffix, result_length;

    // Check if variable name is valid
    if (!regex_match(var_name, regex(name_pattern))) {
      throw std::domain_error("ColumnConfigParser error: invalid variable name. ");
    }

    // Check if variable type is valid
    if (regex_match(var_type, regex(type_scalar_pattern))) {
      // Scalar variable
      var_types_set.insert(var_type);
      var_names_[var_type].push_back(var_name);

    } else if (regex_match(var_type, regex(type_array_pattern))) {
      // Array variable
      // Determine whether it is a int[] or a float[]
      regex_search(var_type, result_prefix, regex(type_array_prefix_pattern));
      string array_var_type = result_prefix.str() + "[]";
      var_types_set.insert(array_var_type);
      var_names_[array_var_type].push_back(var_name);

      // Determine the variable corresponding to its length
      regex_search(var_type, result_suffix, regex(type_array_length_pattern));
      regex_search(result_suffix.str(), result_length, regex(name_pattern));
      var_lengths_.insert(std::make_pair(var_name, result_length.str()));

    } else {
      throw std::domain_error("ColumnConfigParser error: invalid variable type. ");
    }
  }

  // TupleReader expects var_types_ to be a vector
  var_types_ = vector<string>(var_types_set.begin(), var_types_set.end());

  // Check that lengths of array variables are valid
  vector<string> int_var_names = var_names_.at("int");
  bool is_valid_length;
  for (const auto p : var_lengths_) {
    is_valid_length = false;
    for (const auto v : int_var_names) {
      if (p.second == v) is_valid_length = true;
    }
    if (!is_valid_length) {
      throw std::domain_error("ColumnConfigParser error: invalid array length. ");
    }
  }
}

// Return a vector containing names of all variables
vector<string> ColumnConfigParser::GetVarNames() const {
  vector<string> var_names;
  for (const auto &t : var_types_) {
    var_names.insert(var_names.end(), var_names_.at(t).begin(), var_names_.at(t).end());
  }
  return var_names;
}








