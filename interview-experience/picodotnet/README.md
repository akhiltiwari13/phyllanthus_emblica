# picodotnet — DS & Algo set

Practice problems for the Pico interview. One self-testing executable per
question; `q00_template.cpp` is the shape every file follows.

Each solution carries **two implementations in one file** — `brute::solve` and
`optimal::solve` — cross-checked against the same expectation table in
`doTestsPass()`. That is deliberate. The naive version is what you say out loud
first, and keeping it compiled means the fast version has an oracle instead of
a hope.

```bash
# from the repo root, after conan install + cmake --preset conan-debug
cmake --build build/Debug --target q01_rectangle_path -j6
./build/Debug/interview-experience/picodotnet/q01_rectangle_path
```

| # | Problem | Brute | Optimal | Core technique |
|---|---------|-------|---------|----------------|
| [00](q00_template.cpp) | Maximum subarray sum | O(n²) | O(n) / O(1) | Kadane — running fold, drop a negative prefix |
| [01](q01_rectangle_path.cpp) | Does a walk trace a rectangle? | O(n log n) | O(n) / O(1) | Run-length collapse + geometric invariants |
| [02](q02_equal_sum_segments.cpp) | Most disjoint equal-sum pairs | O(n²) | O(n) | Bucket by key, interleaved greedy |

---

## How to think about these

A pattern runs through all three. It is worth naming, because it is the thing
being tested far more than any specific algorithm.

**1. Pin the problem statement down before writing code.** Both q01 and q02 are
stated ambiguously on purpose, and each has a plausible reading that is a
*different and much easier problem*:

| Problem | The easy misreading | Why it's wrong |
|---|---|---|
| q01 | "path returns to origin" | `UUDD` returns to origin and encloses nothing |
| q02 | "count the most frequent pair sum" | ignores disjointness; `[1,1,1]` gives 2, answer is 1 |

Getting this wrong costs the whole question, and no amount of clean code
recovers it. Ask, or state your assumption explicitly and move on.

**2. Write the brute force first, and say why it is too slow.** It is your
correctness oracle, and the interviewer wants to see the improvement *narrated*,
not conjured. Both optimal solutions here are one refactor away from the naive
one — not a different idea.

**3. Find the independence.** This is the actual lever in both problems:

- q02: segments with different sums *cannot interfere*, so the per-sum greedies
  are independent and can be interleaved into one sweep.
- q01: "is it closed" and "does it turn" are *independent* facts. Checking one
  and assuming the other is exactly how `UUDDLLRR` slips through.

**4. Enumerate the degenerate cases before you are asked.** Empty, one element,
everything equal, everything distinct, negatives, and integer overflow. The test
tables in these files are the checklist.

---

## Q01 — Does a walk trace a rectangle?

[`q01_rectangle_path.cpp`](q01_rectangle_path.cpp)

A robot starts at `(0,0)`. `U D L R` move it one unit. Return true iff the path
traced is the perimeter of a rectangle, walked exactly once.

```
"URDL"     -> true    unit square
"UURRDDLL" -> true    2x2 square
"UUDD"     -> false   returns to origin, encloses nothing
"UUDDLLRR" -> false   four straight runs, but they reverse instead of turning
```

### Stage 1 — brute force: geometry, no cleverness

Walk the path and record every unit edge crossed.

1. Any edge crossed twice → reject. A perimeter never doubles back.
2. Must end where it started.
3. Compute the bounding box of everything visited.
4. The set of edges walked must equal *exactly* the box's perimeter edges.

O(n log n) for the `std::set`, O(n) space. Slower and longer than the real
answer, but it is obviously correct — it is close to a literal transcription of
"the path is a rectangle". That is what makes it a trustworthy oracle.

### Stage 2 — the observation

Collapse the move string into **maximal straight runs**. `UUURDDDL` becomes
`U×3, R×1, D×3, L×1`. Each run is one side. A rectangle is then, exactly:

1. **Four** runs.
2. Adjacent runs **perpendicular** — they must *turn*, not reverse.
3. The loop **closes** (net displacement zero).

Condition 3 is what forces opposite sides to be equal, so there is nothing more
to check. Run lengths are ≥1 by construction, so zero area is impossible and
needs no special case.

### Why condition 2 is not free

This is the trap. Run-collapsing already guarantees adjacent runs *differ* — so
testing "different" costs nothing and catches nothing. `UUDDLLRR` is four runs,
all adjacent pairs differ, net displacement zero, and it is a line walked twice.
You need genuine perpendicularity: one run vertical, the next horizontal.

### The wrap-around case

`URRDDLLU` is a rectangle traced starting from the *middle of the left edge*.
Collapsing gives five runs, with the first and last both `U`. Because the path
is closed, those are one side split across the ends — merge them and you have
four. Hence the code allows a fifth run before bailing.

This is a judgement call, and it is flagged in the file: if the grader requires
the walk to begin at a **corner**, delete the merge and `URRDDLLU` is false.

### Complexity

O(n) time, O(1) space — the run list is capped at five entries, so the early
bail keeps it constant regardless of input length.

### A variant worth knowing

If the alphabet is `^ v < >` instead of `U D L R`, store each side as a
**displacement vector** rather than `(char, length)`. One dot product then
answers three separate questions, and the `is_vertical` helper disappears:

| Question | With `(char, length)` | With a vector |
|---|---|---|
| Continuing the current side? | `back.first == c` | `dot(back, s) > 0` |
| Do adjacent sides turn? | `is_vertical(a) == is_vertical(b)` | `dot(a, b) == 0` |
| Does the loop close? | decode, scale, accumulate | sides *are* displacements — just sum |

Shorter, and the three checks become one concept. The cost of `std::pair` for
the vector is that `.first`/`.second` say nothing where `.dx`/`.dy` read
themselves — which is why the committed version keeps the named `Step` struct.

---

## Q02 — Most disjoint equal-sum segments

[`q02_equal_sum_segments.cpp`](q02_equal_sum_segments.cpp)

A segment of length 2 is an adjacent pair `(A[i], A[i+1])`, identified by its
start `i`. Two segments are non-intersecting when their starts differ by ≥2.
Return the largest number of pairwise non-intersecting segments whose sums are
all equal.

```
[10, 1, 3, 1, 2, 2, 1, 0, 4] -> 3
     sum 4 occurs at starts 1, 2, 4, 7 — take 1, 4, 7
```

### Stage 1 — brute force

Collect the distinct pair sums. For each one, sweep left to right taking any
candidate whose start clears the last one taken by ≥2. Keep the best count.

O(n²) — with n = 10⁵ and all sums distinct, that is 10¹⁰ operations. It times
out, and that is the point of the question.

### Stage 2 — why greedy is correct

For a fixed sum, this is **interval scheduling** with fixed-width intervals.
Earliest-first is optimal: since every segment has the same width, taking the
leftmost candidate leaves a suffix that is a superset of what any other choice
leaves. Name the reduction and move on — it is a known result, not something to
re-derive at a whiteboard.

### Stage 3 — the O(n) insight

The outer loop over sums is the waste, and it is removable because **segments
with different sums can never block each other**. Their greedies are completely
independent.

So instead of running them one after another, run them *simultaneously*. Bucket
each start index by its pair sum, and give each bucket its own
`(count, last_start)`:

```
for i in 0 .. n-2:
    s = A[i] + A[i+1]
    if i >= bucket[s].last_start + 2:
        bucket[s].count += 1
        bucket[s].last_start = i
        best = max(best, bucket[s].count)
```

Every index is touched exactly once no matter how many distinct sums exist. The
per-sum greedies are all still running — they are just interleaved.

**O(n) time, O(n) space.** Measured at n = 10⁶ (`-O2`): ~14 ms when every pair
shares one sum, ~115 ms when all 10⁶ sums are distinct. The gap is hash-map
pressure, not an order of growth — from n = 5×10⁵ to n = 4×10⁶ the per-element
cost drifts only ~1.4× (123 → 157 µs per 1k elements) as the table outgrows
cache.

### Details that cost marks

- **`long long` for the sum.** `A[i] + A[i+1]` on two `INT_MAX`s is signed
  overflow — undefined behaviour. It is only ever a hash key, so widening is
  free. There is a test for exactly this.
- **`last_start = -2` sentinel** removes the "first candidate" special case:
  `i >= -2 + 2` is trivially true at `i = 0`.
- **Do not just count frequencies.** `[1,1,1]` has sum 2 twice, but the two
  candidates overlap, so the answer is 1.

---

## Techniques used across the set

| Technique | Where | What to recognise |
|---|---|---|
| Run-length collapse | q01 | Consecutive identical states are one logical unit — compress, then reason about the compressed sequence |
| Geometric invariants | q01 | Replace "simulate and compare shapes" with a small set of necessary-and-sufficient conditions |
| Brute force as oracle | q01, q02 | Keep the naive version compiled and cross-check it; it costs a few lines and buys real confidence |
| Interval scheduling / greedy | q02 | Fixed-width non-overlapping selection → earliest-first is provably optimal |
| Bucket by key | q02 | Independent sub-problems keyed by a value → hash map of per-key state |
| Loop inversion | q02 | "For each key, scan the data" → "scan the data once, advance every key" — the O(n²) → O(n) move |
| Single-pass / O(1) state | q00, q01, q02 | Touch each element once, carry constant state — the shape every streaming system wants |
| Widening to avoid overflow | q00, q02 | `int + int` and `n × INT_MAX` do not fit in `int` |

The last three are the recurring Pico angle: a feed handler sees each tick once
and cannot rewind, so O(1) state per element is the *requirement*, not an
optimisation.

---

## Adding a question

1. Copy `q00_template.cpp` → `qNN_<name>.cpp`.
2. Keep both `brute::solve` and `optimal::solve`, cross-checked in `doTestsPass()`.
3. Fill in the `PROBLEM` / `APPROACH` header and the `INTERVIEW NOTES` footer —
   the notes are the part worth re-reading before a screen.
4. Add `add_executable(qNN_<name> qNN_<name>.cpp)` to `CMakeLists.txt`.
5. Add a row to the table at the top of this file.

Builds with `-Wall -Wextra -Wpedantic -Werror`; warnings are errors, so fix them
rather than working around them.
