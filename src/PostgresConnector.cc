#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>
#include "PostgresConnector.h"

using std::string;
using std::vector;

static void 
exit_nicely(PGconn *conn) {
  PQfinish(conn);
  exit(EXIT_FAILURE);
}

PostgresConnector::PostgresConnector(string db_name, 
                                     string table_name,
                                     vector<string> var_names)
    : var_names_(var_names), 
      num_vars_(var_names.size()),
      param_values_(new const char*[var_names.size()]("DEFAULT")) {

  // Initialize and open connection to the databse
	db_name_ = db_name;
	table_name_ = table_name;
	conn_ = PQsetdbLogin(pghost_, pgport_, pgoptions_, pgtty_, 
                       db_name_.c_str(), login_, pwd_);	
  if (PQstatus(conn_) != CONNECTION_OK) {
    cerr << "Connection to database failed: " << PQerrorMessage(conn_);
    exit_nicely(conn_);
  }
  
  // Construct command to be passed preparing the statement 
  const char* stmt_name_ = "PREPARE_DATA_FOR_INSERT";
  string stmt_command = "INSERT INTO" + table_name + " (";
  for (const auto &n : var_names_) {
    stmt_command += n + ",";
  }
  stmt_command.pop_back();
  stmt_command += ") VALUES (";
  for (size_t i = 1; i <= num_vars_; ++i) {
    stmt_command += "$" + std::to_string(i) + ",";
  }
  stmt_command.pop_back();
  stmt_command += ");";

  // Prepare the statement
  res_ = PQprepare(conn_, stmt_name_, stmt_command.c_str(), 
                   num_vars_, nullptr);
  if (PQresultStatus(res_) != PGRES_COMMAND_OK) {
    cerr << "Prepare failed: " << PQerrorMessage(res_);
    PQclear(res_);
    exit_nicely(conn_);
  }
}

PostgresConnector::~PostgresConnector(){
	PQfinish(conn_);
	PQclear(res_);
}

//void PostgresConnector::regis(){
//	command_column_ = "INSERT INTO " + table_name_ + " (";
//	command_value_ = " values (";
//}

//void PostgresConnector::insert(std::string column, std::string value){
//	command_column_ += column + ",";
//	command_value_ += value + ",";
//}

void PostgresConnector::bind() {
  const char *param_values[num_vars_];
  for (const auto &v : var_names_) {
  }
}

void PostgresConnector::exec(){
	std::string command_exec_;
	command_column_.pop_back();
	command_value_.pop_back();
	command_column_ += ")";
	command_value_ += ");";
	command_exec_ = command_column_ + command_value_;
	res_ = PQexec(conn_, command_exec_.c_str());
	command_column_.clear();
	command_value_.clear();
	if(PQresultStatus(res_) != PGRES_COMMAND_OK)
		throw PQresultErrorMessage(res_);
}
