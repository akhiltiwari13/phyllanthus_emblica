# Ogha-research's assignment
A copy of the assignment can be found here: [assignment](../imgs/ogha/ogha_assignment.pdf)

## Build Instructions
``` 
    - cd <project root> 
    - mkdir build 
    - cd build 
    - cmake .. 
    - make
```

## About the project
   - I am grateful of the opportunity [OGHA Research LLP](http://www.ogha-research.in) has provided me with. As the author of this project I do realize that I am submitting it beyond the agreed upon deadline and I understand if the firm would like to cancel my candidature for the same. I attribute this delay to some urgent personal exigencies which arose a couple of weeks back & would like to make my submission nonetheless. 
## Assumptions
   - This project does not use any 3rd party library. It has been build & tested on an ARM-64 architecture machine running a MacOS(I believe this should work on most *NIX systems and verified using any/most Linux distros). I have tried to account for any edge-cases that I could think off and would like to apologise in advance for any oversight that may have happened. Each program tries to be efficient within the constraint of real world scenarios, edge cases and/or any special requirements mentioned in the problem statement.
  - **problem 01:** Assumes the list to find the nearest pair from can contain duplicate values. Also, if more than one nearest pair exists the program returns the first nearest pair it identifies. Since it uses a Hash-Table based data structures, the order of identifying the first nearest pair is non-deterministic.
  - **problem 02:** A sample input file is available along with the source for testing. Below is the usage description of the generated Executable:
            ```
            ➜  build ./02_split_file/split_file
            Usage: ./02_split_file/split_file <file path> <minimum number of records in a file>
            ```
  - **problem 03:** As asked in the problem statement, I have refrained from using any STL containers. Also since a version history of the queue was needed to be maintained, the nodes used to represent elements of the queue required only soft deletion which is why I have used raw pointers instead of any smart_pointer.


## Acknowledgement:
  - I would like to sincerely thank the team at OGHA for taking time out to evaluate my submission. I am also thankful to [Shashi Rekha](https://www.linkedin.com/in/shashi-rekha-a6a076a/) for her understanding and allowing me extended time to work on this assignment. I am especially grateful towards [Karla Chávez Romero](https://www.linkedin.com/in/karlachavezromero/) for her constant encouragement and vast patience.
