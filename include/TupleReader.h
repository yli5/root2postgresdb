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
#include <sstream>

//ROOT headers
#include <TDirectory.h>
#include <TFile.h>
#include <TTree.h>

// Custom class headers
#include "ColumnConfigParser.h"

class TupleReader {

  public:
    TupleReader(const std::string &root_filename,
                const std::string &root_treename,
                const ColumnConfigParser &ccp,
                const size_t MaxArraySize);
    ~TupleReader();

    // next_record() is a wrapper of the TTree::GetEntry(i) function,
    // which populates the locations in the memory specified by the 
    // SetAddresses() function so that the variables can be retrieved
    // using the accessors.
    
    bool next_record();

    // get() is a public accessor for variable values; 
    // it returns the value as a string for all 4 data types.
    //
    // Example: int - "4", float - "3.1392300000",
    //          int[] - "{3,2,1}",
    //          float[] - "{3.2148290000, 0.2143900000}"
    //
    std::string get(const std::string &var_name) const;

  private:
    // For more information about private section, see
    // TupleReader.cc
    TFile *root_file_;
    TTree *root_tree_;
    const size_t kMaxArraySize;

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

    mutable std::stringstream ss_;
    
    std::string GetVarInt(const std::string &var_name) const;
    std::string GetVarFloat(const std::string &var_name) const;
    std::string GetVarVectorInts(const std::string &var_name) const;
    std::string GetVarVectorFloats(const std::string &var_name) const;
    size_t get_array_length(const std::string &var_name) const;
};

#endif
