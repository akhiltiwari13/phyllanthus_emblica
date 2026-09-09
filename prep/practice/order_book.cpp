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
#include <iostream>
#include <optional>

enum class Side { kBuy, kSell };

struct Quote {
  std::int64_t price = 0;
  std::uint64_t qty = 0;

  friend bool operator==(const Quote&, const Quote&) = default;
};

class OrderBook {
 public:
  bool add(std::uint64_t id, Side side, std::int64_t price, std::uint64_t qty) {
    (void)id, (void)side, (void)price, (void)qty;
    return false;  // TODO
  }

  bool cancel(std::uint64_t id) {
    (void)id;
    return false;  // TODO
  }

  bool reduce(std::uint64_t id, std::uint64_t qty) {
    (void)id, (void)qty;
    return false;  // TODO
  }

  std::optional<Quote> bestBid() const { return std::nullopt; }  // TODO

  std::optional<Quote> bestAsk() const { return std::nullopt; }  // TODO

  std::optional<std::int64_t> spread() const { return std::nullopt; }  // TODO

  std::uint64_t qtyAt(Side side, std::int64_t price) const {
    (void)side, (void)price;
    return 0;  // TODO
  }

  std::size_t restingOrders() const { return 0; }  // TODO
};

// ------------------------------------------------------------------- TESTS --

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
