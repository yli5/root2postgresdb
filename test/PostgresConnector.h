#ifndef POSTGRESCONNECTOR_H
#define POSTGRESCONNECTOR_H

#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>

class PostgresConnector{
public:
PostgresConnector() = default;
PostgresConnector(std::string db_name, std::string table_name);
~PostgresConnector();

void regis();
void insert(std::string column, std::string value);
void exec();

private:
	//connector
	PGconn* conn_;
	char* pghost_ = NULL;
	char* pgport_ = NULL;
	char* pgoptions_ = NULL;
	char* pgtty_ = NULL;
	std::string db_name_;
	char* login_ = NULL;
	char* pwd_ = NULL;
	std::string table_name_;

	//command execution
	std::string command_column_;
	std::string command_value_;
	PGresult* res_;

};

#endif
