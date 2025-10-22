#include <iostream>

struct base {
    int a = 10;
    int b = 3;
    void tester() {
        std::cout << "This is the base class\n";       
    }   
};

struct derived: base {
    int a = 2;
    int c = b;

    void tester() {
        std::cout << "This is the derived class\n";
    }
};

struct indep {
    int a = 4; int b = 6; int c = 20;
    void tester(){
        std::cout << "This is the indepoendent class";
    }
};

void main(){
    base* baseptr = new base();
    derived* derivedptr = new derived();
    indep* indepptr = new indep();

    base* derivedtest = new derived();
    
    baseptr->tester();
    derivedptr->tester();
    indepptr->tester();

    std::cout << derivedtest.c;
}