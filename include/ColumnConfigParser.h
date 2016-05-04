// ConfigParser is a class that parses the column configuration
// file and stores the appropriate information (variables names,
// type, and length).
// It is meant to be used to instantiate the TupleReader object.

#ifndef COLUMN_CONFIG_PARSER_H
#define COLUMN_CONFIG_PARSER_H

#include <string>
#include <map>
#include <vector>

class ColumnConfigParser {
  public:
    ColumnConfigParser(std::string column_spec_fname);
    ~ColumnConfigParser();

    inline std::vector<std::string> GetVarTypes() const {
      return var_types_;
    }

    inline std::map<std::string, std::vector<std::string>> GetVarNames() const {
      return var_names_;
    }

    inline std::map<std::string, std::string> GetVarLengths() const {
      return var_lengths_;
    }

  private:
    std::vector<std::string> var_types_;
    std::map<std::string, std::vector<std::string>> var_names_;
    std::map<std::string, std::string> var_lengths_;
};
#endif
