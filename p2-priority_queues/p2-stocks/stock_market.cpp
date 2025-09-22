// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#include <iostream>
#include <vector>
#include <algorithm>

#include "stock_market.hpp"

using namespace std;

Market::Market(int argc, char **argv)
{
  getOptions(argc, argv);
  readInput();
}
