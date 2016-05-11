#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <algorithm>

#include <ColumnConfigParser.h>
#include <TupleReader.h>
#include <PostgresConnector.h>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void root2postgres(const po::variables_map &vm);

int main(int argc, char **argv) {

  try {

    // define program options 
    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration options");
    config.add_options()

        ("postgres_dbname", po::value<std::string>(), "Postgres database name. ")
        ("postgres_tblname", po::value<std::string>(), "Postgres table name. ")
        ("rows_per_insert", po::value<size_t>()->default_value(30), 
         "Number of rows per insertion statement ")

        ("cernroot_fname", po::value<std::string>(), "ROOT file name. ")
        ("cernroot_trname", po::value<std::string>()->default_value("ntp1"), "ROOT TTree name. ")

        ("column_spec_fname", po::value<std::string>(), "Column configuration file. ")

        ("run", po::value<std::string>(), "Run number (1-6) ")
        ("mode_label", po::value<std::string>(), "SP mode for MC, on/offpeak for data. ")
    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("config_file", po::value<std::string>(), "Job configuration file name. ")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config);

    po::options_description visible;
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("config_file", -1);

    // parse program options and configuration file
    po::variables_map vm;
    store(po::command_line_parser(argc, argv).
          options(cmdline_options).positional(p).run(), vm);
    notify(vm);

    if (vm.count("help") || !vm.count("config_file")) {
      std::cout << std::endl;
      std::cout << "Usage: root2postgres [options] config_fname" << std::endl;
      std::cout << visible << "\n";
      return 0;
    }

    std::ifstream fin(vm["config_file"].as<std::string>());
    if (!fin) {
      std::cout << "cannot open config file: ";
      std::cout << vm["config_file"].as<std::string>() << std::endl;
      return 0;
    }

    store(parse_config_file(fin, config_file_options), vm);
    notify(vm);

    // main routine
    root2postgres(vm);


  } catch(std::exception& e) {

    std::cerr << "error: " << e.what() << "\n";
    return 1;

  } catch(...) {

    std::cerr << "Exception of unknown type!\n";
    return 1;
  }


  return 0;
}


void root2postgres(const po::variables_map &vm) {

  // read configuration file parameters
  std::string postgres_dbname = vm["postgres_dbname"].as<std::string>();
  std::string postgres_tblname = vm["postgres_tblname"].as<std::string>();
  const size_t rows_per_insert = vm["rows_per_insert"].as<size_t>();
  std::string cernroot_fname = vm["cernroot_fname"].as<std::string>();
  std::string cernroot_trname = vm["cernroot_trname"].as<std::string>();
  std::string column_spec_fname = vm["column_spec_fname"].as<std::string>();
  std::string run = vm["run"].as<std::string>();
  std::string mode_label = vm["mode_label"].as<std::string>();

  // print
  //std::cout << postgres_dbname << std::endl;
  //std::cout << postgres_tblname << std::endl;
  //std::cout << cernroot_fname << std::endl;
  //std::cout << cernroot_trname << std::endl;

  // parse column configuration
  ColumnConfigParser ccp(column_spec_fname);
  std::vector<std::string> var_names = ccp.GetVarNames();
  std::vector<std::string> usr_var_names = {"run", 
                                            "mode_label"};

  // open root file
  TupleReader tuple_reader(cernroot_fname, cernroot_trname, ccp, 800);

  // open postgres connection
  std::vector<std::string> all_var_names = usr_var_names;
  all_var_names.insert(all_var_names.end(), var_names.begin(), var_names.end());
  PostgresConnector conn(postgres_dbname, postgres_tblname, all_var_names);

  // initialize vector to hold the rows to be inserted
  std::vector<std::string> record_values_vector;

  // stream over each event in the root file
  std::cout << "Inserting " << cernroot_fname << "..." << std::endl;
  unsigned int evt_idx = 0;
  while (tuple_reader.next_record()) {

    // Bind values of all variables in current record
    // and append to vector holding rows to be inserted
    for (const auto &v : var_names) {
      conn.bind(v, tuple_reader.get(v));
    }
    conn.bind("run", run);
    conn.bind("mode_label", mode_label);

    //// for each event, manually insert each column by name
    //conn.bind("mcLen", tuple_reader.get("mcLen"));
    //conn.bind("R2", tuple_reader.get("R2"));
    //conn.bind("mcLund", tuple_reader.get("mcLund"));
    //conn.bind("mcenergycm", tuple_reader.get("mcenergycm"));

    record_values_vector.push_back(conn.GetRowAsString());

    // Insert into database
    if (evt_idx % rows_per_insert == 0) {
      conn.insert(record_values_vector);
      record_values_vector.clear();
    }
    ++evt_idx;
  }

  // Insert any remaining rows
  if (!record_values_vector.empty()) conn.insert(record_values_vector);

  return;

}
