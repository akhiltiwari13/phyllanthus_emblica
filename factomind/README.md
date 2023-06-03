# factomind's assignment
problem statement: [assignment](https://factec.notion.site/Coding-Assignment-9ca9538c97ae4d5f85e7afc9cbcb7c78)

## Build Instructions
``` 
    - cd <project root> 
    - mkdir build 
    - cd build 
    - cmake .. 
    - make
```

## About the project
   - I am grateful of the opportunity [Factomind](https://www.factomind.io) has provided me with. As the author of this project I do realize that I am submitting it beyond the agreed upon deadline and I understand if the firm would like to cancel my candidature for the same. I attribute this delay to some urgent personal exigencies which arose a couple of weeks back. I have always intentended on puting in the work & would like to make my submission nonetheless. 

## Project Description & Assumptions
   - Given the nature and complexity of this project it utilizes some mainstream, opensourced 3rd party C++ libraries. It has been build & tested on an ARM-64 architecture machine running a MacOS(I believe this should work on most *NIX systems). I have tried to account for any edge-cases that I could think off and would like to apologise in advance for any oversight that may have happened.

### Project Structure:
 - Brief: 
 ```
    Designing a simulator program that calculates the history of holding positions according to various portfolio trading algorithm codes requires careful consideration of the program structure and functionality. Here's a high-level outline of the program structure:

1. Read Config:
   - Read the configuration file (in YAML format) that contains simulation information, such as start time, end time, and algorithm configurations.
   - Parse the configuration data and store it in appropriate data structures.

2. Read Input Data:
   - Read the input data file (in CSV format) containing the time-series data for each stock.
   - Parse the input data and store it in a suitable data structure (e.g., a 2D array).

3. Algorithm Implementation:
   - Implement the trading algorithm(s) as separate functions or classes.
   - Each algorithm function/class should have the necessary logic to calculate the position of each stock at a specific time point based on the input data.
   - The algorithm code should consider input parameters and state variables as mentioned in the requirements.

4. Simulation:
   - Iterate over the time points from the start time to the end time.
   - For each time point, invoke the algorithm(s) specified in the configuration file.
   - Pass the appropriate input data, algorithm parameters, and state variables to the algorithm function/class.
   - Receive the calculated positions and store them in a historical position data structure.

5. Write Output Data:
   - Write the historical position data to an output CSV file.
   - The output file should have the same shape as the input data, containing the amount of stock held for each stock at each time point.

Additional Considerations:
- Efficiency: Consider efficient data structures and algorithms to handle large-scale simulations.
- Memory Usage: Optimize memory usage by avoiding unnecessary duplication of data and using appropriate data structures.
- Speed: Optimize the simulation process by utilizing multi-threading to perform multiple simulations simultaneously.
- Minute or Sub-Minute Resolution: For simulations with finer time resolution, additional considerations are required:
  - Memory Usage: Use memory-efficient data structures to handle a large number of time points.
  - Algorithm Efficiency: Optimize the trading algorithm(s) for faster execution with finer time resolution.
  - Input Data Management: Efficiently manage and process the input data for minute or sub-minute intervals.

The above outline provides a general framework for designing the simulator program. You can implement the program based on this structure, considering the specific requirements and constraints of your project.
 ``` 
 -
 -
 -
 -


### Libraries Used:
- Like any non-trivial C++ programs this simulator also uses the [C++ Standard library](https://en.cppreference.com/w/cpp/standard_library)
- Uses [yaml-cpp](https://github.com/jbeder/yaml-cpp) to read configuration files for the Simulator
- Uses [csv-parser](https://github.com/vincentlaucsb/csv-parser) to read csv files for the Simulator
- 
- 

### Project Dependencies and Build
- Install a  c++ compiler which supports C++17, for the target platform.
- Install the required dependent libraries. below are the steps for installing libraries on a Mac OS X running on ARM-64 Architeture [M1]()
    ```

    ```
-

## Acknowledgement:
  - I would like to sincerely thank the team at Factomind/Hashed Emergent for taking time out to evaluate my submission. I am especially thankful to [Ajay Rai]() for his continued support and encouragement throuhgout the lenght of working on this assignment.
