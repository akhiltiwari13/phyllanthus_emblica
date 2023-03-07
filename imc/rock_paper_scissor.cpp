/**
 * @file rock_paper_scissor.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief  rock-paper-scissor game implementation as per IMC's home assignment
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright akhiltiwari.13@gmail.com (c) 2023
 *
 */

#include <_types/_uint32_t.h>
#include <_types/_uint64_t.h>
#include <_types/_uint8_t.h>
#include <iostream>
#include <string>
#include <sys/wait.h>

namespace imc::rps {

    enum class GameMove { ROCK = 0, PAPER = 1, SCISSOR = 2, INVALID = 255 };

    class RPS{
        public:
            RPS(uint64_t r) : _reps(r) {}

            void rpsMenu() {
                std::cout << "rules:\n ->paper beats (wraps) rock\n ->rock beats(blunts) "
                    "scissor\n ->scissor beats (cuts) paper."
                    << std::endl;
                std::cout << " for paper input p \nfor rock input r \nfor sicssors input s"
                    << std::endl;
            }

            GameMove getSystemMove(){

                //randomly generate a move for the system
                return GameMove::ROCK;
            }

            void evaluateGame(){
                if(_userMove == GameMove::INVALID){
                    std::cout<<"Invalid move by user. Game Drawn"<<std::endl;
                }else if(_userMove == _systemMove){

                } 
            }

            void setUserMove(std::string move){
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

            void initialize(){
                _userMoveStr = "";
                _userMove = GameMove::INVALID;
                _systemMove = GameMove::INVALID;
            }

            void displayScore(){
                std::cout<<"Total Games: "<<_reps<<std::endl;
                std::cout<<"Draws: "<<_drawCounts<<std::endl;
                /* std::cout<<"Winner: "<<(_userWinCounts>)<<std::endl; */
            }

            // loop to play the game
            void play() {
                while (_reps--) {
                    initialize();
                    std::cout<<"User Input:"<<std::endl;
                    std::cin>> _userMoveStr;

                    setUserMove(_userMoveStr);
                    getSystemMove();
                    evaluateGame();
                }
                displayScore();
            }

        private:
            uint64_t _reps{};
            std::string _userMoveStr;
            GameMove _userMove{GameMove::INVALID}, _systemMove{GameMove::INVALID};
            uint64_t _systemWinCounts{};
            uint64_t _userWinCounts{};
            uint64_t _drawCounts{};
    };
}// namespace imc::rps

using namespace imc::rps;
int main() {
    uint64_t games;
    std::cout << "Enter Game count:" << std::endl;
    std::cin >> games;

    RPS rps(games);
    rps.play();

    return 0;
}

// TODO: convert enums to strings & vice-versa.
// TODO: check std::optional | std::variant | enum class uses
// TODO: check conversion from user input to enums
// TODO: Any 3rd party libs for parsing user inputs.
