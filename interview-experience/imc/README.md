# IMC Assignment
    This README has any supplementary info required for the 2 problems. It also includes my answers to the subjective questions in the 2nd problem.

## Rock-Paper-Scissors [solution](./rock_paper_scissor/main.cpp)
    The project was built, executed & tested on a MacOS m/c. It should, most likely, be compatible with most linux distros as well. 
### build instructions:
    from the source directory
    mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make

## ConcurrentQueue code review Answers [file](./concurrent_queue/ConcurrentQueue.cpp):
```     
   • What changes would you suggest in a code review? Would you check in your code like this? Do you think the code is clean? 
    -> There are some asthetic change that could improve the code for example using standard library functions where possible and segregating the concurrent queue among header and cpp files etc.. Detailed review is added as comments to the code.

    • Do you see room for improving the performance without breaking thread safety?
    -> yes, certain results can be stored in variables instead of calculating them on the fly @ runtime.
    -> getter member functions could be made inline 
    
    • What steps would you take to find the bug?
    1-> build and execute the code to find if it breaks at runtime. if not, we could write functional stress test to check the performance of the queue on the edge cases.
    2-> if the program, has a segfault, the generated core could be analyzed via gdb/clangdb. If a core dump is not generated, we can look at the logs (stdout/stderr) to find the last successful execution in the code.

    • If you can find the bug, what fix would you suggest? Write a proper test case to prove that the bug is solved (may be in pseudo code), preferably in a deterministic matter?
    -> testcase pseudo code:
        1. create multiple producer threads, preferably a large number of producers to fill the queue to it's capacity.
        2. create a single consumer thread 
        3. introduce a minor delay in the producers to match with the assumption that consumer consumes faster than the rate of production.
        4. run the setup in a loop.

    • If you cannot find the bug, how would you go about testing the thread safety of the class?
    -> testcase pseudo code:
        1. create multiple producer threads, preferably a large number of producers to fill the queue to it's capacity.
        2. duplicate the producer messages to tally them against the messages that the consumer would have consumed.
        3. create a single consumer thread. Copy the messages that have been consumed.
        4. run the setup in a loop.
        5. Tally the produced and consumed messages and check for data loss and their states.
```

