#include <ColumnConfigParser.h>
#include <fstream>
#include <exception>
#include <set>
#include <utility>
#include <boost/algorithm/string.hpp>

using std::string;
using std::vector;

ColumnConfigParser::ColumnConfigParser(string column_spec_fname) {
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
    boost::split(contents, line, boost::is_any_of(" "));

    if (contents.size() != 2)
      throw std::domain_error("Column spec file does not contain "
                              "exactly 2 columns. ");
    var_name = contents[0];
    var_type = contents[1];
    auto opening_bracket_pos = var_type.find('[');
    auto closing_bracket_pos = var_type.find(']');

    if (opening_bracket_pos == string::npos &&
        closing_bracket_pos == string::npos) {
      var_types_set.insert(var_type);
      var_names_[var_type].push_back(var_name);
    } else if (opening_bracket_pos < var_type.size() &&
               closing_bracket_pos == var_type.size() - 1){
      string array_var_type = var_type.substr(0, opening_bracket_pos);
      string array_var_length = var_type.substr(opening_bracket_pos + 1,
                                                closing_bracket_pos - opening_bracket_pos - 1);
      var_type = array_var_type + "[]";
      var_types_set.insert(var_type);
      var_names_[var_type].push_back(var_name);
      var_lengths_.insert(std::make_pair(var_name, array_var_length));
    } else { 
      throw std::domain_error("Variable type must be one of: "
                              "int, float, int[], float[]. ");
    }
  }
  var_types_ = vector<string>(var_types_set.begin(), var_types_set.end());
}

ColumnConfigParser::~ColumnConfigParser() {}
