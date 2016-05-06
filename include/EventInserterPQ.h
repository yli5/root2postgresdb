#ifndef EVENTINSERTERPQ_H
#define EVENTINSERTERPQ_H

#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>
//#include "Event.h"
//#include "Root2Event.h"
//#include "TupleReader.h"

class EventInserterPQ{
private:
	//connector
	PGconn* conn;
	char* pghost = NULL;
	char* pgport = NULL;
	char* pgoptions = NULL;
	char* pgtty = NULL;
	std::string db_name;
	char* login = NULL;
	char* pwd = NULL;

	//command execution
	std::string table_name;
	PGresult* res;
	std::map<std::string, std::vector<std::string> > val_name;
	
	void CreateTable();
	

public:
	EventInserterPQ() = default;
	EventInserterPQ(std::string db_name_, std::string table_name_, std::map<std::string, std::vector<std::string> > val_name_);
	~EventInserterPQ();

	void EventInserterPQ::insert();

};

template<typename T>
std::string to_string(std::vector<T> x);

#endif
