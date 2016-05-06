#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>
#include "PostgresConnector.h"

using std::string;
using std::vector;

PostgresConnector::PostgresConnector(string db_name, 
                                     string table_name,
                                     vector<string> var_names){
	db_name_ = db_name;
	table_name_ = table_name;
	conn_ = PQsetdbLogin(pghost_, pgport_, pgoptions_, pgtty_, 
                       db_name_.c_str(), login_, pwd_);	
	//res_ = PQexec(conn_, command_column_.c_str());
	if (PQstatus(conn_) != CONNECTION_OK)
		throw PQerrorMessage(conn_);
  
  // Construct command to be passed preparing the statement 
  const char* stmtName = "PREPARE_DATA_FOR_INSERT";
  string stmt_command = "INSERT INTO" + table_name + " (";
  for (const auto &n : var_names) {
    stmt_command += n + ",";
  }
  stmt_command.pop_back();
  stmt_command += ") VALUES (";
  for (size_t i = 1; i <= var_names.size(); ++i) {
    stmt_command += "$" + std::to_string(i) + ",";
  }
  stmt_command.pop_back();
  stmt_command += ");";
  PGresult* stmt = PQprepare(conn_, stmtName, stmt_command.c_str(), 
                             var_names.size(), NULL);
  std::cout << PQresultErrorMessage(stmt) << " Test to use stmt. "
            << std::endl;
}

PostgresConnector::~PostgresConnector(){
	PQfinish(conn_);
	PQclear(res_);
}

void PostgresConnector::regis(){
	command_column_ = "INSERT INTO " + table_name_ + " (";
	command_value_ = " values (";
}

void PostgresConnector::insert(std::string column, std::string value){
	command_column_ += column + ",";
	command_value_ += value + ",";
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
