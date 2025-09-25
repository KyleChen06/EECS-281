// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#include <algorithm>
#include <iostream>

#include "stock_market.hpp"

#include <getopt.h>
using namespace std;

// Process the command line; there is no return value, but the Options
// struct is passed by reference and is modified by this function to send
// information back to the calling function.
void Market::getOptions(int argc, char **argv) {
  // These are used with getopt_long()
  opterr = static_cast<int>(false); // Let us handle all error output for command line options
  int choice = 0;
  int index = 0;

  // NOLINTBEGIN: getopt predates C++ style, this usage is from `man getopt`
  option longOptions[] = {
      {"verbose", no_argument, nullptr, 's'},
      {"median", no_argument, nullptr, 'm'},
      {"trader_info", no_argument, nullptr, 'i'},
      {"time_travelers", no_argument, nullptr, 't'},
      {"help", no_argument, nullptr, 'h'},
      {nullptr, 0, nullptr, '\0'},
  }; // longOptions[]
  // NOLINTEND

  while ((choice = getopt_long(argc, argv, "vmith", static_cast<option *>(longOptions), &index)) != -1) {
    switch (choice) {
    case 'h':
      // printHelp(*argv);
      break;
    case 'v':
      v_out = true;
      break;
    case 'm':
      m_out = true;
      break;
    case 'i':
      i_out = true;
      break;
    case 't':
      t_out = true;
      break;
    default:
      cerr << "Unknown command line option" << endl;
      exit(1);

    } // switch ..choice
  } // while

  // error handling
  // none needed :D
} // getOptions()