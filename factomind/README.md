# factomind's assignment

problem statement: [assignment](https://factec.notion.site/Coding-Assignment-9ca9538c97ae4d5f85e7afc9cbcb7c78)

## Project Description

### Introduction
The objective of this program is to create a simulator that calculates the history of holding positions for various portfolio trading algorithms provided by the user. The program will read input data in the form of a CSV file, iterate calculations to generate positions, and write the output data in CSV format. The trading algorithms, referred to as trading algo codes, will be implemented by the user and loaded dynamically at runtime.
Given the nature and complexity of this project it utilizes some mainstream, opensourced 3rd party C++ libraries. It has been build & tested on an ARM-64 architecture machine running a MacOS(I believe this should work on most *NIX systems, given the project dependencies are satisfied). I have tried to account for any edge-cases that I could think off and would like to apologise in advance for any oversight that may have happened.

### Program Design Document

#### Application Flow
   The Application follows the following flow:
   - Reads the configuration file.
   - Reads the input data from a CSV file.
   - Iterates the data to generate positions for each time point for each strategy as specified in the config.yaml.
   - Writes the output data to a CSV file.

#### Input Data
   - The input data is a time-series data for each stock given in the form of a CSV file.
   - The shape of the array is T x N, where T is the number of time points and N is the total number of stocks.

#### Output Data
   - The output data will have the same shape as the input data, representing the amount of stock held for each stock at each time point.
   - The time points and stock order will match the input data.

#### Trading Algorithms (Trading Algo)
   - Trading algo refers to the algorithms that calculate the amount of stock held for each stock at a specific time point.
   - Users will implement their trading ideas as algorithm codes, each with a unique name.
   - Trading algo code will include data names, variables for holding input data, specific variables used in the algorithm, and calculation logic.
   - Algorithm configs can be provided in the configuration file, including parameter values specific to each algorithm.

#### Simulation
   - The simulation is defined in the configuration file.
   - It specifies the start time and end time of the simulation, as well as the algorithm configs to be used.
   - Multiple algorithm configs can be included in the configuration file, allowing multiple trading algos to be simulated.
   - The simulator will iterate the run() function for each time point within the specified start and end time.
   - The positions calculated at each time point will be stored as a historical positions 2D array.
   - The results will be saved in CSV format, with each simulation result saved separately.

#### Program Design Considerations
   - Efficient data structures and algorithms should be used to handle large-scale simulations with high memory usage and speed requirements.
   - Thread safety and concurrent processing can be considered to allow multiple simulations to be performed simultaneously using multi-threading.
   - The program should be designed to accommodate frequent addition of new trading algo codes without requiring extensive changes to the entire program.
   - Precautions should be taken to handle minute or sub-minute resolution simulations, including addressing memory usage, simulation speed, and other potential issues that may arise.

#### Program Structure
The program can be structured into the following components:

- ConfigParser: Reads and parses the configuration file.
- DataReader: Reads the input data from the CSV file.
- Simulator: Implements the simulation logic, including iterating calculations and storing historical positions.
- TradingAlgo: Defines the trading algo interface and provides a mechanism for dynamically loading and executing user-defined trading algo codes.
- OutputWriter: Writes the output data to a CSV file.

#### Assumptions and Additional Implementations

- The program will be implemented in C++ using modern C++ practices.
- Third-party libraries can be used to simplify the implementation and enhance functionality.
- The trading algo codes will be compiled as shared libraries(.dylib on Mac | .so on *nix ) and dynamically loaded at runtime.
- Additional error handling and input validation can be implemented to ensure the robustness of the program.
- Logging and debugging mechanisms can be added for easier troubleshooting and analysis.
- Performance optimizations can be applied to enhance the speed and memory usage of the program, such as efficient data structures and parallel processing.

#### Conclusion

This program aims to create a simulator that calculates holding positions based on user-defined trading algorithms. By following the program flow, utilizing the trading algo codes, and adhering to the guidelines and considerations mentioned above, the simulator can handle various scenarios and allow for scalability, flexibility, and efficient execution. The program design document serves as a guide for project-author, collaborators, and users to understand the structure, functionality, and implementation details of the simulator.

### Project Structure

### Build Instructions

```
    - cd <project root> 
    - mkdir build 
    - cd build 
    - cmake .. 
    - make
```

### Libraries Used

- Like any non-trivial C++ programs this simulator uses the [C++ Standard library](https://en.cppreference.com/w/cpp/standard_library)
- Uses [yaml-cpp](https://github.com/jbeder/yaml-cpp) to read configuration files for the Simulator
- Uses [Boost Library] components for reading csv files, Logging etc..
-

### Project Dependencies and Build

- Install a  c++ compiler which supports C++17, for the target platform.
- Install the required dependent libraries. below are the steps for installing libraries on a Mac OS X running on ARM-64 Architeture [M1]()

    ```
brew install clang
brew install cmake
brew install yaml-cpp
brew install boost
    ```

## Acknowledgement

- I am grateful of the opportunity [Factomind](https://www.factomind.io) has provided me with. I would like to sincerely thank the team at Factomind/Hashed Emergent for taking time out to evaluate my submission. I am especially thankful to [Ajay Rai]() for his continued support and encouragement throuhgout the lenght of working on this assignment.


<!-- ### dlfcn library and it's uses
The `dlfcn` library is a dynamic linking library in C/C++ that provides functions for working with dynamically loaded shared objects (dynamic libraries) at runtime. It allows programs to load shared objects dynamically, retrieve function pointers from the loaded objects, and invoke functions from those objects.

The key functions provided by the `dlfcn` library are:

- `dlopen`: Opens a shared object and returns a handle that can be used for subsequent operations.
- `dlsym`: Retrieves the address of a symbol (function or variable) from a loaded shared object.
- `dlclose`: Closes a previously opened shared object.
- `dlerror`: Retrieves a textual description of the most recent error occurred during dynamic linking operations.

The `dlfcn` library is commonly used in scenarios where dynamic loading of shared objects is required, such as:

- Plugin systems: Applications that support plugins can use `dlfcn` to load and unload plugins at runtime.
- Dynamic module loading: Programs that need to load modules dynamically based on certain conditions or configurations can benefit from `dlfcn`.
- Runtime extensions: Libraries or frameworks that support runtime extensions or scripting languages often use `dlfcn` to load user-provided code dynamically.

Overall, `dlfcn` provides a flexible and powerful mechanism for dynamically loading and using shared objects, enabling runtime extensibility and modularity in C/C++ programs. -->
