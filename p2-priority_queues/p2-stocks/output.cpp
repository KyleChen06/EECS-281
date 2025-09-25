// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6
#include <iostream>

#include "stock_market.hpp"

using namespace std;

void Market::trader_info_output() {
  cout << "---Trader Info---" << '\n';
  for (size_t i = 0; i < trader_info.size(); i++) {
    cout << "Trader " << i << " bought " << trader_info[i].bought << " and sold " << trader_info[i].sold
         << " for a net transfer of $" << trader_info[i].net << '\n';
  }
}

void Market::time_traveler_output() {
  cout << "---Time Travelers---" << '\n';
  for (size_t i = 0; i < stocks.size(); i++) {
    if (stocks[i].num_traded > 0 && stocks[i].price1 < stocks[i].price2 && stocks[i].timestamp1 <= stocks[i].timestamp2)
      cout << "A time traveler would buy Stock " << i << " at time " << stocks[i].timestamp1 << " for $" << stocks[i].price1
           << " and sell it at time " << stocks[i].timestamp2 << " for $" << stocks[i].price2 << '\n';
    else
      cout << "A time traveler could not make a profit on Stock " << i << '\n';
  }
}