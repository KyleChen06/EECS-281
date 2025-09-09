// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9

#include <iostream>

#include "letterman.hpp"
#include "command_line.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  std::ios_base::sync_with_stdio(false);

  Options options;
  getOptions(argc, argv, options);

  // defines the object to call on, and initializes most of the variables
  Letterman letterman(options.begin, options.end, options.container, options.output);
  letterman.morph(options.change, options.swap, options.length);
  letterman.output();

  return 0;
}