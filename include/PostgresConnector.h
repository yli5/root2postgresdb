// This class handles the connection and the insertion of records
// into the postgres database.
// It takes in as input the database name, table name, and
// the variables you want to insert into the table.
// It requires that the table already exists and columns 
// corresponding to var_names are available.
// Usually, one can use the ColumnConfigParser::GetVarNames()
// to get the vector of variables names.

#ifndef POSTGRESCONNECTOR_H
#define POSTGRESCONNECTOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <libpq-fe.h>

class PostgresConnector{

public:
  // Constructor opens the connection to the database and
  // creates the statement template.
  PostgresConnector(std::string db_name,
                    std::string table_name, 
                    std::vector<std::string> var_names);

  // The destructor closes the connection to the databse 
  // and deletes any dynamically allocated memory.
  ~PostgresConnector();

  // The bind function stores the value of the variable
  // in a vector.
  void bind(const std::string &var_name, const std::string &var_value);

  // The exec function performs the insertion of the 
  // variable values that were bound by the bind function
  // above.
  void exec();

private:
	//connector
	PGconn* conn_;
	char* pghost_ = nullptr;
	char* pgport_ = nullptr;
	char* pgoptions_ = nullptr;
	char* pgtty_ = nullptr;
	char* login_ = nullptr;
	char* pwd_ = nullptr;
	std::string db_name_;
	std::string table_name_;

	//command execution
	PGresult *res_;
  std::string stmt_name_;

  //variables
  std::unordered_map<std::string, size_t> var_name_to_idx_map_;
  size_t num_vars_;
  std::vector<std::string> param_values_vector_;
  std::vector<std::string>::iterator var_position_iter_;
  size_t var_idx_;
  const char **param_values_;
};

#endif
