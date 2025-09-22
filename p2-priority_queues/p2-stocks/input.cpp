// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#include <iostream>
#include <sstream>

#include "stock_market.hpp"
#include "P2random.h"

using namespace std;

void Market::readInput()
{
  string temp;
  getline(cin, temp); // remove comment line

  cin >> temp >> temp;     // get mode;
  if (temp.front() == 'P') // default on TL mode
    inputMode = 1;

  cin >> temp >> temp; // get number of traders
  num_traders = static_cast<size_t>(stoi(temp));

  cin >> temp >> temp; // get number of stocks
  num_stocks = static_cast<size_t>(stoi(temp));
  stocks.reserve(num_stocks);

  // use helper functions to read in rest based on inputMode
  if (inputMode = 0)
    processOrders(cin);
  else
  {
    stringstream ss;

    cin >> temp >> temp;
    seed = static_cast<size_t>(stoi(temp));

    cin >> temp >> temp;
    num_orders = static_cast<size_t>(stoi(temp));

    cin >> temp >> temp;
    arr_rate = static_cast<size_t>(stoi(temp));

    P2random::PR_init(ss, seed, num_traders, num_stocks, num_orders, arr_rate);
    processOrders(ss);
  }
}

void Market::processOrders(istream &inputStream)
{
  string time_stamp;
  string intent;
  string trader_id;
  string stock_id;
  string cost;
  string inventory;

  while (inputStream >> time_stamp >> intent >> trader_id >> stock_id >> cost >> inventory)
  {
    size_t stock_num = static_cast<size_t>(stoi(stock_id.substr(1)));
    size_t priority = (intent.front() == 'B') ? stocks[stock_num].buyers.size() : stocks[stock_num].sellers.size();
    bool buy = (intent.front() == 'B') ? true : false;

    // create trader object to place into Market
    Trader input{
        static_cast<size_t>(stoi(time_stamp)),
        static_cast<size_t>(stoi(trader_id.substr(1))),
        static_cast<size_t>(stoi(inventory.substr(1))),
        static_cast<size_t>(stoi(cost.substr(1))),
        priority,
    };

    // put the trader/stock into the corresponding stock, and assign it to buyer/seller
    (buy) ? stocks[stock_num].buyers.push(input) : stocks[stock_num].sellers.push(input);
  }
}