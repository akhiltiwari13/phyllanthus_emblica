#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

// Structure to represent an order
struct Order {
  char side; // 'B' for buy, 'S' for sell
  int quantity;
  int price;
};

// Type alias for the order book
using OrderBook = std::map<int, std::vector<Order>>;

// Function to process a new order
void processNewOrder(OrderBook &orderBook, int orderId, char side, int quantity,
                     int price) {
  Order order{side, quantity, price};
  orderBook[price].push_back(order);
}

// Function to process a delete order
void processDeleteOrder(OrderBook &orderBook, int orderId) {
  for (auto &[price, orders] : orderBook) {
    auto it = std::remove_if(
        orders.begin(), orders.end(),
        [orderId](const Order &order) { return order.orderId == orderId; });
    orders.erase(it, orders.end());
  }
}

// Function to match orders and print trades
void matchOrders(OrderBook &orderBook) {
  auto bidIt = orderBook.rbegin();
  auto askIt = orderBook.begin();

  while (bidIt != orderBook.rend() && askIt != orderBook.end()) {
    int bidPrice = bidIt->first;
    int askPrice = askIt->first;

    if (bidPrice >= askPrice) {
      auto &bidOrders = bidIt->second;
      auto &askOrders = askIt->second;

      int tradeQuantity =
          std::min(bidOrders[0].quantity, askOrders[0].quantity);

      std::cout << tradeQuantity << " shares of XYZ were sold at " << askPrice
                << " USD\n";

      bidOrders[0].quantity -= tradeQuantity;
      askOrders[0].quantity -= tradeQuantity;

      if (bidOrders[0].quantity == 0) {
        bidOrders.erase(bidOrders.begin());
        if (bidOrders.empty())
          bidIt = std::next(bidIt).base();
      }

      if (askOrders[0].quantity == 0) {
        askOrders.erase(askOrders.begin());
        if (askOrders.empty())
          ++askIt;
      }
    } else {
      break;
    }
  }
}

// Function to print the order book
void printOrderBook(const OrderBook &orderBook) {
  std::cout << "=================\n";
  std::cout << "ASK\n";
  for (auto it = orderBook.rbegin(); it != orderBook.rend(); ++it) {
    int price = it->first;
    const auto &orders = it->second;
    std::cout << price << ": ";
    for (const auto &order : orders) {
      std::cout << order.quantity << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "------------\n";
  std::cout << "BID\n";
  std::cout << "=================\n";
}

// Function to process the market data file
void processMarketData(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Failed to open the market data file.\n";
    return;
  }

  OrderBook orderBook;
  std::unordered_map<int, Order> activeOrders;
  std::string line;

  while (std::getline(file, line)) {
    char messageType;
    int orderId, quantity, price;
    char side;

    std::stringstream ss(line);
    ss >> messageType >> orderId >> side >> quantity >> price;

    if (messageType == 'A') {
      processNewOrder(orderBook, orderId, side, quantity, price);
      activeOrders[orderId] = {side, quantity, price};
    } else if (messageType == 'X') {
      processDeleteOrder(orderBook, orderId);
      activeOrders.erase(orderId);
    }

    matchOrders(orderBook);
  }

  for (const auto &[orderId, order] : activeOrders) {
    processNewOrder(orderBook, orderId, order.side, order.quantity,
                    order.price);
  }

  printOrderBook(orderBook);
}

int main() {
  processMarketData("market_data.txt");
  return 0;
}
