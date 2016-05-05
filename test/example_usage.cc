#include <TupleReader.h>
#include <ColumnConfigParser.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// This script demonstrates an example usage of the ColumnConfigParser
// and TupleReader classes. Copy to test_root2postgres.cc and run make
// to run this script.

int main() {

  string root_filename = "/home/jkim/raid13/ntp/sp11444r1/root/1.root";
  string root_treename = "ntp1";
  string column_config_fname = "column_config.csv";

  // Instantiate a ColumnConfigParser object from the 
  // column specification file. 
  ColumnConfigParser ccp = ColumnConfigParser(column_config_fname);

  // Instantiate a TupleReader object.
  TupleReader tr(ccp.GetVarTypes(), ccp.GetVarNames(), ccp.GetVarLengths(),
                 root_filename, root_treename);


  // Loop through every event in the ROOT file and for each event,
  // access the variables declared in the column config file and
  // print them. 
  // Note that accessing all variables of certain type can be
  // automated, for example (getting all integer variables):
  //
  // for (auto v : ccp.GetVarNames.at("int")) {
  //     int int_variable = tr.GetVarInt(v);
  // }
  
  size_t idx = 0; // Index for output formatting

  while (tr.next_record()) {
    if (idx % 100 == 0) {
      cout << "Event #" << idx;
      cout << " has mcLen = " << tr.GetVarInt("mcLen");
      cout << ", R2 = " << tr.GetVarFloat("R2");
      cout << "      The mcLund are :";
      for (const auto &m : tr.GetVarVectorInts("mcLund"))
        cout << m << " ";
      cout << endl;
      cout << "      The mcenergyCM are :";
      for (const auto &m : tr.GetVarVectorFloats("mcenergyCM"))
        cout << m << " ";
      cout << endl;
    }
    idx++;
  }

  return 0;
}
