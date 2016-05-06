#include <TupleReader.h>
#include <ColumnConfigParser.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int main() {
  string root_filename = "/home/jkim/raid13/ntp/sp11444r1/root/1.root";
  string root_treename = "ntp1";
  string column_config_fname = "column_config.csv";
  ColumnConfigParser ccp = ColumnConfigParser(column_config_fname);

  cout << "var_types: ";
  for (auto t : ccp.GetVarTypes()) cout << t << " ";
  cout << endl;
  cout << "var_names: ";
  for (auto p : ccp.GetVarNames()) {
    cout << p.first << ": ";
    for (auto v : p.second) cout << v << " ";
    cout << "; ";
  }
  cout << endl;
  cout << "var_lengths: ";
  for (auto p : ccp.GetVarLengths()) {
    cout << p.first << ", " << p.second << "; ";
  }
  cout << endl;

  cout << "Instantiating a TupleReader object: ";
  TupleReader tr(ccp.GetVarTypes(), ccp.GetVarNames(), ccp.GetVarLengths(),
                 root_filename, root_treename);
  cout << "Done. " << endl;

  size_t idx = 0;
  while (tr.next_record()) {
    if (idx % 100 == 0) {
      cout << "Event #" << idx;
      cout << " has mcLen = " << tr.GetVarInt("mcLen");
      cout << ", R2 = " << tr.GetVarFloat("R2");
      cout << endl;
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
