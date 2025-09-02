// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "command_line.hpp"

#include <getopt.h>
using namespace std;

// Class for Mode CLI
enum class Mode
{
  kSwap,
  kChange,
  kLength
}; // Mode{}

// store all options from CLI
struct Options
{
  bool container = 0; // 0 == stack, 1 == queue
  vector<Mode> mode;  // holds a vector of the mods: if we have c or s, we require l
  bool output = 0;    // 0 == W, 1 == M; default to word
}; // Options{}

// Process the command line; there is no return value, but the Options
// struct is passed by reference and is modified by this function to send
// information back to the calling function.
void getOptions(int argc, char **argv, Options &options)
{
  // These are used with getopt_long()
  opterr = static_cast<int>(false); // Let us handle all error output for command line options
  int choice = 0;
  int index = 0;

  // NOLINTBEGIN: getopt predates C++ style, this usage is from `man getopt`
  option longOptions[] = {
      {"begin", required_argument, nullptr, 'b'},
      {"end", required_argument, nullptr, 'e'},
      {"stack", optional_argument, nullptr, 's'},
      {"queue", optional_argument, nullptr, 'q'},
      {"change", optional_argument, nullptr, 'c'},
      {"length", optional_argument, nullptr, 'l'},
      {"swap", optional_argument, nullptr, 'p'},
      {"output", optional_argument, nullptr, 'o'},
      {"help", no_argument, nullptr, 'h'},
      {nullptr, 0, nullptr, '\0'},
  }; // longOptions[]
  // NOLINTEND

  while ((choice = getopt_long(argc, argv, "o::m:b:e:h", static_cast<option *>(longOptions), &index)) != -1)
  {
    switch (choice)
    {
    case 'h':
      // printHelp(*argv);
      exit(0);

    case 'm':
    { // Need a block here to declare a variable inside a case
      string arg{optarg};
      if (arg != "resize" && arg != "reserve" && arg != "nosize")
      {
        // The first line of error output has to be a 'fixed' message
        // for the autograder to show it to you.
        cerr << "Error: invalid mode\n"
             << flush;
        // The second line can provide more information, but you
        // won't see it on the AG.
        cerr << "  I don't recognize: " << arg << '\n'
             << flush;
        exit(1);
      } // if ..arg valid

      if (arg == "reserve")
      {
        options.mode = Mode::kReserve;
      }
      else if (arg[0] == 'r')
      {
        options.mode = Mode::kResize;
      }
      else
      {
        options.mode = Mode::kNoSize;
      } // if ..arg
      break;
    } // case 'm'

    default:
      cerr << "Error: invalid option\n"
           << flush;
      exit(1);

    } // switch ..choice
  } // while

  if (options.mode == Mode::kNone)
  {
    cerr << "Error: no mode specified\n"
         << flush;
    exit(1);
  } // if ..mode
} // getOptions()

int main()
{
  return 0;
}