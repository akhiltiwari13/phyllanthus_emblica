/**
 * @file rps.h
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief RockPaperScissor class's declaration.
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <string>

namespace imc::rps {

    enum class GameMove { ROCK = 0, PAPER = 1, SCISSOR = 2, INVALID = 255 };

    class RPS{
        public:
            RPS(uint64_t r);
            RPS();
            void menu(); 
            GameMove genSystemMove();
            void evaluateGame();
            void setUserMove(std::string move);
            char getSystemMove();
            void resetVals();
            void displayScore();
            void play();

        private:
            uint64_t _reps{};
            std::string _userMoveStr;
            GameMove _userMove{GameMove::INVALID}, _systemMove{GameMove::INVALID};
            uint64_t _systemWinCounts{};
            uint64_t _userWinCounts{};
            uint64_t _drawCounts{};
            uint64_t _noResultCounts{};
    };
}// namespace imc::rps
