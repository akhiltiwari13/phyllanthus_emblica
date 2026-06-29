# Phyllanthus Emblica  <img align="center" width="75" height="75" src="problems/logo/logo.ico" >


## Brief:
> Collection of interview questions and coding assignments. The Author strongly **discourages plagarism**. The solutions are implemented in C++ and *tries to conform to [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## Build Instruction:
> This project uses [Conan 2.x](https://conan.io/) for dependency management and CMake (3.30+) presets to build. Dependencies are declared in `conanfile.py`.
> 1.  Install dependencies and generate the CMake preset (pick a profile from `conan/conan-profiles/`):
>     ```bash
>     conan install . --profile=conan/conan-profiles/debug-omarchy-x86-gcc --build=missing
>     ```
> 2.  Configure with the Conan-generated preset:
>     ```bash
>     cmake --preset conan-debug
>     ```
> 3.  Build (capped at 6 jobs):
>     ```bash
>     cmake --build build/Debug -j 6
>     ```

## Problems:
- ### [Goldman Sachs](https://www.goldmansachs.com/) 
    > The problem is to find the root node of the largest tree (with the largest number of nodes) in a forest. [Solution](interview-experience/goldman_sachs/largestTreeinForest.cpp) 

- ### [Optiver](https://www.optiver.com/) 
    > The problems had hidden testcases which had to be passed. 
    1. [optv1a](problems/optiver/code_graph_traversal0.png)
    2. [optv1b](problems/optiver/code_graph_traversal1.png)
    3. [optv1c](problems/optiver/code_graph_traversal2.png)
    4. [optv1d](problems/optiver/code_graph_traversal3.png)
        - [solution](interview-experience/optiver/graph_traversal.cpp)

- ### [jumpTrading](https://www.jumptrading.com/) 
    > The problem is to implement a file parser that stores only  integral data from the file. [Solution](interview-experience/jump_trading/TextParser.cpp) 

- ### [Tower Research Capital](https://www.tower-research.com/) 
    > Following is a collection of set of problems encountered during TRC's interviews.
    1. [trc_1a](problems/trc/market_parser/14_MarketDataParsing.jpeg)
    2. [trc_1b](problems/trc/market_parser/14_MarketDataParsing2.jpeg)
    3. [trc_1c](problems/trc/market_parser/14_MarketDataParsing3.jpeg)
        - [solution](interview-experience/tower_research_capital/order_trade_feed_parser.cpp)

    5. [trc_2a](problems/trc/road_network/10RoadNetwork01.png)
    6. [trc_2b](problems/trc/road_network/10RoadNetwork02.png)
        - [solution](interview-experience/tower_research_capital/road_network.cpp)

- ### [Amazon](https://www.amazon.com/) 
    > These problems were encountered in amazon's interview process for the role of software developer in their embedded software-dev team.
    1. [solutions](interview-experience/amazon_embedded/) (`OrderBatchSerializer.cpp`, `deserializer.cpp`, `orderbatch.cpp`)

- ### [IMC](https://www.imc.com/ap/) 
    > IMC's introductory assignment.
    1. [assignment](problems/imc/imc_cpp_asgnmt.pdf)
        - [solution](interview-experience/imc/README.md)

- ### [Ogha](http://www.ogha-research.in) 
    > ogha-research's introductory assignment.
    1. [assignment](problems/ogha/ogha_assignment.pdf)
        - [solution](interview-experience/ogha/README.md)

- ### [Squarepoint Capital](https://squarepoint-capital.com) 
    > sqpc's 2nd attempt.
    
    2. [problem](problems/squarepoint-capital/sqpc2.png)
        - [solution](interview-experience/squarepoint-capital/accumulator.cpp)


- ### Miscellaneous
    > This directory has problems from various other interviews. 
    1. [misc1](interview-experience/miscellaneous/find_scrambled.cpp)

- ### [LHFT's](https://www.lhft.io/) [problem statement](interview-experience/lhft/problem_statement.md) 
[Solution](interview-experience/lhft/main.cpp) 

- ### [Greenland Investment management's](https://www.lhft.io/) introductory assignment problems  
    > Collection of assignment problems. [solutions](interview-experience/greenland_investment_mgmt/)

## Additional solutions:
> The following companies/assignments also have solutions under `interview-experience/`:
- [aargo_trade](interview-experience/aargo_trade/main.cpp)
- [edgeverve](interview-experience/edgeverve/suffixQueries.cpp)
- [factomind](interview-experience/factomind/README.md)
- [falconx](interview-experience/falconx/README.md)
- [flipkart](interview-experience/flipkart/AdvertisementCappingSystem/)
- [fractal_prot](interview-experience/fractal_prot/lenCalc.py)
- [futurefirst](interview-experience/futurefirst/README.md)
- [hsbc](interview-experience/hsbc/main.cpp)
- [jpmc](interview-experience/jpmc/jpmctest.cpp)
- [jstreet](interview-experience/jstreet/main.cpp)
- [millenium](interview-experience/millenium/README.md)
- [qnance](interview-experience/qnance/README.md)
- [standard_chartered](interview-experience/standard_chartered/solve.cpp)
- [trading_technologies](interview-experience/trading_technologies/main.cpp)
- [turing](interview-experience/turing/open_cv_basic.py)
- [worldquant](interview-experience/worldquant/target1.cpp)


