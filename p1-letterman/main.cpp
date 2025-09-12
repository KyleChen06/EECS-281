// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9

#include <iostream>

#include "letterman.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  std::ios_base::sync_with_stdio(false);

  // defines the object to call on, and initializes most of the variables
  Letterman letterman(argc, argv);
  letterman.morph();
  letterman.output();

  return 0;
}