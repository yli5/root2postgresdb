#include "PostgresConnector.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>


using namespace std;

int main(){
	PostgresConnector conn("darkphoton", "test");
	conn.regis();
	conn.insert("mcLen","3");
	conn.insert("mass", "0.4523");
	conn.insert("mclund", "{1, 2, 3}");
	conn.insert("mcd1mass", "{1.2, 3.4, 5.6}");
	conn.exec();
	return 0;
}
