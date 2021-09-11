#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>

/*
   Parallel Task Processor
   The two classes below should be able to take in any typeof data or
   processing function
   - Processing Engine
   - Output

   The aim is to end up with the following pipeline:
   Feeder -> Engine -> Output
   This excersize is quite long so please focus on having something which
   works. You should start with the Engine class as the Outpus module is less
   important.

   Application example: string sorting
   Example input:
   bdajcfegih
   bdajcfegih
   bdajcfegih
   bdajcfegih
   bdajcfegih
   bdajcfegih
   bdajcfegih
   bdajcfegih
   bdajcfegih
   */

namespace app {
    void process(std::string& s){
        std::sort(s.begin(), s.end());
    }

    void reverse_sort(std::string& s){
        std::sort(s.rbegin(), s.rend());
    }

    void output(const std::string& s){
        std::cout<< s<< std::endl;
    }

    class Feeder{
        public:
            Feeder() = default; //use of default keyword.
            ~Feeder() noexcept = default; //use of default keyword.

            void run(){
                m_thread= std::thread([this](){
                        for(std::string line; std::getline(std::cin,line);){
                        std::cout<< "Feeding "<< line <<std::endl;
                        // @TODO- send to engine.
                        }
                        });
            }

            void stop(){
                m_thread.join();
            }

        private:
            std::thread m_thread;


    };
}

namespace framework{
    /* @TODO: create class Engine; */

}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    // time measurement
    {
        app::Feeder feeder;
        feeder.run();

        feeder.stop();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout<<std::endl<< "Duration:"<< std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()<< " ns."<<std::endl;

    return 0; }
