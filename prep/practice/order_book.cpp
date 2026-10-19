/**
 * @file order_book.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief PRACTICE — aggregated limit order book. Target: 35 minutes.
 *
 * Build a book that tracks resting orders and exposes top-of-book cheaply.
 *
 *   bool add(id, side, price, qty)   reject a duplicate id or a zero qty
 *   bool cancel(id)                  remove a resting order entirely
 *   bool reduce(id, qty)             shrink one; remove it if it hits zero
 *   optional<Quote> bestBid()        highest resting buy  + its total qty
 *   optional<Quote> bestAsk()        lowest  resting sell + its total qty
 *   optional<int64_t> spread()       bestAsk - bestBid, nullopt if either empty
 *   uint64_t qtyAt(side, price)      aggregate qty resting at one price
 *   size_t restingOrders()
 *
 * Matching is out of scope: a crossed book is stored as-is, and spread() may
 * come back negative.
 *
 * Aim for O(log L) add/cancel/reduce in the number of price levels, and O(1)
 * top-of-book. Think about what has to happen to a price level the moment its
 * last order leaves, and what bestBid() would report if it did not.
 *
 * Run it: the tests below are the spec. Fill in OrderBook until it prints
 * ALL TESTS PASS. Reference solution in solutions/order_book.cpp.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>

// Follow-up questions an interviewer may ask
//
// - Sorted vector instead of map? It's better for the cache, and cheap when
// there are few levels and most activity is near the best
//   price.
// - Prices limited to a fixed range? Use an array indexed by tick, plus a
// cached best index, and every operation becomes O(1).
// - Fewer allocations? Use a custom allocator or reuse nodes for the maps on
// the hot path.

enum class Side { kBuy, kSell };

struct Quote {
  std::int64_t price = 0;
  std::uint64_t qty = 0;

  // @ques: what does = default does?
  // @ques: can you explain why this friend function in inside the struct?
  // shouldn't the friend function be outside the class it's a friend of? please
  // clarify?
  friend bool operator==(const Quote&, const Quote&) = default;
  // friend bool operator==(const Quote& q1, const Quote& q2) {
  //   return (q1.price == q2.price) && (q1.qty == q2.qty);
  // }
};

// represent an order
struct Order {
  uint64_t id{};
  Side side{};
  Quote quote{};
};

class OrderBook {
 public:
  bool add(std::uint64_t id, Side side, std::int64_t price, std::uint64_t qty) {
    // (void)id, (void)side, (void)price,
    //     (void)qty;  // casting it to make it compile?

    if (!qty) {
      // std::cout << "invalid  quantity" << std::endl;
      return false;
    }
    if (_orders.contains(id)) {
      // std::cout << "order exists" << std::endl;
      return false;
    } else {
      if (side == Side::kBuy) {
        _bids[price] += qty;
      } else {
        _asks[price] += qty;
      }
      _orders[id] = {id, side, {price, qty}};
    }
    return true;
  }

  bool cancel(std::uint64_t id) {
    if (!_orders.contains(id)) {
      // std::cout << "order doesn't exist!" << std::endl;
      return false;
    }
    auto& ord = _orders[id];
    if (ord.side == Side::kBuy) {
      _bids[ord.quote.price] -= ord.quote.qty;
      if (!_bids[ord.quote.price]) _bids.erase(ord.quote.price);
    } else {
      _asks[ord.quote.price] -= ord.quote.qty;
      if (!_asks[ord.quote.price]) _asks.erase(ord.quote.price);
    }
    _orders.erase(id);
    return true;
  }

  bool reduce(std::uint64_t id, std::uint64_t qty) {
    // (void)id, (void)qty;
    if (qty <= 0) return false;
    if (!_orders.contains(id)) return false;
    if (_orders[id].quote.qty < qty) return false;
    auto& ord = _orders[id];
    if (ord.side == Side::kBuy) {
      _bids[ord.quote.price] -= qty;
      // if (!_bids[ord.quote.price]) {
      //   _bids.erase(ord.quote.price);
      //   _orders.erase(id);
      // }
    } else {
      _asks[ord.quote.price] -= qty;
      // if (!_asks[ord.quote.price]) {
      //   _asks.erase(ord.quote.price);
      //   _orders.erase(id);
      // }
    }
    _orders[id].quote.qty -=
        qty;  // reduce must update the quantity in order lists as well!
    if (!_orders[id].quote.qty) _orders.erase(id);

    return true;
  }

  std::optional<Quote> bestBid() const {
    if (!_bids.empty()) {
      return std::optional<Quote>{
          {_bids.rbegin()->first, _bids.rbegin()->second}};
    }
    return std::nullopt;
  }

  std::optional<Quote> bestAsk() const {
    if (!_asks.empty()) {
      return std::optional<Quote>{
          {_asks.begin()->first, _asks.begin()->second}};
    }
    return std::nullopt;
  }

  std::optional<std::int64_t> spread() const {
    if (!_asks.empty() && !_bids.empty()) {
      return _asks.begin()->first - _bids.rbegin()->first;
    }  // TODO
    return std::nullopt;
  }

  // .at() throws std::out_of_range for a
  // missing key, and a missing level should give 0. Use find and return 0
  // when nothing is found.
  std::uint64_t qtyAt(Side side, std::int64_t price) const {
    // (void)side, (void)price;
    if (side == Side::kBuy) {
      if (_bids.find(price) != _bids.end()) {
        return _bids.at(price);
      }
    } else {
      if (_asks.find(price) != _asks.end()) {
        return _asks.at(price);
      }
    }
    return 0;  // TODO
  }

  std::size_t restingOrders() const { return _orders.size(); }
  //
 private:
  // The priority_queue won't compile. The template is priority_queue<T,
  // Container, Compare>, and your second argument is a comparator where
  // the container goes. The comparators are also swapped: std::less gives a
  // max-heap, which suits bids, and std::greater gives a min-heap, which
  // suits asks.

  // @ask: there is a commom orderbook implementation using a
  // heap/priority_queue.. how did that go?

  // std::priority_queue<Quote, std::greater> bids;
  // std::priority_queue<Quote, std::less> asks;
  //
  // std::map<int, std::vector<Order>> _bids, _asks;  //<price-level,
  // order_list>
  std::map<int64_t, uint64_t> _bids, _asks;  //<price-level, quantity>
  std::unordered_map<uint64_t, Order>
      _orders;  // directly point my order to it's
                // location in the _bids and _asks
};

// ------------------------------------------------------------------- TESTS
// --

namespace {

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

bool doTestsPass() {
  bool passed = true;
  OrderBook book;

  passed &= expect("empty book has no bid", !book.bestBid().has_value());
  passed &= expect("empty book has no ask", !book.bestAsk().has_value());
  passed &= expect("empty book has no spread", !book.spread().has_value());

  passed &= expect("add bid", book.add(1, Side::kBuy, 100, 10));
  passed &=
      expect("add second bid, same level", book.add(2, Side::kBuy, 100, 5));
  passed &= expect("add better bid", book.add(3, Side::kBuy, 101, 7));
  passed &= expect("add ask", book.add(4, Side::kSell, 105, 20));

  passed &= expect("duplicate id rejected", !book.add(1, Side::kBuy, 99, 1));
  passed &= expect("zero qty rejected", !book.add(9, Side::kBuy, 99, 0));

  passed &= expect("level aggregates", book.qtyAt(Side::kBuy, 100) == 15);
  passed &= expect("best bid is highest", book.bestBid() == Quote{101, 7});
  passed &= expect("best ask is lowest", book.bestAsk() == Quote{105, 20});
  passed &= expect("spread", book.spread() == 4);
  passed &= expect("resting count", book.restingOrders() == 4);

  // Cancelling the top bid must promote the level below it.
  passed &= expect("cancel top bid", book.cancel(3));
  passed &= expect("best bid promoted", book.bestBid() == Quote{100, 15});
  passed &= expect("cancel is idempotent-safe", !book.cancel(3));

  // Partial reduce leaves the level; full reduce must erase it.
  passed &= expect("reduce partial", book.reduce(1, 4));
  passed &= expect("level reflects reduce", book.qtyAt(Side::kBuy, 100) == 11);
  passed &= expect("over-reduce rejected", !book.reduce(1, 999));
  passed &= expect("zero reduce rejected", !book.reduce(1, 0));
  passed &= expect("reduce unknown id rejected", !book.reduce(42, 1));

  passed &= expect("reduce to zero", book.reduce(1, 6));
  passed &= expect("order gone after full reduce", !book.cancel(1));
  passed &=
      expect("level survives on sibling", book.qtyAt(Side::kBuy, 100) == 5);

  passed &= expect("cancel last of level", book.cancel(2));
  passed &=
      expect("emptied level reports zero", book.qtyAt(Side::kBuy, 100) == 0);
  passed &= expect("bid side now empty", !book.bestBid().has_value());
  passed &= expect("ask side untouched", book.bestAsk() == Quote{105, 20});
  passed &= expect("no spread with one side", !book.spread().has_value());

  // Crossed book: the structure stores it, matching is out of scope here.
  passed &= expect("add crossing bid", book.add(10, Side::kBuy, 110, 1));
  passed &= expect("crossed spread is negative", book.spread() == -5);

  passed &= expect("only crossing bid and ask rest", book.restingOrders() == 2);
  return passed;
}

}  // namespace

#ifndef RunTests
int main() {
  if (doTestsPass()) {
    std::cout << "ALL TESTS PASS." << std::endl;
  } else {
    std::cout << "TESTS FAILED." << std::endl;
  }
  return 0;
}
#endif
