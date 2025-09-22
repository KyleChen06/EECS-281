// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#ifndef STOCK_MARKET_HPP
#define STOCK_MARKET_HPP

#include <vector>
#include <iostream>
#include <queue>

class Market
{
public:
  // constructor
  Market(int argc, char **argv);

  // traders do their trades
  void Trade();

private:
  bool inputMode = 0; // 0 = TL, 1 = PR
  bool v_out = 0;     // verbose
  bool m_out = 0;     // median
  bool i_out = 0;     // trader info
  bool t_out = 0;     // time traveller

  struct Trader
  {
    size_t time;
    size_t id;
    size_t num_stocks;
    size_t price;
    size_t priority;

    // TODO: make a functor for comparisons
  };

  struct Stock // will have multiple different types
  {
    size_t stock_num;
    std::priority_queue<Trader> buyers;
    std::priority_queue<Trader> sellers;
  };

  std::vector<Stock> stocks; // .reserve based on input

  size_t current_timestamp = 0;

  // reads options from x and reads them all into pv's
  void getOptions(int argc, char **argv);

  // read in the traders
  void readInput();
};

#endif