# Trading Technologies

TT builds trading software — the TT platform, order gateways, risk, market data. The
Gujarat (Ahmedabad) office hires C++ engineers for low-latency work, which sets the tone
of the test: correctness under `-Werror`, then constant factors.

## Test format

Both attempts so far have used a **Codility-style harness**: the grader compiles with
`RunTests` defined and supplies its own `main`, so a submitted file keeps its own `main`
behind `#ifndef RunTests` and must not rename the given class or method signatures. A few
MCQs accompany the coding question.

## Attempts

### `attempt_2021/` — 2021

Two single-class problems, both re-solved here with inline tests. The originals were
submitted with real defects, which is why they are worth redoing rather than reading:

- **`chain_link.cpp`** — given a link in a doubly-linked chain, report which side holds
  more links. The submitted version never initialised `left`/`right`, so `append()` read an
  indeterminate pointer on the first call, and `longerSide()` terminated its leftward walk
  by comparing the cursor against the *right* neighbour.
- **`friend_graph.cpp`** — decide whether two people are in the same connected component of
  a friendship graph. The submitted version kept `visited` local to each recursive call, so
  with bidirectional friendships the recursion never terminated, and it overwrote an early
  `true` with a later `false`.

Both now build as `tt21_chain_link` / `tt21_friend_graph` and print `ALL TESTS PASS.`

The shape of these is worth noting for next time: a small given API, an obvious O(n)
answer, and marks lost on uninitialised state and traversal bookkeeping rather than on
algorithmic insight.

### `tt_guj_2026/` — this attempt

`q01.cpp` is a copy of `prep/templates/q00_template.cpp`, ready to paste the given skeleton
into. Add `q02.cpp` and uncomment its target in `CMakeLists.txt` as more questions arrive,
and record what was actually asked — MCQ topics included — in `tt_guj_2026/README.md` while
it is still fresh.

## Preparing

General material is in [`prep/`](../../prep/), deliberately not duplicated here:

- [`prep/mcq/low_latency_cpp.md`](../../prep/mcq/low_latency_cpp.md) — MCQ revision:
  cache lines and false sharing, branch prediction, memory ordering, dispatch cost,
  allocation, TCP/UDP multicast and feed arbitration, kernel bypass, compiler flags.
- [`prep/practice/`](../../prep/practice/) — timed problems. `order_book`,
  `feed_arbitrator` and `timer_wheel` are the closest fit to TT's order-gateway and
  market-data domain.

## Build

```bash
cmake --build build/Debug -j 6 --target tt21_chain_link tt21_friend_graph tt26_q01
./build/Debug/interview-experience/trading_technologies/attempt_2021/tt21_chain_link
./build/Debug/interview-experience/trading_technologies/attempt_2021/tt21_friend_graph
```
