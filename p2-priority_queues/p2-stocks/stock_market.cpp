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

void Market::trade()
{
  cout << "Processing orders..." << "\n";

  while (!waiting.empty()) // keep running until there are no more offers in the prio queue;
  {
    while (!waiting.empty() && waiting.front().time == current_timestamp) // keep running on timestamp
    {
      // place trade into corresponding market for their stock
      auto trader = &waiting.front();
      if (trader->intent) // buy
      {
        stocks[trader->stock].buyers.push(*trader);
        stocks[trader->stock].buying++;
      }
      else
      {
        stocks[trader->stock].sellers.push(*trader);
        stocks[trader->stock].selling++;
      }

      if (stocks[trader->stock].buying > 0 && stocks[trader->stock].selling > 0)
      {
        process_trade(stocks[trader->stock], trader->stock);
      }

      waiting.pop();
    } // while (.top().time)
    current_timestamp++;
  } // while (.empty())

  cout << "---End of Day---" << '\n';
  cout << "Trades Completed: " << completed_trades << '\n';

  if (i_out)
    trader_info_output();

  if (t_out)
    time_traveler_output();
}

void Market::process_trade(Stock &stock, size_t stock_id)
{
  // while the pq's aren't empty and they can match each other
  while (!stock.sellers.empty() && !stock.buyers.empty() && stock.sellers.top().price <= stock.buyers.top().price)
  {
    auto seller = stock.sellers.top();
    auto buyer = stock.buyers.top();

    size_t price;
    size_t quantity = min(buyer.inventory, seller.inventory);

    if (seller.priority < buyer.priority) // seller has priority so we take their price
      price = seller.price;
    else // buyer has priority so we take their price
      price = buyer.price;

    if (t_out)
    {
      // first time run through, assign it to the top of each
      if (stock.num_traded == 0)
      {
        stock.price1 = seller.price;
        stock.price2 = buyer.price;
        stock.timestamp1 = seller.time;
        stock.timestamp2 = buyer.time;
      }
      else
      {
        if (buyer.time > stock.timestamp1 && buyer.price > stock.price2)
        {
          stock.price2 = buyer.price;
          stock.timestamp2 = buyer.time;
        }
        if (seller.time < stock.timestamp2 && seller.price < stock.price1)
        {
          stock.price1 = seller.price;
          stock.timestamp1 = seller.time;
        }
      }
    }

    if (buyer.inventory == quantity)
    {
      stock.buyers.pop();
      seller.inventory -= quantity;
      stock.sellers.pop();
      stock.sellers.push(seller);
    }
    else
    {
      stock.sellers.pop();
      buyer.inventory -= quantity;
      stock.buyers.pop();
      stock.buyers.push(buyer);
    }

    if (v_out)
      cout << "Trader " << buyer.id << " purchased " << quantity << " shares of Stock " << stock_id
           << " from Trader " << seller.id << " for $" << price << "/share" << '\n';

    if (i_out)
    {
      // buyer
      trader_info[buyer.id].bought += static_cast<int>(quantity);
      trader_info[buyer.id].net -= static_cast<int>(quantity * price);

      // seller
      trader_info[seller.id].sold += static_cast<int>(quantity);
      trader_info[seller.id].net += static_cast<int>(quantity * price);
    }

    stock.num_traded++;
    completed_trades++;
  }
}