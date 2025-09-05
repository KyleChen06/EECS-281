// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9

#include <iostream>

#include "letterman.hpp"
#include "command_line.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  Options options;
  getOptions(argc, argv, options);

  // defines the object to call on, and initializes most of the variables
  Letterman letterman(options.begin, options.end);
  letterman.output();

  // cerr if

  return 0;
}