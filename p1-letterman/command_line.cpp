// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#include <algorithm>
#include <iomanip>
#include <iostream>

#include "command_line.hpp"

#include <getopt.h>
using namespace std;

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

  while ((choice = getopt_long(argc, argv, "o::b:e:hsqclp", static_cast<option *>(longOptions), &index)) != -1)
  {
    switch (choice)
    {
    case 'h':
      // printHelp(*argv);
      exit(0);
    case 'c':
      options.change = 1;
      break;
    case 'p':
      options.swap = 1;
      break;
    case 'l':
      options.length = 1;
      break;
    case 's':
      if (options.container == 0 || options.container == 1)
      {
        cerr << "Conflicting or duplicate stack and queue specified" << endl;
        exit(1);
      }
      options.container = 0;
      break;
    case 'q':
      if (options.container == 0 || options.container == 1)
      {
        cerr << "Conflicting or duplicate stack and queue specified" << endl;
        exit(1);
      }
      options.container = 1;
      break;
    case 'e':
      options.end = optarg;
      break;
    case 'b':
      options.begin = optarg;
      break;
    case 'o':
      if (optarg)
      {
        if (optarg == "M")
          options.output = 1;
        else if (optarg == "W")
          options.output = 0;
        else
          cerr << "Invalid output mode specified" << endl;
        exit(1);
      }
      break;
    default:
      cerr << "Unknown command line option\n"
           << flush;
      exit(1);

    } // switch ..choice
  } // while

  // error handling
  if (options.container != 0 && options.container != 1)
  {
    cerr << "Must specify one of stack or queue" << endl;
    exit(1);
  } // if ..container

  if (options.change == 0 && options.length == 0 && options.swap == 0)
  {
    cerr << "Must specify at least one modification mode (change length swap)" << endl;
    exit(1);
  } // if ..mode

  if (options.begin == "")
  {
    cerr << "Beginning word not specified" << endl;
    exit(1);
  } // if ..begin

  if (options.end == "")
  {
    cerr << "Ending word not specified" << endl;
    exit(1);
  } // if ..end

  if (!options.length && options.begin.length() != options.end.length())
  {
    cerr << "The first and last words must have the same length when length mode is off" << endl;
    exit(1);
  } // if ..length
} // getOptions()