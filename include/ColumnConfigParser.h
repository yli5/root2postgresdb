// ConfigParser is a class that parses the column configuration
// file and stores the appropriate information (variables names,
// type, and length) to be passed on to the TupleReader class.
//
// Every ColumnConfigParser object must be instantiated using
// a column specification file (e.g. column_config.csv), which
// is a space-separated file with 2 columns:
//
// First column: Name of the variable, composed of alphanumeric
// character and underscore (_).  First character cannot be a
// number.
//
// Second column: Type of the variable.  Currently supports
// 4 types: int, float, int[], and float[].  The array variables
// are variable-length arrays, with their lengths determined by
// an integer variable that exists in the same spec file.
// 
// Example of column spec file (no comments allowed):
//
// mcLen         int
// R2            float
// mcLund        int[mcLen]
// mcenergyCM    float[mcLen]
// 
// Make sure that if you specify an array variable, its length
// is another variable within the same file!


#ifndef COLUMN_CONFIG_PARSER_H
#define COLUMN_CONFIG_PARSER_H

#include <string>
#include <map>
#include <vector>

class ColumnConfigParser {

  public:
    // Constructor takes in the column spec file as input.
    ColumnConfigParser(const std::string &column_spec_fname);
    ~ColumnConfigParser() { };

    // Accessors for the data members to be passed to TupleReader
    std::vector<std::string> GetVarTypes() const {
      return var_types_;
    }

    std::map<std::string, std::vector<std::string>> GetVarNames() const {
      return var_names_;
    }

    std::map<std::string, std::string> GetVarLengths() const {
      return var_lengths_;
    }

  private:
    std::vector<std::string> var_types_;
    std::map<std::string, std::vector<std::string>> var_names_;
    std::map<std::string, std::string> var_lengths_;
};
#endif
