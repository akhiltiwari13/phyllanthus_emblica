/**
 * @file order_book.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference solution — aggregated limit order book.
 *
 * Two ordered maps keyed by price (bids descending, asks ascending) give
 * O(log L) insert and O(1) top-of-book via begin(). A flat id -> order index
 * makes cancel/reduce O(log L) without scanning levels. Aggregate quantity is
 * cached per level, so qtyAt() and bestBid()/bestAsk() never walk the resting
 * orders, and a level is erased the moment it empties — a book that keeps
 * zero-quantity levels around will eventually report a stale best price.
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
#include <unordered_map>

enum class Side { kBuy, kSell };

struct Quote {
  std::int64_t price = 0;
  std::uint64_t qty = 0;

  friend bool operator==(const Quote&, const Quote&) = default;
};

class OrderBook {
 public:
  /// @return false if @p id is already resting, or @p qty is zero.
  bool add(std::uint64_t id, Side side, std::int64_t price, std::uint64_t qty) {
    if (qty == 0 || orders_.contains(id)) return false;

    orders_.emplace(id, Order{side, price, qty});
    if (side == Side::kBuy) {
      bids_[price] += qty;
    } else {
      asks_[price] += qty;
    }
    return true;
  }

  /// @return false if @p id is not resting.
  bool cancel(std::uint64_t id) {
    const auto it = orders_.find(id);
    if (it == orders_.end()) return false;

    removeQty(it->second.side, it->second.price, it->second.qty);
    orders_.erase(it);
    return true;
  }

  /// Reduces a resting order by @p qty, removing it once it reaches zero.
  /// @return false if @p id is unknown, @p qty is zero, or @p qty exceeds the
  ///         resting quantity.
  bool reduce(std::uint64_t id, std::uint64_t qty) {
    const auto it = orders_.find(id);
    if (it == orders_.end() || qty == 0 || qty > it->second.qty) return false;

    removeQty(it->second.side, it->second.price, qty);
    it->second.qty -= qty;
    if (it->second.qty == 0) orders_.erase(it);
    return true;
  }

  std::optional<Quote> bestBid() const {
    if (bids_.empty()) return std::nullopt;
    return Quote{bids_.begin()->first, bids_.begin()->second};
  }

  std::optional<Quote> bestAsk() const {
    if (asks_.empty()) return std::nullopt;
    return Quote{asks_.begin()->first, asks_.begin()->second};
  }

  /// Best ask minus best bid; nullopt while either side is empty.
  std::optional<std::int64_t> spread() const {
    if (bids_.empty() || asks_.empty()) return std::nullopt;
    return asks_.begin()->first - bids_.begin()->first;
  }

  std::uint64_t qtyAt(Side side, std::int64_t price) const {
    if (side == Side::kBuy) {
      const auto it = bids_.find(price);
      return it == bids_.end() ? 0 : it->second;
    }
    const auto it = asks_.find(price);
    return it == asks_.end() ? 0 : it->second;
  }

  std::size_t restingOrders() const { return orders_.size(); }

 private:
  struct Order {
    Side side;
    std::int64_t price;
    std::uint64_t qty;
  };

  // Bids descend so begin() is the highest buy; asks ascend so begin() is the
  // lowest sell. Both therefore expose top-of-book in O(1).
  using Bids = std::map<std::int64_t, std::uint64_t, std::greater<>>;
  using Asks = std::map<std::int64_t, std::uint64_t, std::less<>>;

  template <typename Levels>
  static void eraseFrom(Levels& levels, std::int64_t price, std::uint64_t qty) {
    const auto it = levels.find(price);
    if (it == levels.end()) return;
    it->second -= qty;
    if (it->second == 0) levels.erase(it);
  }

  void removeQty(Side side, std::int64_t price, std::uint64_t qty) {
    if (side == Side::kBuy) {
      eraseFrom(bids_, price, qty);
    } else {
      eraseFrom(asks_, price, qty);
    }
  }

  Bids bids_;
  Asks asks_;
  std::unordered_map<std::uint64_t, Order> orders_;
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
