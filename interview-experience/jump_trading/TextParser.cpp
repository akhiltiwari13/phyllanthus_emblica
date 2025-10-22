#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// solution design judging from the example usage in main
// 1. Parser::Iterator it => A nested iterator class in Parser
// 2. begin() & end() member functions in Parser
// 3. define operators * ++  != for Parser::Iterator
// 4. Parser::Iterator it = parsr.begin() => a copy constructor for Parser's
// iterator
class Parser {
public:
  class Iterator; // fwd declaration to return Iterator obj from begin() &&
                  // end()

  Parser(std::ifstream &filestream) {
    std::string line;
    int num{};

    while (getline(filestream, line)) {
      std::stringstream iss(line);
      if (iss >> num && iss.eof()) { // extract interger form stream && check if
                                     // reached the end of stream.
        numbers.push_back(num);
      }
      iss.clear();
    }
  }

  Iterator begin() { return Iterator(numbers.begin()); }

  Iterator end() { return Iterator(numbers.end()); }

  class Iterator {
  public:
    Iterator(std::vector<int>::iterator it) : vit(it) {}

    int &operator*() { return *vit; }

    Iterator &operator++() {
      vit++;
      return *this;
    }

    bool operator!=(const Iterator &other) { return vit != other.vit; }

  private:
    std::vector<int>::iterator vit;
  };

private:
  std::vector<int> numbers{}; // this vector will store the parsed integers.
};

// test function
int main() {
  std::ifstream inputFile("./input.txt");

  /* example usage in main: */
  Parser prsr(inputFile);
  for (Parser::Iterator it = prsr.begin(); it != prsr.end(); ++it) {
    int x = *it;
    std::cout << x << std::endl;
  }

  inputFile.close();
  return 0;
}

