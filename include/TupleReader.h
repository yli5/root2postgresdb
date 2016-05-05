// TupleReader reads in a root file based on the configuration
// passed on by a ColumnConfigParser (CCP) object.
// It handles the memory allocation so that one can access the
// available variables through one of the 4 accessors.
//
// While the ColumnConfigParser class has its own exception handling,
// the TupleReader class performs its own checks to make sure
// the variables are valid.  Read more about the allowed types
// in the ColumnConfigParser header file.
//
// Suggested way to instantiate a TupleReader object is to directly
// call accessor functions of CCP: GetVarTypes(), GetVarNames(),
// and GetVarLengths(). (see example_usage.cc)

#ifndef TUPLE_READER_H
#define TUPLE_READER_H

#include <vector>
#include <string>
#include <map>

//ROOT Headers
#include <TDirectory.h>
#include <TFile.h>
#include <TTree.h>

class TupleReader {

  public:
    TupleReader(std::vector<std::string> var_types, 
                std::map<std::string, std::vector<std::string>> var_names,
                std::map<std::string, std::string> var_lengths,
                std::string root_filename,
                std::string root_treename);
    ~TupleReader();

    // next_record() is a wrapper of the TTree::GetEntry(i) function,
    // which populates the locations in the memory specified by the 
    // SetAddresses() function so that the variables can be retrieved
    // using the accessors.
    
    bool next_record();

    // Accessors for the variables, currently only 4 supported types.
    
    int GetVarInt(const std::string &var_name) const;
    float GetVarFloat(const std::string &var_name) const;
    std::vector<int> GetVarVectorInts(const std::string &var_name) const;
    std::vector<float> GetVarVectorFloats(const std::string &var_name) const;

  private:
    TFile *root_file_;
    TTree *root_tree_;

    std::vector<std::string> var_types_;
    std::map<std::string, std::vector<std::string>> var_names_;
    std::map<std::string, std::string> var_lengths_;

    std::map<std::string, int> var_values_int_;
    std::map<std::string, float> var_values_float_;
    std::map<std::string, std::vector<int>> var_values_vec_ints_;
    std::map<std::string, std::vector<float>> var_values_vec_floats_;

    int current_event_idx_ = 0;
    int num_events_ = 0;

    void SetAddresses();
    size_t get_array_length(const std::string &var_name) const;
};

#endif
