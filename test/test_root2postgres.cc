#include <TupleReader.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int main() {
  string root_filename = "/home/jkim/raid13/ntp/sp11444r1/root/1.root";
  string root_treename = "ntp1";
  vector<string> var_types = {"int", "float", "int[]", "float[]"};
  map<string, vector<string>> var_names = {{"int", {"mcLen", "nY"}},
                                           {"float", {"eePx","beamSX"}},
                                           {"int[]", {"mcLund"}},
                                           {"float[]", {"mcmass"}}};
  map<string, string> var_lengths = {{"mcLund","mcLen"}, {"mcmass","mcLen"}};

  cout << "Instantiating a TupleReader object: ";
  TupleReader tr(var_types, var_names, var_lengths, root_filename, root_treename);
  cout << "Done. " << endl;

  size_t idx = 0;
  while (tr.next_record()) {
    if (idx % 100 == 0) {
      cout << "Event #" << idx;
      cout << " has mcLen = " << tr.GetVarInt(var_names["int"][0]);
      cout << ", nY = " << tr.GetVarInt(var_names["int"][1]);
      cout << ", eePx = " << tr.GetVarFloat(var_names["float"][0]);
      cout << ", and beamSX = " << tr.GetVarFloat(var_names["float"][1]) << endl;
      cout << "      The mcLund are :";
      for (const auto &m : tr.GetVarVectorInts(var_names["int[]"][0]))
        cout << m << " ";
      cout << endl;
      cout << "      The mcmass are :";
      for (const auto &m : tr.GetVarVectorFloats(var_names["float[]"][0]))
        cout << m << " ";
      cout << endl;
    }
    idx++;
  }

  return 0;
}
