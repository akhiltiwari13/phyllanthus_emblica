# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

"Phyllanthus Emblica" — a collection of HFT/Quant interview problems and library experiments in C++23. It is **not** a single application: it is many independent single-file programs, each compiled to its own executable. There is no shared library, no central entry point, and no cross-module dependency graph to learn.

`AGENTS.md` holds the detailed coding-style guide (naming, includes, Doxygen headers, error handling). Read it before writing source; this file covers build/architecture only.

## Environment (this machine: omarchy / Arch, ThinkPad E14)

- **Always cap build parallelism at 6 jobs.** Using all 22 cores freezes this machine. Pass `-j 6` (or `--parallel 6`) to every `cmake --build`.
- This host is omarchy x86 — prefer the `*-omarchy-*` Conan profiles (gcc 15 / clang 21), not the `fedora`/`mac` ones referenced in `AGENTS.md`.

## Build workflow

Conan 2.x provides dependencies and generates the CMake preset; CMake (3.30+) drives the build. In-source builds are blocked by the root `CMakeLists.txt`.

```bash
# 1. Install deps + generate preset (GCC). Use the clang profile to build with clang/libc++.
conan install . --profile=conan/conan-profiles/debug-omarchy-x86-gcc --build=missing

# 2. Configure (preset comes from conan-generated CMakePresets.json, pulled in via CMakeUserPresets.json)
cmake --preset conan-debug

# 3. Build everything — ALWAYS -j 6 on this machine
cmake --build build/Debug -j 6

# Build / run one target (faster iteration than building all)
cmake --build build/Debug -j 6 --target forest
./build/Debug/interview-experience/goldman_sachs/forest
```

Use `default-omarchy-*` profiles + `--preset conan-release` for Release (LTO is auto-enabled when the toolchain supports IPO).

## Architecture / how targets are wired

- Root `CMakeLists.txt` sets C++23, `-Wall -Wextra -Wpedantic -Werror` (warnings are errors), and adds three subtrees: `interview-experience/`, `playground/`, `extras/`.
- Each leaf directory has its own `CMakeLists.txt` declaring `add_executable(...)` targets, usually one `.cpp` → one binary. Boost/fmt/etc. are linked per-target via `find_package` + `target_link_libraries`.
- **Targets only build if their subdirectory is registered in the parent `CMakeLists.txt`.** Many `add_subdirectory(...)` / `add_executable(...)` lines are commented out (e.g. `lhft`, `amazon_embedded`, `factomind`, several boost experiments). Enabling a problem = uncommenting/adding its line, not just adding files.
- `buinftech/` and `interview-experience/<company>/` may carry their own `conanfile.py` for isolated experiments; the root `conanfile.py` is the one that backs the normal build.

## Where things live

- `interview-experience/<company>/` — interview solutions, grouped by firm (goldman_sachs, jump_trading, imc, jpmc, greenland_investment_mgmt, …).
- `playground/` & `playground/playground_extra/` — library spikes (boost asio/ipc/ptree, fmt, spdlog, folly, cereal, capnproto, tracy, yaml, nlohmann).
- `extras/` — loose snippets and latency/cache experiments.
- `conan/conan-profiles/` — per OS/compiler Conan settings.

## Testing

No test framework wiring is in active use. Most solutions self-verify with an inline `doTestsPass()` that `main()` runs and prints `ALL TESTS PASS.` / `TESTS FAILED.`. gtest and google-benchmark are available via Conan but largely unused. "Run the tests" for a problem = build its target and execute the binary.
