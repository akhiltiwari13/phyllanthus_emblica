# Millennium: Market Data Real-Time Developer (Hong Kong, Equity IT): prep plan

Working sheet for the October 2026 loop. Work through it over the days before round 1,
ticking boxes as you go. Earlier Millennium test notes are in [README.md](README.md).

## The process

| Stage | Format | Notes |
| --- | --- | --- |
| Round 1 | 45 min, Webex + live HackerRank code pairing | Background chat, then live coding. Interviewer is UK-based. |
| Rounds 2-3+ | At least two more rounds | At least one face-to-face at the Hong Kong office. |
| Caliper | Online assessment | Behavioural traits + mathematical reasoning. |

Round 1 shape (expected):

| Minutes | Content |
| --- | --- |
| ~10 | Background. Lead with market data: order books, feed handlers, replay, multicast. |
| ~25-30 | Live coding, C++. Talk through the approach, write it, then test edge cases aloud. |
| ~5 | Your questions. |

## Day-by-day plan

- [ ] **Thu 15:** C++ refresh (memory model, move semantics, containers). Code the order book from scratch twice.
- [ ] **Fri 16:** networking and the market-data pipeline. Sketch the ticker-plant design out loud.
- [ ] **Sat 17:** 4 timed HackerRank mediums in C++. Redo the big-endian parser below.
- [ ] **Sun 18:** 4 more timed mediums. One mock interview. Caliper-style numerical practice.
- [ ] **Mon 19, morning:** reread the four headline stories, test Webex + HackerRank setup. Stop studying 2 hours before.

## 1. Live coding

Work these against the clock. Ones already in this repo are linked; build them with `-j 6`.

| Problem | Where | Target |
| --- | --- | --- |
| [ ] Order book: add / modify / delete, best bid/ask, depth at N levels | [prep/practice/order_book.cpp](../../prep/practice/order_book.cpp) | 35 min |
| [ ] A/B feed arbitration, sequence gaps, reorder buffer | [prep/practice/feed_arbitrator.cpp](../../prep/practice/feed_arbitrator.cpp) | 30 min |
| [ ] **Big-endian binary market-data parser** (`bswap32/64`, `#pragma pack`, ignore trades, process quotes) | Previous Millennium test, see [README.md](README.md). Rewrite from scratch; the old [ticker_parser.cpp](ticker_parser.cpp) passed 6/13 | 35 min |
| [ ] Ring buffer / SPSC queue | [extras/circ_buff.cpp](../../extras/circ_buff.cpp) | 25 min |
| [ ] LRU cache | [prep/practice/lru_cache.cpp](../../prep/practice/lru_cache.cpp) | 25 min |
| [ ] Fixed-size object pool | [prep/practice/object_pool.cpp](../../prep/practice/object_pool.cpp) | 35 min |
| [ ] Fixed-point price arithmetic | [prep/practice/fixed_point_price.cpp](../../prep/practice/fixed_point_price.cpp) | 30 min |
| [ ] Merge k sorted feeds by sequence number / timestamp | new | 25 min |
| [ ] VWAP / moving average over a sliding time window | new | 25 min |
| [ ] Top-K most-traded symbols from a stream | new | 20 min |
| [ ] Big-integer addition on strings (reported in a Millennium C++ phone screen) | new | 15 min |

On the day: copy [prep/templates/q00_template.cpp](../../prep/templates/q00_template.cpp),
put the given examples into the tests **before** implementing, and say the complexity out loud.

Parser checklist (the previous test's traps):

- [ ] Read the stream chunk by chunk; a message can straddle two chunks.
- [ ] `#pragma pack(push, 1)` structs, or `memcpy` field by field; never cast an unaligned pointer.
- [ ] Convert with `__builtin_bswap32/64` (or `std::byteswap` in C++23) after `memcpy`.
- [ ] Skip unwanted message types by their length field, not by guessing.
- [ ] Match the output format exactly (precision, separators, trailing newline).

## 2. C++ questions

Revision sheet: [prep/mcq/low_latency_cpp.md](../../prep/mcq/low_latency_cpp.md).

- [ ] Move semantics, rule of 0/3/5, when the compiler stops generating moves.
- [ ] Virtual dispatch (vtable cost, devirtualisation) vs CRTP / templates.
- [ ] `constexpr`, `consteval`, templates vs concepts.
- [ ] `std::atomic` and memory ordering: relaxed, acquire/release, seq_cst. Write an SPSC queue with acquire/release and explain why it is correct.
- [ ] False sharing, cache lines, `alignas(64)`, `std::hardware_destructive_interference_size`.
- [ ] Allocation on the hot path: pools, arenas, `reserve`, small-buffer optimisation.
- [ ] `std::map` vs `unordered_map` vs flat / array-indexed maps for a price ladder.
- [ ] `std::vector` growth, iterator invalidation.
- [ ] Undefined behaviour: strict aliasing, signed overflow, unaligned access.

## 3. Linux and networking

- [ ] UDP multicast, IGMP join, why market data is multicast.
- [ ] A/B line arbitration; snapshot + incremental recovery; retransmission requests.
- [ ] Packet path from NIC to user space; where the latency goes.
- [ ] Kernel bypass: OpenOnload / ef_vi, DPDK, ExaNIC. When it is worth it.
- [ ] CPU pinning, `isolcpus`, IRQ affinity, NUMA, huge pages, busy-polling vs `epoll`.
- [ ] Hardware timestamps, PTP clock sync, measuring tick-to-trade.

## 4. Market-data domain

- [ ] Feed handler → normaliser → book builder → distribution.
- [ ] Gap detection and recovery; stale-data detection; sequence numbers per channel.
- [ ] Conflation for slow consumers.
- [ ] Capture and replay for debugging and back-testing.
- [ ] HKEX OMD-C (securities market data) at a high level; Hong Kong equities market hours and auctions.

## 5. System design (later rounds)

**"Design a ticker plant."** Practise out loud, 30 minutes:

1. Requirements: venues, symbols, consumers, latency budget, recovery guarantees.
2. Exchange feed handlers (A/B arbitration, gap recovery).
3. Normalisation to an internal format.
4. Book building per symbol; level vs order-by-order books.
5. Distribution: shared memory / multicast, conflation for slow consumers.
6. Capture + replay; monitoring; latency measurement at each hop.
7. Failure modes: feed down, gap storm, consumer lag, clock drift.

## 6. Stories to have ready

| Story | Use for |
| --- | --- |
| QuompTX order book: ~64ns updates, ~50ns level access, ~70ns top-of-book inserts; how it was measured | Latency, data structures |
| Edelweiss market-data simulator: zstd-compressed capture, streaming replay | Replay, testing |
| Edelweiss `.pcap` latency profiler | Measurement |
| Gemini: packet loss and sync issues in production; UltraMessaging multicast reliability | Incident ownership, networking |
| Alkimi: WebSocket staleness detection with REST fallback | Stale data, failure handling |
| AlgoQuant: next-gen platform while keeping the legacy one in production | Priorities, trade-offs |

Behavioural: why Millennium, why Hong Kong, why the job moves (each move widened the view
of trading tech: sell-side → buy-side → exchange → crypto → platform lead), Quomptrade.

## 7. Caliper

- [ ] One practice personality questionnaire: answer consistently, not "ideally".
- [ ] Numerical reasoning: number series, ratios, percentages, quick mental arithmetic. One timed set the evening before.

## 8. Questions to ask the interviewer

- Which venues and feeds does the team own, and is it per-region or global?
- How is latency measured and budgeted across the ticker plant?
- How do strategies consume data: shared memory, multicast, a library?
- What does a typical week look like: new feeds, latency work, production support?
- How is on-call / production support split across Hong Kong, London and New York?

## Log

| Date | Done | Notes |
| --- | --- | --- |
| | | |
