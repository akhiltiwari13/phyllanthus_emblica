#include <cstdio>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <set>

int main() {
    std::vector<std::string> input_files{"rn_input1.txt", "rn_input2.txt"};

    for(auto file: input_files){

        std::set<std::tuple<unsigned int, unsigned int, unsigned int>> road_edge_list; 
        std::set<std::tuple<unsigned int, unsigned int, unsigned int>> proposal_edge_list; 

        /* varaibles to store inputs. */
        unsigned int num_city{}, num_road{}, num_proposals{};
        unsigned int city_s{}, city_d{}, distance{};

        /* std::tuple<unsigned int, unsigned int, unsigned int> highway; */
        freopen(file.c_str(), "r", stdin);
        std::cin>>num_city>>num_road>>num_proposals;

        for(int i=0; i< num_road; ++i){
            std::cin>>city_s;
            std::cin>>city_d;
            std::cin>>distance;

            road_edge_list.insert(std::make_tuple(city_s,city_d,distance));
        }

        for(int i=0; i< num_proposals; ++i){
            std::cin>>city_s;
            std::cin>>city_d;
            std::cin>>distance;

            proposal_edge_list.insert(std::make_tuple(city_s,city_d,distance));
        }

        /* print roads and proposals */
        std::cout<<"[DEBUG] road list:"<<std::endl;
        for(auto roads: road_edge_list){
            std::cout<<"{"<<std::get<0>(roads)<<", "<<std::get<1>(roads)<<", "<<std::get<2>(roads)<<"}"<<std::endl;
        }
        std::cout<<"[DEBUG] proposal list:"<<std::endl;
        for(auto prop: proposal_edge_list){
            std::cout<<"{"<<std::get<0>(prop)<<", "<<std::get<1>(prop)<<", "<<std::get<2>(prop)<<"}"<<std::endl;
        }

    }


    return 0; }
