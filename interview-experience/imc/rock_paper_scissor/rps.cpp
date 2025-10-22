/**
 * @file rps.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief cpp file for RPS definitions
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "rps.h"
#include <iostream>

using namespace imc::rps;

RPS::RPS(uint64_t r) : _reps(r),_userMoveStr("\0"),_userMove(GameMove::INVALID),_systemMove(GameMove::INVALID),_systemWinCounts(0),_userWinCounts(0),_drawCounts(0),_noResultCounts(0)  {}

RPS::RPS() : _reps(0),_userMoveStr("\0"),_userMove(GameMove::INVALID),_systemMove(GameMove::INVALID),_systemWinCounts(0),_userWinCounts(0),_drawCounts(0),_noResultCounts(0)  {}

void RPS::menu() {
    std::cout<<"============================"<<std::endl;
    std::cout << "**rules:\n ->paper beats (wraps) rock\n ->rock beats(blunts) "
        "scissor\n ->scissor beats (cuts) paper.\n"
        << std::endl;
    std::cout << "for paper input: p \nfor rock input: r \nfor sicssors input: s"
        << std::endl;
    std::cout<<"============================"<<std::endl;
}

GameMove RPS::genSystemMove(){
    srand(time(0));
    _systemMove=GameMove(rand()%3);
    return _systemMove;
}

void RPS::evaluateGame(){
    if(_userMove == GameMove::INVALID){
        std::cout<<"*Invalid move by user"<<std::endl;
        ++_noResultCounts;
    }else if(_userMove == _systemMove){
        std::cout<<"*Game Drawn"<<std::endl;
        ++_drawCounts;
    }else if((_userMove == GameMove::ROCK && _systemMove == GameMove::SCISSOR) || (_userMove == GameMove::SCISSOR && _systemMove == GameMove::PAPER)  || (_userMove == GameMove::PAPER && _systemMove == GameMove::ROCK )) {
        std::cout<<"*User Won."<<std::endl;
        ++_userWinCounts;
    }else{
        std::cout<<"*System Won."<<std::endl;
        ++_systemWinCounts;
    }
}

void RPS::setUserMove(std::string move){
    if(!move.length()) _userMove = GameMove::INVALID;
    else{
        switch (move[0]){
            case 'r':
                _userMove = GameMove::ROCK;
                break;
            case 'p':
                _userMove = GameMove::PAPER;
                break;
            case 's':
                _userMove = GameMove::SCISSOR;
                break;
            default:
                _userMove = GameMove::INVALID;
        }
    }
}

char RPS::getSystemMove(){
    switch (_systemMove){
        case GameMove::ROCK:
            return 'r';
        case GameMove::PAPER:
            return 'p';
        case GameMove::SCISSOR:
            return 's';
        default:
            return '\0';
    }

}


void RPS::resetVals(){
    _userMoveStr = "";
    _userMove = GameMove::INVALID;
    _systemMove = GameMove::INVALID;
}

void RPS::displayScore(){
    std::cout<<"\n===========\nfinal score\n==========="<<std::endl;
    std::cout<<"Total Games: "<<_reps<<std::endl;
    std::cout<<"Draws: "<<_drawCounts<<std::endl;
    std::cout<<"No Contest: "<<_noResultCounts<<std::endl;
    std::cout<<"User Won: "<<_userWinCounts<<std::endl;
    std::cout<<"System Won: "<<_systemWinCounts<<std::endl;
}

void RPS::play() {
    menu();
    auto tmp{_reps};
    // loop to play the game
    while (tmp--) {
        resetVals();
        std::cout<<"\nUser Input:"<<std::endl;
        std::cin>> _userMoveStr;

        setUserMove(_userMoveStr);
        genSystemMove();
        std::cout<<"System Move:"<<getSystemMove()<<std::endl;
        evaluateGame();
    }
    displayScore();
}

