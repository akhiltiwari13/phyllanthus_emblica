/**
 * @file main.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief  rock-paper-scissor game implementation as per IMC's home assignment
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright akhiltiwari.13@gmail.com (c) 2023
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include "rps.h"


int main() {
    uint64_t games;
    std::cout << "Enter Game count:" << std::endl;
    std::cin >> games;

    imc::rps::RPS rps(games);
    rps.play();

    return 0;
}
