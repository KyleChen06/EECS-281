// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#ifndef STOCK_MARKET_HPP
#define STOCK_MARKET_HPP

#include <vector>
#include <iostream>
#include <queue>

class Market {
public:
  // constructor
  Market(int argc, char **argv);

  // traders do their trades
  void trade();

private:
  bool inputMode = 0; // 0 = TL, 1 = PR
  bool v_out = 0;     // verbose
  bool m_out = 0;     // median
  bool i_out = 0;     // trader info
  bool t_out = 0;     // time traveller

  struct Trader {
    size_t time;
    size_t priority;
    bool intent; // false == sell, true == buy
    size_t id;
    size_t stock;
    size_t inventory;
    size_t price;
  };

  // keep track of information for trader info
  struct Trader_Info {
    size_t bought = 0;
    size_t sold = 0;
    int net = 0;
  };

  // we want highest price first because sellers want to sell at highest price
  struct BuyerComp {
    bool operator()(const Trader &left, const Trader &right) const {
      if (left.price == right.price) {
        if (left.time == right.time)
          return left.priority > right.priority;
        else
          return left.time > right.time;
      } else
        return left.price < right.price;
    }
  };

  // we want lowest price first because buyers want to buy at lowest price
  struct SellerComp {
    bool operator()(const Trader &left, const Trader &right) const {
      if (left.price == right.price) {
        if (left.time == right.time)
          return left.priority > right.priority;
        else
          return left.time > right.time;
      } else
        return left.price > right.price;
    }
  };

  // different stocks hold different information
  struct Stock {
    std::priority_queue<Trader, std::vector<Trader>, BuyerComp> buyers;
    std::priority_queue<Trader, std::vector<Trader>, SellerComp> sellers;
    size_t num_traded = 0;
    size_t selling = 0;
    size_t buying = 0;
    // time traveler info
    size_t price1;
    size_t price2;
    size_t timestamp1 = 0;
    size_t timestamp2 = 0;
    // median info
    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> right;
    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> left;
  };

  size_t num_traders;
  size_t num_stocks;
  std::vector<Stock> stocks; // .resize based on input, vector index will be stock #
  std::queue<Trader> waiting;
  std::vector<Trader_Info> trader_info;
  size_t current_timestamp = 0;
  size_t completed_trades = 0;

  // PR MODE pvs
  size_t seed, num_orders, arr_rate;

  // reads options from x and reads them all into pv's
  void getOptions(int argc, char **argv);

  // read in the traders
  void readInput();

  void processInput(std::istream &inputStream);

  // outputs
  void trader_info_output();
  void time_traveler_output();

  // trade() helpers
  void process_trade(Stock &stock, size_t stock_id);
};

#endif