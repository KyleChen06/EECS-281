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
  if (i_out)
    trader_info.resize(num_traders);

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
  string Ktime_stamp;
  string Kintent;
  string Ktrader_id;
  string Kstock_id;
  string Kcost;
  string Kinventory;

  size_t t = 0;
  size_t priority = 0;

  while (inputStream >> Ktime_stamp >> Kintent >> Ktrader_id >> Kstock_id >> Kcost >> Kinventory)
  {
    // size_t stock_num = static_cast<size_t>(stoi(Kstock_id.substr(1)));
    int trader_id_int = (stoi(Ktrader_id.substr(1)));
    int stock_id_int = (stoi(Kstock_id.substr(1)));
    int price_int = (stoi(Kcost.substr(1)));
    int quantity_int = (stoi(Kinventory.substr(1)));
    int time_int = (stoi(Ktime_stamp));
    bool intent = 0;

    // cerrs
    if (!inputMode) // TL mode
    {
      if (time_int < 0)
      {
        cerr << "Error: Negative timestamp" << endl;
        exit(1);
      }
      else if (static_cast<size_t>(time_int) > t)
      {
        t = static_cast<size_t>(time_int);
      }
      else if (static_cast<size_t>(time_int) < t)
      {
        cerr << "Error: Decreasing timestamp" << endl;
        exit(1);
      }
      else if (trader_id_int < 0 || static_cast<size_t>(trader_id_int) >= num_traders)
      {
        cerr << "Error: Invalid trader ID" << endl;
        exit(1);
      }
      else if (stock_id_int < 0 || static_cast<size_t>(stock_id_int) >= num_stocks)
      {
        cerr << "Error: Invalid stock ID" << endl;
        exit(1);
      }
      else if (quantity_int < 0)
      {
        cerr << "Error: Invalid price" << endl;
        exit(1);
      }
      else if (price_int < 0)
      {
        cerr << "Error: Invalid quantity" << endl;
        exit(1);
      }
    }

    size_t trader_id = static_cast<size_t>(stoi(Ktrader_id.substr(1)));
    size_t stock_id = static_cast<size_t>(stoi(Kstock_id.substr(1)));
    size_t price = static_cast<size_t>(stoi(Kcost.substr(1)));
    size_t quantity = static_cast<size_t>(stoi(Kinventory.substr(1)));
    size_t time = static_cast<size_t>(stoi(Ktime_stamp));

    if (Kintent[0] == 'B')
      intent = 1;

    // create trader object to place into Market
    Trader input{
        time,
        priority,
        intent,
        trader_id,
        stock_id,
        quantity,
        price,
    };

    // push all into priority queue
    waiting.push(input);
    priority++;
  }
}