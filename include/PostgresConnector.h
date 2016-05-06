#ifndef POSTGRESCONNECTOR_H
#define POSTGRESCONNECTOR_H

#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>

class PostgresConnector{
public:
PostgresConnector() = default;
PostgresConnector(std::string db_name,
                  std::string table_name, 
                  std::vector<std::string> var_names);
~PostgresConnector();

//void regis();
//void insert(std::string column, std::string value);
void bind();
void exec();

private:
	//connector
	PGconn* conn_;
	char* pghost_ = nullptr;
	char* pgport_ = nullptr;
	char* pgoptions_ = nullptr;
	char* pgtty_ = nullptr;
	std::string db_name_;
	char* login_ = nullptr;
	char* pwd_ = nullptr;
	std::string table_name_;

	//command execution
	std::string command_column_;
	std::string command_value_;
	PGresult *res_;
	PGresult *stmt_name_;

  //variables
  std::vector<std::string> var_names_;
  size_t num_vars_;
  const char *param_values_;
};

#endif
