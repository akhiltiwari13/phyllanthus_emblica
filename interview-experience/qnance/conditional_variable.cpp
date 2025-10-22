#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;

std::condition_variable cv;
bool cond{false};
std::mutex mut{};

void funct_wait(){
    std::unique_lock<std::mutex> lg(mut);
    /* The waiting threads call the wait() function on the condition variable, which atomically releases the lock and suspends the thread until it is notified. */
    cv.wait(lg,[]{std::cout<<"condition: "<<cond<<std::endl; return cond;});
    /* When a waiting thread receives a notification, it reacquires the lock on the mutex and resumes execution. It then checks whether the condition it was waiting for is met. If not, it may choose to go back to waiting or perform other actions. */

    cout<<"condition true, resuming ops"<<std::endl;
    for(int i=0; i<100; ++i){
        cout<<"i: "<<i<<std::endl;
    }
}

void funt_notify(){
    std::unique_lock<std::mutex> lg(mut);

    //simulating some work
    std::this_thread::sleep_for(std::chrono::seconds(10));
    cond = true;


    /* a separate thread that is responsible for changing the condition signals the waiting threads by calling notify_one() or notify_all() on the condition variable. */
    cv.notify_all();

}


int main(int argc, char* argv[]){

    std::thread t1(funct_wait);
    std::thread t2(funt_notify);


    t1.join();
    t2.join();


    return 0;
}
