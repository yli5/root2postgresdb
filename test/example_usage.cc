#include "TupleReader.h"
#include "ColumnConfigParser.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "PostgresConnector.h"

using namespace std;

// This script demonstrates an example usage of the ColumnConfigParser
// and TupleReader classes.

int main() {

  string root_filename = "/home/jkim/raid13/ntp/sp11444r1/root/1.root";
  string root_treename = "ntp1";
  string column_config_fname = "column_config.csv";

  // Instantiate a ColumnConfigParser object from the 
  // column specification file. 
  ColumnConfigParser ccp = ColumnConfigParser(column_config_fname);

  // Instantiate a TupleReader object.
  TupleReader tr(root_filename, root_treename, ccp);

  //Instantiate a PostgresConnector object.
  PostgresConnector conn("testing", "mcevent", ccp.GetVarNames());

  // Loop through every event in the ROOT file and for each event,
  // access the variables declared in the column config file and
  // print them. 
  
  size_t idx = 0; // Index for output formatting

  // You can retrive all the variable names defined in the config
  // file through the ColumnConfigParser::GetVarNames() method.
  
  vector<string> v = ccp.GetVarNames();
  cout << endl << "Variable names are: ";
  for (const auto &n : v) {
    cout << n << " ";
  }
  cout << endl << endl;;

  while (tr.next_record()) {

    if (idx % 100 == 0) {
      cout << "Event #" << idx;
      cout << " has mcLen = " << tr.get("mcLen");
      cout << ", R2 = " << tr.get("R2");
      cout << endl;
      cout << "      The mcLund are :" << tr.get("mcLund");
      cout << endl;
      cout << "      The mcenergyCM are :" << tr.get("mcenergyCM");
      cout << endl;
      cout << endl;
    }

    conn.bind("mcLen", tr.get("mcLen"));
    conn.bind("R2", tr.get("R2"));
    conn.bind("mcLund",tr.get("mcLund"));
    conn.bind("mcenergyCM",tr.get("mcenergyCM"));
    conn.exec();

    idx++;
  }

  return 0;
}
