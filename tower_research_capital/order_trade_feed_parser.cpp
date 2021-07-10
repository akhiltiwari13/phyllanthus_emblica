/**
 * This program has not been tested thoroughly because generating test case for this problem seems like a lot of hassle.! 
 **/

#include <cstdio>
#include <iostream>
#include <string>

/* processes market packets line by line. */
void parser(const std::string pkt) {
    std::string::size_type start_idx{};
    const std::string::size_type headerLen =
        static_cast<std::string::size_type>(6);

    /* std::cout<<"[DEBUG] pkt.size()="<<pkt.size()<<std::endl; */

    const std::string delims{" \t,.;|"};
    start_idx = pkt.find_first_not_of(delims);
    /* process packet header. */
    if ((pkt.size() == 0) || (start_idx == std::string::npos)){
        std::cout<<"[INFO] no data in this line"<<std::endl;
        return;
    }
    else {
        start_idx += headerLen;
    }

    /* check suitable boundary conditions */
    while ((start_idx != std::string::npos) && (start_idx < 65536) &&
            (start_idx < pkt.size()-1)) {
        /* process market updates. */
        /* currently start_idx points to the first index of market update packet. */
        /* std::cout<<"[DEBUG] pkt.at(start_idx + 9)="<<pkt.at(start_idx + 9)<<std::endl; */
        if (pkt.at(start_idx + 9) == 'T') {
            /* print trade info. */
            /* std::cout<<"[INFO] trade found! "; */
            std::cout << stoi(pkt.substr(start_idx + 10, 4)) << " "
                << pkt.substr(start_idx + 4, 5) << " "
                << stoll(pkt.substr(start_idx + 14, 8)) << std::endl;
        }
        auto increment_idx_by=stoi(pkt.substr(start_idx , 4));
        start_idx += increment_idx_by;
        /* std::cout<<"[DEBUG] index incremented to: "<< start_idx<<std::endl; */
    }
}

int main() {
    /* reads the file to an input stream and replaces cin with it. */;
    std::freopen("parser_input.txt", "r", stdin);
    std::string input_line;

    std::cout<<"QTY SYM PRICE"<<std::endl;
    while(getline(std::cin,input_line)){
        parser(input_line);
    }

    return 0;
}
