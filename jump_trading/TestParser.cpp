#include <fstream>
#include <iostream>


/* forward Declaration */
class Parser;
class Iterator;

int main() {
    std::ifstream inputFile("TestParserInput.txt");
    std::string strOneLine;

    std::cout << "Starting.... " << std::endl;

    while (inputFile) {
        getline(inputFile, strOneLine);
        std::cout << strOneLine << std::endl;
    }

    inputFile.close();

    /* example usage in main: */
    /* Parser prsr(stream); */
    /* for(Parser::Iterator it = prsr.begin(); it != prsr.end(); ++it){ */
    /*     int x = *it; */
    /*         std::cout<<x<<std::endl; */
    /*         } */

    return 0;
}

