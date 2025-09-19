// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#include <algorithm>
#include <iostream>

#include "letterman.hpp"

#include <getopt.h>
using namespace std;

// Process the command line; there is no return value, but the Options
// struct is passed by reference and is modified by this function to send
// information back to the calling function.
void Letterman::getOptions(int argc, char **argv)
{
  // These are used with getopt_long()
  opterr = static_cast<int>(false); // Let us handle all error output for command line options
  int choice = 0;
  int index = 0;

  // NOLINTBEGIN: getopt predates C++ style, this usage is from `man getopt`
  option longOptions[] = {
      {"begin", required_argument, nullptr, 'b'},
      {"end", required_argument, nullptr, 'e'},
      {"stack", no_argument, nullptr, 's'},
      {"queue", no_argument, nullptr, 'q'},
      {"change", no_argument, nullptr, 'c'},
      {"length", no_argument, nullptr, 'l'},
      {"swap", no_argument, nullptr, 'p'},
      {"output", required_argument, nullptr, 'o'},
      {"help", no_argument, nullptr, 'h'},
      {nullptr, 0, nullptr, '\0'},
  }; // longOptions[]
  // NOLINTEND

  while ((choice = getopt_long(argc, argv, "o:b:e:hsqclp", static_cast<option *>(longOptions), &index)) != -1)
  {
    switch (choice)
    {
    case 'h':
      // printHelp(*argv);
      break;
    case 'c':
      c = 1;
      break;
    case 'p':
      p = 1;
      break;
    case 'l':
      l = 1;
      break;
    case 's':
      if (queue)
      {
        cerr << "Conflicting or duplicate stack and queue specified" << endl;
        exit(1);
      }
      stack = 1;
      stack_or_queue = false;
      break;
    case 'q':
      if (stack)
      {
        cerr << "Conflicting or duplicate stack and queue specified" << endl;
        exit(1);
      }
      queue = 1;
      stack_or_queue = true;
      break;
    case 'e':
      end_word = string(optarg);
      break;
    case 'b':
      begin_word = string(optarg);
      current = begin_word;
      break;
    case 'o':
      if (optarg)
      {
        if (string(optarg) == "M")
        {
          output_version = 1;
        }
        else if (string(optarg) == "W")
        {
          output_version = 0;
        }
        else
        {
          cerr << "Invalid output mode specified" << endl;
          exit(1);
        }
      }
      break;
    default:
      cerr << "Unknown command line option" << endl;
      exit(1);

    } // switch ..choice
  } // while

  // error handling
  if (stack == 0 && queue == 0)
  {
    cerr << "Must specify one of stack or queue" << endl;
    exit(1);
  } // if ..container

  if (c == 0 && l == 0 && p == 0)
  {
    cerr << "Must specify at least one modification mode (change length swap)" << endl;
    exit(1);
  } // if ..mode

  if (begin_word.empty())
  {
    cerr << "Beginning word not specified" << endl;
    exit(1);
  } // if ..begin

  if (end_word.empty())
  {
    cerr << "Ending word not specified" << endl;
    exit(1);
  } // if ..end

  // length is not on and begin/end aren't same length
  if (!l && begin_word.length() != end_word.length())
  {
    cerr << "The first and last words must have the same length when length mode is off" << endl;
    exit(1);
  } // if ..length
} // getOptions()