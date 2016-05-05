#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>

//#include "Event.h"
#include "EventInserterPQ.h"

using std::string;

EventInserterPQ::EventInserterPQ(std::string db_name_, std::string table_name_, std::map<std::string, std::vector<std::string> > val_name_){
	db_name = db_name_;
	table_name = table_name_;
	val_name = val_name_;
}

EventInserterPQ::~EventInserterPQ(){
	// delete pointers
	PQfinish(conn);
	PQclear(res);
}

void EventInserterPQ::CreateTable(){
	//if db_name not exist, create it; else do nothing
	conn = PQsetdbLogin(pghost, pgport, pgoptions, pgtty, db_name.c_str(), login, pwd);
	if(PQstatus(conn) != CONNECTION_OK)
		throw PQerrorMessage(conn);
	else{
		if(val_name.empty())
			throw std::invalid_argument("Value_size error: val_name cannot be empty");
		else{
			std::string command("CREATE TABLE IF NOT EXISTS ");
			command += table_name + "(";
			for(auto const& i : val_name){
				for(size_t j = 0; j < i.second.size(); ++j){
					command += i.second[j] + " " + i.first + ",";
				}
			}
			command.pop_back();
			command += ");";
			res = PQexec(conn, command.c_str());
			if(PQresultStatus(res) != PGRES_COMMAND_OK)
				throw PQresultErrorMessage(res);
		}
	}
	return;
}

void EventInserterPQ::insert(){
	CreateTable();
	//Define TupleReader class here:
	std::string command("INSERT INTO ");
			command += table_name + " VALUES (";
			for(auto const& i : val_name){
				for(size_t j = 0; j < i.second.size(); ++j){
					command += to_string(tuplereader.get(i.second[j])) + ",";
				}
			}
			command.pop_back();
			command += ");";
			res = PQexec(conn, command.c_str());
			if(PQresultStatus(res) != PGRES_COMMAND_OK)
				throw PQresultErrorMessage(res);
}

template<typename T>
std::string to_string(std::vector<T> x){
	std::string resultstring("'{");
	if(x.size() == 0) return resultstring + "}'";
	for(size_t i = 0; i < x.size(); ++i){
		resultstring += to_string(x[i]) + ",";
	}
	resultstring.pop_back();
	resultstring += "}'";
	return resultstring;
}

/*
std::string to_string(std::vector<int> x){
	std::string resultstring;
	if(x.size() == 0) return resultstring + "{}";
	resultstring = "{" + std::to_string(x[0]);
	if(x.size() == 1) return resultstring + "}";

	for(unsigned int i = 1; i < x.size(); ++i){
		resultstring += "," + std::to_string(x[i]);
	}
	resultstring += "}";
	return resultstring;
}

std::string to_string(std::vector<float> x){
	std::string resultstring;
	if(x.size() == 0) return resultstring + "{}";
	resultstring = "{" + std::to_string(x[0]);
	if(x.size() == 1) return resultstring + "}";

	for(unsigned int i = 1; i < x.size(); ++i){
		resultstring += "," + std::to_string(x[i]);
	}
	resultstring += "}";
	return resultstring;
}
*/








