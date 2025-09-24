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
  stocks.resize(num_stocks);

  // use helper functions to read in rest based on inputMode
  if (inputMode == 0)
    processInput(cin);
  else
  {
    stringstream ss;

    cin >> temp >> temp;
    seed = static_cast<size_t>(stoi(temp));

    cin >> temp >> temp;
    num_orders = static_cast<size_t>(stoi(temp));

    cin >> temp >> temp;
    arr_rate = static_cast<size_t>(stoi(temp));

    P2random::PR_init(ss, static_cast<unsigned int>(seed), static_cast<unsigned int>(num_traders), static_cast<unsigned int>(num_stocks), static_cast<unsigned int>(num_orders), static_cast<unsigned int>(arr_rate));
    processInput(ss);
  }
}

void Market::processInput(istream &inputStream)
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
    size_t priority;
    if (intent[0] == 'B')
    {
      priority = stocks[stock_num].buyers.size();
    }
    else
    {
      priority = stocks[stock_num].sellers.size();
    }
    // size_t priority = (intent.front() == 'B') ? stocks[stock_num].buyers.size() : stocks[stock_num].sellers.size();
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