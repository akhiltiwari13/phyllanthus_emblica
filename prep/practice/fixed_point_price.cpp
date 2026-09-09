/**
 * @file fixed_point_price.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief PRACTICE — exact decimal price type, no floating point. 30 minutes.
 *
 * Money is never a double: 0.1 has no exact binary representation, so prices
 * drift as you accumulate them and 0.1 + 0.2 != 0.3. Store an integer count of
 * ticks instead. Four decimal places, so kScale = 10000.
 *
 *   static optional<Price> parse(string_view)
 *       "123.45" -> 1234500 ticks. Optional sign, optional fraction; ".5" and
 *       "7." are both valid, "" "-" "." "1.2.3" "12a" are not. More than four
 *       decimals rounds half away from zero — and away from zero for negatives
 *       too, not toward it.
 *   static constexpr Price fromTicks(int64_t)
 *   int64_t ticks()
 *   int64_t notionalTicks(qty)     price * qty, still in ticks
 *   string toString()              exact round trip, always four decimals
 *   + - unary-  ==  <=>            exact, because the representation is exact
 *
 * Do the parse yourself: no strtod, no stod, no ostringstream with precision.
 * Watch the sign handling in toString(), and think about what negating
 * INT64_MIN does.
 *
 * Run it: the tests below are the spec. Reference in solutions/.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <compare>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

class Price {
 public:
  static constexpr std::int64_t kScale = 10000;

  constexpr Price() = default;

  static constexpr Price fromTicks(std::int64_t ticks) { return Price(ticks); }

  static std::optional<Price> parse(std::string_view text) {
    (void)text;
    return std::nullopt;  // TODO
  }

  constexpr std::int64_t ticks() const { return ticks_; }

  constexpr std::int64_t notionalTicks(std::int64_t qty) const {
    (void)qty;
    return 0;  // TODO
  }

  std::string toString() const { return {}; }  // TODO

  constexpr Price operator+(Price rhs) const {
    (void)rhs;
    return Price(0);  // TODO
  }

  constexpr Price operator-(Price rhs) const {
    (void)rhs;
    return Price(0);  // TODO
  }

  constexpr Price operator-() const { return Price(0); }  // TODO

  friend constexpr bool operator==(Price, Price) = default;
  friend constexpr std::strong_ordering operator<=>(Price, Price) = default;

 private:
  explicit constexpr Price(std::int64_t ticks) : ticks_(ticks) {}

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
