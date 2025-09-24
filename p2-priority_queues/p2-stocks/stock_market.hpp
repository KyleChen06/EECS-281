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
    size_t inventory;
    size_t price;
    size_t priority;

    // TODO: make a functor for comparisons
    bool operator<(const Trader &other) const
    {
      if (this->time == other.time)
        return this->priority > other.priority;
      else
        return this->time > other.time;
    }
  };

  struct Stock // will have multiple different types
  {
    std::priority_queue<Trader> buyers;
    std::priority_queue<Trader> sellers;
  };

  size_t num_traders;
  size_t num_stocks;
  std::vector<Stock> stocks; // .resize based on input, vector index will be stock #
  size_t current_timestamp = 0;

  // PR MODE pvs
  size_t seed, num_orders, arr_rate;

  // reads options from x and reads them all into pv's
  void getOptions(int argc, char **argv);

  // read in the traders
  void readInput();

  void processInput(std::istream &inputStream);
};

#endif