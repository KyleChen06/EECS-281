// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#include <iostream>

#include "stock_market.hpp"

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  Market market(argc, argv);
  market.trade();

  return 0;
}