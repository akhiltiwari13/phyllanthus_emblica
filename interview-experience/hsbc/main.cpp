#include <iostream>
#include <thread>

using namespace std;

void funct(int a, int b){
    cout<<"hello"<<std::endl;

}



class base{
    public:
    virtual void foo(){
        cout<<"base"<<std::endl;
    }

};

class derived: public base{
    private:
    void foo(){
        cout<<"derived"<<std::endl;
    }
};

int  main(){

    auto var = [](){cout<<"hello\n";};

    std::thread t1(funct, 1, 3);
    std::thread t2(var );

    t1.join();

    base* b = new derived();
    b->foo();
    base *b2; 

    /* derived d = dynamic_cast<derived>(&b); */
    derived* d = dynamic_cast<derived*>(b2);


    return 0;


    /* () //c style */

    /* c++ -> static_cast() , dynamic_cast(), const_cast(), reinterpret_cast() */

vector v{1...100};

/* even numbers..... */
erase remove idiomk

    remove_if(begin, end, predicate)

    auto it = remove_if(v.begin(), v.end(),[](int n){return n%2==0;} );
    v.erase(it);


    for(auto e: v){
        if(e%2 == 0)//even
    }




}
