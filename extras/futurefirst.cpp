#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int i44 = 44;
// problems.
/*
  thread2:
    get mutexA
    get mutexB
    operation()

  thread2:
    get mutexB
    get mutexA
    operation()


    */

/*int main() {
  std::string str = "abcdef TUVWXYZ";
  std::printf("Original string is: %s\n", str.c_str());

  std::string encodedStr = Encode(str);
  std::printf("Encoded string is:  %s\n", encodedStr.c_str());

  return 0;
}
*/

//
// Original string is: abcdefz ABTUVWXYZ
// Encoded string is:  nopqrsm NOGHIJKLM
//

std::string Encode(std::string str) {
  for (auto c : str) {
    if (c >= 'A' && c <= 'Z') // upper case
    {
      c = 'A' + ((c - 'A' + 13) % 26); //@todo
    } else if (c >= 'a' && c <= 'z')   // lower cased
    {
      c = 'a' + ((c - 'a' + 13) % 26); //@todo
    }
  }

  return str;
}

/*  int main() {
    std::string str = "abcdef TUVWXYZ";
    std::printf("Original string is: %s\n", str.c_str());

    std::string upcasedStr = ToUpper(str);
    std::printf("Upcased string is:  %s\n", upcasedStr.c_str());

    return 0;
  }

  */

//
// Original string is: abcdef TUVWXYZ
// Upcased string is:  ABCDEF TUVWXYZ
//

std::string ToUpper(const std::string &str) {
  std::string rslt{};

  for (auto c : str) {
    if (c >= 'a' && c <= 'z') {
      // upper case
      rslt.push_back(c - ('a' - 'A'));
      continue;
    }
    rslt.push_back(c);
  }

  return rslt;
}

void Func(int &pi) { pi = i44; }

int main(int argc, char *argv[]) {
  int i = 11;
  Func(i);
  printf("After Func: %d\n", i);

  return 0;
}
