/**
 * @file fixed_point_price.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference solution — integer-scaled price type, no floating point.
 *
 * Money is never a double. 0.1 has no exact binary representation, so a double
 * price accumulates error, compares unequal to itself after a round trip, and
 * ties-to-even rounding silently loses a tick. Exchanges quote in integral
 * ticks; the type below stores an integer count of 1/kScale units and does all
 * arithmetic in int64.
 *
 * What this question is really testing:
 *   - parsing "123.45" without going through strtod
 *   - rounding half-away-from-zero at the boundary, symmetric for negatives
 *   - notional = price * qty overflowing int64 if you multiply before scaling
 *   - equality and ordering being exact, which is the whole point
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <compare>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

class Price {
 public:
  /// Ticks per whole unit: 4 decimal places.
  static constexpr std::int64_t kScale = 10000;

  constexpr Price() = default;
  static constexpr Price fromTicks(std::int64_t ticks) { return Price(ticks); }

  /// Parses a decimal string exactly, without floating point.
  /// Accepts an optional sign, digits, and at most kScale's worth of decimals;
  /// extra decimal places are rounded half away from zero.
  static std::optional<Price> parse(std::string_view text) {
    if (text.empty()) return std::nullopt;

    bool negative = false;
    if (text.front() == '+' || text.front() == '-') {
      negative = text.front() == '-';
      text.remove_prefix(1);
    }
    if (text.empty()) return std::nullopt;

    const std::size_t dot = text.find('.');
    const std::string_view whole = text.substr(0, dot);
    const std::string_view frac = dot == std::string_view::npos
                                      ? std::string_view{}
                                      : text.substr(dot + 1);
    if (whole.empty() && frac.empty()) return std::nullopt;
    if (!allDigits(whole) || !allDigits(frac)) return std::nullopt;

    std::int64_t ticks = 0;
    for (const char c : whole) ticks = ticks * 10 + (c - '0');
    ticks *= kScale;

    std::int64_t unit = kScale / 10;
    std::size_t i = 0;
    for (; i < frac.size() && unit > 0; ++i, unit /= 10) {
      ticks += (frac[i] - '0') * unit;
    }
    // Round half away from zero on the first digit we cannot represent.
    if (i < frac.size() && frac[i] >= '5') ++ticks;

    return Price(negative ? -ticks : ticks);
  }

  constexpr std::int64_t ticks() const { return ticks_; }

  /// Notional value of @p qty at this price, in ticks. Scaling is left to the
  /// caller precisely because the product is what overflows.
  constexpr std::int64_t notionalTicks(std::int64_t qty) const {
    return ticks_ * qty;
  }

  std::string toString() const {
    const bool negative = ticks_ < 0;
    // Negate in unsigned to stay defined for INT64_MIN.
    const auto magnitude = negative ? -static_cast<std::uint64_t>(ticks_)
                                    : static_cast<std::uint64_t>(ticks_);
    const auto scale = static_cast<std::uint64_t>(kScale);

    std::string out = negative ? "-" : "";
    out += std::to_string(magnitude / scale);
    out += '.';

    std::string frac = std::to_string(magnitude % scale);
    out.append(kDecimals - frac.size(), '0');
    out += frac;
    return out;
  }

  constexpr Price operator+(Price rhs) const {
    return Price(ticks_ + rhs.ticks_);
  }
  constexpr Price operator-(Price rhs) const {
    return Price(ticks_ - rhs.ticks_);
  }
  constexpr Price operator-() const { return Price(-ticks_); }

  // Exact, because the representation is exact.
  friend constexpr bool operator==(Price, Price) = default;
  friend constexpr std::strong_ordering operator<=>(Price, Price) = default;

 private:
  static constexpr std::size_t kDecimals = 4;

  explicit constexpr Price(std::int64_t ticks) : ticks_(ticks) {}

  static constexpr bool allDigits(std::string_view s) {
    for (const char c : s) {
      if (c < '0' || c > '9') return false;
    }
    return true;
  }

  std::int64_t ticks_ = 0;
};

// ------------------------------------------------------------------- TESTS --

namespace {

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

bool parsesTo(std::string_view text, std::int64_t expected_ticks) {
  const std::optional<Price> p = Price::parse(text);
  return p.has_value() && p->ticks() == expected_ticks;
}

/// Guarded round-trip check: a parse that fails must report a failure, not
/// dereference an empty optional.
bool renders(std::string_view text, std::string_view expected) {
  const std::optional<Price> p = Price::parse(text);
  return p.has_value() && p->toString() == expected;
}

Price priceOr(std::string_view text, Price fallback) {
  const std::optional<Price> p = Price::parse(text);
  return p.value_or(fallback);
}

bool doTestsPass() {
  bool passed = true;

  passed &= expect("whole number", parsesTo("123", 1230000));
  passed &= expect("two decimals", parsesTo("123.45", 1234500));
  passed &= expect("four decimals", parsesTo("0.0001", 1));
  passed &= expect("leading dot", parsesTo(".5", 5000));
  passed &= expect("trailing dot", parsesTo("7.", 70000));
  passed &= expect("zero", parsesTo("0", 0));
  passed &= expect("explicit plus", parsesTo("+2.5", 25000));
  passed &= expect("negative", parsesTo("-1.25", -12500));

  // Rounding must be symmetric about zero, not toward it.
  passed &= expect("rounds half up", parsesTo("0.00005", 1));
  passed &= expect("rounds down below half", parsesTo("0.00004", 0));
  passed &= expect("negative rounds away from zero", parsesTo("-0.00005", -1));

  passed &= expect("empty rejected", !Price::parse("").has_value());
  passed &= expect("sign alone rejected", !Price::parse("-").has_value());
  passed &= expect("dot alone rejected", !Price::parse(".").has_value());
  passed &= expect("letters rejected", !Price::parse("12a.5").has_value());
  passed &= expect("letters in fraction rejected",
                   !Price::parse("12.5x").has_value());
  passed &= expect("second dot rejected", !Price::parse("1.2.3").has_value());

  // Round trip is exact — the property a double cannot give you.
  passed &= expect("round trip", renders("123.4500", "123.4500"));
  passed &= expect("pads decimals", renders("5", "5.0000"));
  passed &= expect("sub-unit round trip", renders("0.0001", "0.0001"));
  passed &= expect("negative round trip", renders("-0.5", "-0.5000"));

  // The classic double trap: 0.1 + 0.2 != 0.3 in binary floating point.
  {
    const Price a = priceOr("0.1", Price::fromTicks(-1));
    const Price b = priceOr("0.2", Price::fromTicks(-2));
    const Price c = priceOr("0.3", Price::fromTicks(-3));
    passed &= expect("0.1 + 0.2 == 0.3 exactly", a + b == c);
    passed &=
        expect("0.1 + 0.2 renders as 0.3000", (a + b).toString() == "0.3000");
  }

  // Accumulating a tick a thousand times must not drift.
  {
    Price total;
    const Price tick = Price::fromTicks(1);
    for (int i = 0; i < 1000; ++i) total = total + tick;
    passed &= expect("no accumulation drift",
                     total == priceOr("0.1", Price::fromTicks(-1)));
  }

  // Ordering is exact.
  {
    const Price low = priceOr("99.9999", Price::fromTicks(-1));
    const Price high = priceOr("100.0000", Price::fromTicks(-2));
    passed &= expect("ordering", low < high);
    passed &= expect("one tick apart", high.ticks() - low.ticks() == 1);
    passed &= expect("negation", (-low).ticks() == -low.ticks());
    passed &= expect("subtraction", (high - low) == Price::fromTicks(1));
  }

  passed &= expect("notional in ticks",
                   priceOr("10.5", Price()).notionalTicks(200) == 21000000);
  passed &= expect("negative notional",
                   priceOr("-2.5", Price()).notionalTicks(4) == -100000);

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
