# Image triage worklist

Restored from a backup and committed **as-is** so nothing could be lost to a `git clean`.
Verified against `git log --all`: most of these have never been in git history before.
This file is the worklist for the follow-up commit that renames them and moves problem
statements under `problems/<company>/`, which is their canonical home per `AGENTS.md`.

## 1. Exact duplicates of files already under `problems/` (13, md5-identical)

Delete the `interview-experience/` copy; keep `problems/` as canonical.

| Copy in `interview-experience/` | Already in `problems/` |
| --- | --- |
| `optiver/code_graph_traversal0.png` | `problems/optiver/code_graph_traversal0.png` |
| `optiver/code_graph_traversal1.png` | `problems/optiver/code_graph_traversal1.png` |
| `optiver/code_graph_traversal2.png` | `problems/optiver/code_graph_traversal2.png` |
| `optiver/code_graph_traversal3.png` | `problems/optiver/code_graph_traversal3.png` |
| `squarepoint-capital/Screenshot from 2021-06-21 16-39-38.png` | `problems/squarepoint-capital/` same name |
| `squarepoint-capital/Screenshot from 2021-06-21 16-39-40.png` | `problems/squarepoint-capital/` same name |
| `squarepoint-capital/Screenshot from 2021-06-21 17-30-08.png` | `problems/squarepoint-capital/` same name |
| `squarepoint-capital/Screenshot from 2021-06-21 17-30-19.png` | `problems/squarepoint-capital/` same name |
| `tower_research_capital/attempt_3_may2021/10RoadNetwork02.png` | `problems/trc/road_network/10RoadNetwork01.png` |
| `tower_research_capital/attempt_3_may2021/10RoadNetwork03.png` | `problems/trc/road_network/10RoadNetwork02.png` |
| `tower_research_capital/problem_snap/14_MarketDataParsing.jpeg` | `problems/trc/market_parser/14_MarketDataParsing.jpeg` |
| `tower_research_capital/problem_snap/14_MarketDataParsing2.jpeg` | `problems/trc/market_parser/14_MarketDataParsing2.jpeg` |
| `tower_research_capital/problem_snap/14_MarketDataParsing3.jpeg` | `problems/trc/market_parser/14_MarketDataParsing3.jpeg` |

Note `squarepoint-capital/Screenshot from 2021-06-21 16-39-21.png` is **not** a duplicate
despite `problems/squarepoint-capital/` holding a file of the same name — the bytes differ.
Compare both before touching either.

## 2. Images whose solution file is known — just needs linking in `README.md`

| Images | Solution |
| --- | --- |
| `goldman_sachs/cpad_1/gs_largestForest{0,1,2}.png` | `interview-experience/goldman_sachs/largestTreeinForest.cpp` |
| `jump_trading/Jump1_{1,2}.png` | `interview-experience/jump_trading/TextParser.cpp` |
| `optiver/code_graph_traversal*.png` | `interview-experience/optiver/graph_traversal.cpp` |
| `tower_research_capital/problem_snap/14_MarketDataParsing*.jpeg` | `interview-experience/tower_research_capital/order_trade_feed_parser.cpp` |
| `tower_research_capital/attempt_3_may2021/10RoadNetwork*.png` | `interview-experience/tower_research_capital/road_network.cpp` |
| `flipkart/capping_system_problem_statement/*.png` | `interview-experience/flipkart/AdvertisementCappingSystem/` |

## 3. Images with **no** solution file yet — unsolved problems

These are the real backlog. Each needs a `.cpp` written and a CMake target.

- `maven_securities/*` — 11 images, **no** solution, **no** `CMakeLists.txt`, dir not registered
  in `interview-experience/CMakeLists.txt`. Two problems (`Maven1_*`, `Maven2_*`) plus
  `maven_questions.png`.
- `optiver/code_roman_number_sorting{0,1,2,4}.png` — roman-numeral sorting, unsolved.
  (Note the gap: there is no `...3.png`.)
- `optiver/mcq_time_complexity_problem.png`, `instructions.png`, `problem_set.png` — test context.
- `goldman_sachs/cpad_2/Screenshot from 2021-06-08 *.png` — 3 images, contents unidentified.
- `goldman_sachs/document.pdf` — unidentified.
- `miscellaneous/ion_stringConstruction.png` — ION, string construction. Unsolved.
- `miscellaneous/opent_numWithout5.png` — numbers without digit 5. Unsolved.
- `tower_research_capital/attempt_2_may2021/*` — bug-fix style problems
  (`trc_1fixTaxicab`, `trc_3fixIncrementByOne`, `trc_4fixOddNodesSum`, `trc_5fixPossibleParams`,
  `trc_6fixCountingSort`, `trc6_fixCuriousPointers`, `trc7_descReliableMulitcast`) — unsolved.
- `tower_research_capital/attempt_3_may2021/` — `08trwExchange*`, `09MinMaxGridDP*`,
  `11CovidOutbreak*` unsolved; `theoretical/*` are MCQ-style (memory bandwidth, UDP, processes,
  STL containers, array bugs) — good MCQ revision material, see `prep/mcq/`.
- `docs/ARM MCQs.pdf`, `docs/ASSIGNMENT-SOLUTION-WEEK1.pdf` — unrelated to interviews, from 2021.

## 4. Misfiled

- `interview-experience/JDs/*.docx` are **Squarepoint Capital** job descriptions (confirmed by
  extracting the docx text — "Squarepoint is a global investment management firm…"), despite the
  generic `JDs/` name. They belong under `interview-experience/squarepoint-capital/JDs/`.

## 5. Pre-existing duplication — flagged, not fixed here

Already in git, unrelated to this restore: `problems/interview snaps/snaps/` and
`problems/job-interviews/snaps/` are byte-identical trees. Deduping them is a separate decision.
