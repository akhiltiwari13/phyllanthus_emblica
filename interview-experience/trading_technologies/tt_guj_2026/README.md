# tt-guj-2026 — recall log

## Format

- Platform: Codility-style harness (grader defines `RunTests` and supplies its own `main`)
- Content: a few MCQs plus a coding question
- Toolchain specified by the interviewer: **gcc 9.3, `-std=c++2a`** (recorded for the test
  environment; the copy here is built with the repo's normal C++23 toolchain)

## MCQs

Topic and, as far as you remember it, the question and the answer you gave. Cross-reference
`prep/mcq/low_latency_cpp.md` and fold anything new back into it.

| # | Topic | Question | Answered | Confident? |
| --- | --- | --- | --- | --- |
| 1 | thread lifetime | Predict the behaviour: a `timer` class spawning a `std::thread` in its ctor with an empty destructor | `std::terminate()` / SIGABRT — `~thread()` aborts when the thread is still `joinable()` | yes |

**Worth remembering from Q1:** a `std::thread` stays `joinable()` even *after* its function
returns, so the abort is guaranteed rather than a race with the sleep. Only `join()` or
`detach()` clears it. `std::jthread` (C++20) joins on destruction and carries a `stop_token`
for an interruptible wait.

## Coding question — q01, PacketReceiver

### Statement

Messages arrive over a network, each split into multiple parts. The application is notified
about the **start of a packet**, then receives parts of that packet. **Parts may arrive in
any order.** After all parts are sent, another start notification arrives and the
application can process parts of the next packet. E.g. `start, id1, id0, start, id2, id1`.

### Given API

```cpp
class PacketReceiver {
 public:
  void StartPacket();
  bool ReceivePart(uint16_t id, size_t controlsum, const std::string& data);
  std::vector<std::string> GetCollectedPackets() const;
  size_t GetNumOfFailedParts() const;
 private:
  // utility functions
};
```

Control sum is computed with `std::hash<std::string>`.

### Specified behaviour

- `StartPacket()` prepares the object for a new packet. At least one call is required before
  parts can be collected; without it every part is failed. Two calls with no `ReceivePart()`
  in between add an empty packet.
- `ReceivePart()` takes the part's `id` (its order in the final packet), the part's control
  sum, and the payload. It verifies the data, **overwrites** on a repeated `id`, fails if
  `StartPacket()` has not been called, and returns `true` on success / `false` on failure.
- `GetCollectedPackets()` builds the final packets and returns them as strings.
- `GetNumOfFailedParts()` returns the failed-part count **across all packets**.

### Approach

`std::vector<std::map<uint16_t, std::string>>` — one map per packet, keyed by part id.
`std::map` gives ascending-id merge order for free, makes overwrite a plain `operator[]`
assignment, and handles sparse or non-contiguous ids without special-casing. "A packet is
open" is just `!packets_.empty()`, so no separate `started` flag is needed.

- `StartPacket()` — O(1) amortised, `emplace_back()`
- `ReceivePart()` — O(log n) in parts, dominated by hashing the payload, O(len)
- `GetCollectedPackets()` — O(total bytes), one allocation per packet via `reserve()`
- `GetNumOfFailedParts()` — O(1)

### Ambiguities in the statement, and the calls made

Each is a single commented line in the implementation, so it can be flipped if the grader
disagrees.
These are the points to raise aloud in a live round.

1. **Is the currently-open packet returned by `GetCollectedPackets()`?** Taken as yes.
   Otherwise the ordinary `StartPacket` → parts → `GetCollectedPackets` sequence would
   return nothing at all.
2. **`StartPacket()` twice with no parts** gives *two* empty strings, since every started
   packet is returned. The statement's "an empty packet added" describes the one closed by
   the second call; the newly-opened one is empty too and, by (1), also returned.
3. **A repeated `id` arriving with a bad control sum** is verified before storing, so it
   counts as failed and leaves the previously verified part untouched. Letting corruption
   overwrite good data would be a defect.
4. **A valid overwrite is not a failure** — returns `true`, failed count unchanged.

### The trap in the tests

`std::hash` is **not** specified to be stable across implementations, and is not. For
`"hello"`, libstdc++ gives `2762169579135187400`; libc++ gives `235368941344721064`.
Control sums in the tests are therefore computed, never hardcoded — a literal would pass
under `debug-omarchy-x86-gcc` and fail under `debug-omarchy-x86-clang`.

### Follow-ups to expect

- **Why `std::map`?** O(log n) per part plus a pointer chase per node. Dense ids →
  `std::vector<std::string>` indexed by id, O(1) and cache-friendly. Sparse ids →
  `unordered_map` plus one sort at collection time. `std::map` is the choice that stays
  correct for any id distribution.
- **What if a part never arrives?** Nothing here expires: partial packets are held forever.
  A real line handler bounds in-flight packets or ages them out — see
  `prep/practice/timer_wheel.cpp`.
- **Is `std::hash` a checksum?** No. It is not a cryptographic or error-detecting code, it
  has no avalanche guarantee, and it is not portable. A real wire protocol uses CRC32C
  (hardware instruction on x86) or similar.
- **Concurrency.** The class is not thread-safe. A real receiver takes parts off a network
  thread; the usual answer is one receiver per stream rather than a lock.

### Result

- Result: _fill in_
- What cost time: _fill in_

## Build

```bash
cmake --build build/build/Debug -j 6 --target tt26_q01_packet_receiver
./build/build/Debug/interview-experience/trading_technologies/tt_guj_2026/tt26_q01_packet_receiver
```

Split across three files — `q01_packet_receiver.h` (declaration),
`q01_packet_receiver.cpp` (definitions) and `q01_main.cpp` (tests). Verified as separate
translation units under gcc C++23, clang with libc++, and `-fsanitize=address,undefined`.

## Afterwards

- What to add to `prep/practice/`:
- What to add to the MCQ sheet:
