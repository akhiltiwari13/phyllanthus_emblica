// thread safe circular buffer. which internally uses --> Arrays (size fixed at
// intialization) apis: enque() | dequeue() | find(index) -> based on index.
//
// 1 4 5
//
//
//
//
//
#include <vector>
#include <mutex>
#include <iostream>
#include <thread>

using namespace std;

template <typename T> class TSCircBuff {

private:
  std::vector<T> buff;
  size_t head;
  size_t tail;
  size_t capacity;
  bool full;
  std::mutex mtx;

public:
  // comp functions
  explicit TSCircBuff()
      : head(0), tail(0), capacity(1), full(false), buff(std::vector<T>(1)) {}

  explicit TSCircBuff(size_t capacity)
      : head(0), tail(0), capacity(capacity), full(false), buff(std::vector<T>(capacity)) {}

  bool enque(T obj) {
    std::lock_guard<std::mutex> lock(mtx);
    if (full)
      return false;
    else {
      buff[head] = obj;
      head = (head + 1) % capacity;
    }
    full = (head == tail) ? true : false;
    return true;
  }

  bool deque() {
    std::lock_guard<std::mutex> lock(mtx);

    // check if empty return false

    // if (full)
    //   return false;

    tail = (tail + 1) % capacity;
    full = false;

    return true;
  }

  bool is_full() {
    return full; }

  T &find(size_t idx){
    std::lock_guard<std::mutex> lock(mtx);
    // check index's valididty
    return buff[idx];
  }

  bool is_empty(){
    std::lock_guard<std::mutex> lock(mtx);
    // check index's valididty
    return buff[idx];
  }

  // dequeue(T obj);
  // void erase();
};

int main(int argc, char *argv[]) {

  // producer & consumer
  //
  TSCircBuff<int> cqueue(5);
  auto val = cqueue.enque(1);
  val = cqueue.enque(2); val =  cqueue.enque(6); val =   cqueue.enque(6);

      return 0;
}
