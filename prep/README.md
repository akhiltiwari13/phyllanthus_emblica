# Interview prep

Company-agnostic prep material. A specific test's questions belong under
`interview-experience/<company>/`; what lives here is reusable across tests.

```
prep/
├── mcq/low_latency_cpp.md      revision sheet for low-latency C++ MCQs
├── templates/q00_template.cpp  starting point for a timed OA question
└── practice/
    ├── <problem>.cpp           stub + tests — solve this one
    └── solutions/<problem>.cpp worked reference
```

## Practice problems

Each problem builds twice. `practice_<name>` is the stub: it compiles clean but prints
`TESTS FAILED.` until you implement it. `solution_<name>` is the worked reference, running
the identical test block. The problem statement, the constraints and the traps are in the
file header — read that, not the solution.

| Problem | Target | What it tests |
| --- | --- | --- |
| `order_book` | 35 min | `std::map` ordering, top-of-book in O(1), erasing an emptied price level |
| `feed_arbitrator` | 30 min | A/B multicast arbitration, sequence gaps, reorder buffering |
| `object_pool` | 35 min | `alignas`, placement `new`, manual destruction, intrusive free list |
| `timer_wheel` | 35 min | O(1) schedule/cancel, modular bucketing, deadline aliasing past one revolution |
| `fixed_point_price` | 30 min | exact decimal arithmetic, half-away-from-zero rounding, why money is never a `double` |
| `lru_cache` | 25 min | intrusive list + hash index, `splice`, iterator-invalidation rules |

These were chosen to fill gaps: ring buffers, SPSC queues, producer/consumer, market-data
and ticker parsers, rate limiters, schedulers and graph traversal are all already solved
elsewhere in this repo — see `interview-experience/` and `extras/` before adding more.

## Working a problem against the clock

```bash
# one problem, fast iteration (always -j 6 on this machine)
cmake --build build/Debug -j 6 --target practice_order_book
./build/Debug/prep/practice/practice_order_book

# compare against the reference once you are done
cmake --build build/Debug -j 6 --target solution_order_book
./build/Debug/prep/practice/solution_order_book
```

For anything doing manual memory management (`object_pool`), iterate under sanitizers —
the tests count live instances, but ASan catches the rest:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -g \
    -o /tmp/op prep/practice/object_pool.cpp && /tmp/op
```

## On the day

1. Copy `templates/q00_template.cpp`, paste the given skeleton over the SOLUTION block.
2. Transcribe the worked examples from the problem statement into `doTestsPass()` **before**
   implementing — they are free test cases and catch off-by-ones faster than re-reading code.
3. Keep the `#ifndef RunTests` guard: graders (Codility, HackerRank, TT's own harness)
   compile with `RunTests` defined and supply their own `main`.
4. Before submitting: every member initialised, empty/single/all-equal inputs handled,
   overflow considered on any accumulation, no allocation in a loop the problem calls hot.
