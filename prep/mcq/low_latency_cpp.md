# Low-latency C++ — MCQ revision

Aimed at trading-platform screens (order gateway, risk, market data). Each entry is
**the claim → why → the answer that looks right and isn't**. The trap column is the
point: MCQ distractors are built out of half-remembered rules.

Numbers are order-of-magnitude on a modern x86 server, for calibration only.

---

## 1. Memory hierarchy

| | |
| --- | --- |
| **Claim** | L1 ~1 ns (4-5 cycles), L2 ~4 ns, L3 ~15-40 ns, DRAM ~80-100 ns, NVMe ~50-100 µs. |
| **Why** | Every level is roughly an order of magnitude out from the last. A DRAM miss on the hot path costs more than the rest of the tick logic combined. |
| **Trap** | Being asked for "the cost of a cache miss" and answering with the *L1* latency. The miss cost is the latency of the level that eventually serves it. |

**Cache line = 64 bytes** on x86-64 (128 on Apple M-series, and some ARM). Nearly every
cache question reduces to this number.

- **Spatial locality**: a `struct` smaller than a line costs one fetch; straddling a
  boundary costs two.
- **Prefetcher**: hardware detects *linear* strides. A linked list defeats it — that is
  why `std::vector` beats `std::list` in traversal even when big-O says otherwise.
- **`std::vector` vs `std::list` for iterate-and-sum**: vector wins, always, at every
  size that matters. `list` needs a pointer chase per element and one allocation per node.

### False sharing

Two threads writing to *different* variables that share one cache line. The line
ping-pongs between cores (MESI invalidation) and both threads stall, with no data race
and no incorrect result — just a collapse in throughput.

```cpp
struct Counters {                     // BAD: both counters in one line
  std::atomic<uint64_t> produced;
  std::atomic<uint64_t> consumed;
};

struct Counters {                     // GOOD: one line each
  alignas(64) std::atomic<uint64_t> produced;
  alignas(64) std::atomic<uint64_t> consumed;
};
```

`std::hardware_destructive_interference_size` is the portable spelling of that 64.

| **Trap** | Calling false sharing a *race*. It is purely a performance effect; the program is correct either way. |

---

## 2. Branches

- Mispredict cost: **~15-20 cycles** (pipeline flush and refill).
- The predictor is very good at *consistent* branches, and useless on random ones. A
  branch that is 99 % one way is nearly free; a 50/50 branch is a mispredict half the time.
- **Branchless** alternatives — `std::min`, arithmetic masking, `cmov` — pay off only when
  the branch is genuinely unpredictable. On a predictable branch, branchless code is
  *slower*, because it always evaluates both sides.
- `[[likely]]` / `[[unlikely]]` (C++20) hint at layout, keeping the hot path contiguous in
  the instruction cache. They do not override the hardware predictor.

| **Trap** | "Branchless is always faster." It is not; it removes a mispredict you may not be paying for. |

---

## 3. Atomics and memory ordering

| Order | Guarantee |
| --- | --- |
| `relaxed` | Atomicity only. No ordering with respect to any other variable. Fine for a statistics counter. |
| `acquire` (loads) | Nothing later in program order moves before it. |
| `release` (stores) | Nothing earlier in program order moves after it. |
| `acq_rel` | Both, for read-modify-write. |
| `seq_cst` | Additionally a single total order across all `seq_cst` operations. The default. |

**Acquire and release pair.** A release store publishes; an acquire load on *that same
variable* observes everything the releasing thread did beforehand. One without the other
guarantees nothing.

```cpp
// producer                          // consumer
data = 42;                           if (ready.load(memory_order_acquire))
ready.store(true, release);              use(data);   // 42 is guaranteed visible
```

- On **x86** `acquire`/`release` are free — the hardware is already TSO; only `seq_cst`
  stores emit a fence (`xchg`/`mfence`). On **ARM/POWER** they emit real barriers. So
  "relaxed is faster" is often unmeasurable on x86 and very measurable on ARM.
- `volatile` is **not** an atomic and **not** a barrier. It means "do not optimise this
  access away" — for memory-mapped I/O and signal handlers, not for threads.
- `std::atomic<T>::is_lock_free()` — types wider than the machine's CAS lock a mutex
  internally. `atomic<T>` on a big struct is not automatically fast.
- **`std::atomic_flag` is the only type guaranteed lock-free** on every implementation.

| **Trap** | "`seq_cst` is needed for correctness." Usually acquire/release suffices; `seq_cst` is the safe default, not the required one. |
| **Trap** | Answering that `volatile` makes a variable thread-safe. It never has. |

---

## 4. Dispatch, inlining, and templates

- **Virtual call** = load vptr → load vtable slot → indirect call. ~2-3 ns when the target
  is predicted, far worse when megamorphic, and the compiler generally **cannot inline it**.
  The lost inlining usually costs more than the indirect jump.
- **CRTP** (static polymorphism) resolves at compile time, inlines, and costs nothing —
  at the price of losing a common base type and of code bloat per instantiation.
- **Devirtualisation** happens when the dynamic type is provable (`final`, or a local
  object). Marking a class or method `final` genuinely helps the optimiser.
- `std::function` type-erases: it may heap-allocate for a large capture (small-buffer
  optimised for small ones) and it costs an indirect call. A template parameter or a
  lambda passed directly does not.
- **Templates**: zero runtime cost, paid for in compile time and binary size.

| **Trap** | "Virtual calls are slow because of the vtable lookup." The lookup is cheap; the missed inlining and the indirect-branch mispredict are the real cost. |

---

## 5. Allocation

- `new`/`malloc` on the hot path is the classic latency bug: it can take a lock, and it can
  fault a page in. Cost varies from ~20 ns to microseconds — the *tail* is the problem.
- **Fixes**: preallocate; object pools / free lists; arena or bump allocators; `reserve()`
  before a loop; small-buffer optimisation.
- **Placement `new`** constructs into storage you already own — `::new (ptr) T(args)` — and
  you must then call `p->~T()` by hand. This is what an object pool is built on.
- `std::vector::reserve` prevents reallocation; `shrink_to_fit` is a non-binding request.
- **SSO**: `std::string` stores ~15 chars inline (libstdc++) with no allocation. Longer
  strings allocate. `std::string_view` never owns and never allocates — but never outlive
  the buffer it points at.
- A `noexcept` move constructor lets `vector` *move* on reallocation instead of *copying*.
  Without it, `vector` copies, for exception safety. Marking moves `noexcept` is free
  performance.

| **Trap** | "Object pools avoid allocation." They avoid it *on the hot path* — the pool itself allocates once, up front. |

---

## 6. Casts and RTTI

- `static_cast` — compile time, free.
- `reinterpret_cast` — free, and a promise you had better be able to keep. Type-punning
  through it breaks strict aliasing; use `std::bit_cast` (C++20) or `memcpy`.
- `dynamic_cast` — **runtime**, walks the RTTI hierarchy, can cost 50-100+ ns. Never on a
  hot path. On a class hierarchy, a virtual method or a tag field beats it.
- `const_cast` — free; *writing* through it to an originally-`const` object is UB.

---

## 7. Networking

| | TCP | UDP |
| --- | --- | --- |
| Delivery | Ordered, reliable, retransmitted | Unordered, lossy, no retransmit |
| Connection | Handshake, per-peer state | None |
| Multicast | No | Yes |
| Latency | Higher, and jittery under loss | Lower, predictable |

- Market data is **UDP multicast**: one send reaches every subscriber, and a retransmit of
  stale prices is worthless anyway. Order entry is **TCP**: you must not lose an order.
- **Sequence gaps**: multicast messages are sequenced by the exchange. A gap means loss.
  Handled by an **A/B feed** — the same stream on two groups, arbitrated by sequence number
  (see `prep/practice/feed_arbitrator.cpp`) — with a recovery/retransmit channel as backup.
- **Nagle's algorithm** coalesces small writes, adding up to ~40 ms of delay. `TCP_NODELAY`
  disables it, and every trading connection sets it.
- **Delayed ACK** interacts pathologically with Nagle; that pairing is the classic
  40 ms mystery stall.
- **Kernel bypass** (Solarflare/Onload, DPDK, RDMA) maps the NIC into user space,
  eliminating syscalls, context switches and a copy: ~10 µs down to ~1-2 µs.
- **Busy-poll vs interrupt**: spinning on the NIC burns a whole core and removes both
  interrupt and wake-up latency. Standard in HFT, indefensible anywhere else.
- **`epoll` vs `select`**: `select` is O(n) in watched descriptors and capped at
  `FD_SETSIZE`; `epoll` is O(1) in ready descriptors. `epoll` is level-triggered by default;
  edge-triggered (`EPOLLET`) requires draining until `EAGAIN`.

| **Trap** | "TCP is slower than UDP." Only under loss and small writes. On a clean LAN with `TCP_NODELAY` the difference is small — the real reasons for UDP are multicast and the absence of head-of-line blocking. |

---

## 8. Concurrency

- **Lock-free ≠ wait-free.** Lock-free: *some* thread makes progress. Wait-free: *every*
  thread completes in a bounded number of steps. Wait-free is strictly stronger.
- An **SPSC ring buffer** needs no CAS at all — one atomic index per side, release on
  publish, acquire on consume. This is the queue to reach for first.
- **MPMC** needs CAS, and CAS contention degrades badly with thread count.
- **ABA problem**: a CAS succeeds because the value came back to A, while the world moved
  A→B→A underneath. Fixed with a tagged/versioned pointer or hazard pointers.
- An **uncontended** mutex is cheap (~20 ns, futex, no syscall). A **contended** one is a
  syscall and a context switch (~1-10 µs). "Mutexes are slow" is only true under contention.
- **Spinlock** wins for very short critical sections on distinct cores; it is a disaster if
  the holder is descheduled. Use `_mm_pause()` / `std::this_thread::yield()` in the spin.
- **Context switch** ~1-5 µs, plus the cache and TLB it leaves cold.
- **Thread pinning** (`taskset`, `sched_setaffinity`) keeps a hot thread's cache warm and
  is standard practice; isolate the core (`isolcpus`, `nohz_full`) to keep the scheduler off it.

---

## 9. Compiler and build

- `-O2` vs `-O3`: `-O3` adds aggressive inlining and vectorisation. It can be *slower* —
  bigger code, more i-cache pressure. Measure; do not assume.
- `-march=native` unlocks AVX-512 etc., and produces a binary that will crash on an older CPU.
- **LTO** allows inlining across translation units; usually the largest single win after `-O2`.
- **PGO** typically beats LTO for branch-heavy code, at the cost of a profiling run.
- `-ffast-math` breaks IEEE semantics (NaN, denormals, reassociation). Never in pricing code.
- **RVO/NRVO**: returning a local by value does not copy. Since C++17 RVO for a prvalue is
  *mandatory*. `return std::move(local);` **defeats NRVO** — it is a pessimisation, and one
  of the most common MCQ answers people get backwards.

| **Trap** | "Return `std::move(x)` to avoid a copy." It prevents the copy elision that was already going to happen. |

---

## 10. Measurement

- `rdtsc` is a cycle counter, not a clock: it needs serialising (`rdtscp`/`lfence`) and is
  affected by frequency scaling — though modern CPUs have an invariant TSC.
- `std::chrono::steady_clock` for durations (monotonic); `system_clock` for wall time (can
  jump backwards). Timing anything with `system_clock` is a bug.
- Report **percentiles**, never the mean. p50/p99/p99.9 is the standard; latency
  distributions are long-tailed and a mean hides exactly what you care about.
- **Coordinated omission**: measuring only what the system managed to serve, so the slow
  requests never enter the sample. This is *the* benchmark trap.
- Warm up before measuring: cold cache, cold branch predictor, lazy page faults, and
  (for JITs) unoptimised code all distort the first samples.

---

## Rapid fire

| Question | Answer |
| --- | --- |
| Cache line size, x86-64 | 64 bytes |
| Cost of an L1 hit | ~1 ns / 4-5 cycles |
| Cost of a DRAM access | ~80-100 ns |
| Branch mispredict | ~15-20 cycles |
| Uncontended mutex | ~20 ns |
| Context switch | ~1-5 µs |
| Syscall | ~50-100 ns (post-Spectre mitigations, more) |
| Only guaranteed lock-free type | `std::atomic_flag` |
| Disables Nagle | `TCP_NODELAY` |
| `std::list` node cost | one allocation, plus a pointer chase that beats the prefetcher |
| `vector` growth factor | typically 2× (libstdc++), 1.5× (MSVC) — amortised O(1) |
| `unordered_map` worst case | O(n) per lookup on collisions; iteration order unspecified |
| `map` vs `unordered_map` | `map` O(log n) ordered, better cache behaviour when small; `unordered_map` O(1) average |
| Erasing from a `vector` invalidates | every iterator from the erase point on; reallocation invalidates all |
| Erasing from a `list`/`map` invalidates | only the iterator to the erased element |
