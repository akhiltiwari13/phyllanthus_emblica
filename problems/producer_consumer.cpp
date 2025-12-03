#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

// ask:
//
// 1. create a producer (emit text data)
// 2. create a consumer that calls reads the data produced by the consumer and
// display it on to the screen/console.
//
// single-producer and single consumer model.
//
//
// global mutex
//
//

class Sync {
private:
  std::queue<int> q_;
  std::mutex m_;
  std::condition_variable c_;
  bool flag{false}; // test its requirement.

public:
  void push(int val) {
    {
      std::lock_guard<std::mutex> lock(m_);
      q_.push(val);
    }
    c_.notify_all();
  }

  bool pop(int &val) {

    std::unique_lock<std::mutex> lock(m_);
    c_.wait(lock, [this] { return !q_.empty(); });

    if (q_.empty())
      return false;

    val = std::move(q_.front());
    std::cout << "popped val: " << val << std::endl;
    q_.pop();
    return true;
  }
};

void producer(Sync &sq, int id, int count) {
  for (int id = 0; id < count; id++) {
    sq.push(id * 3 + id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void consumer(Sync &sq, int id) {
  int value;
  while (sq.pop(value)) {
    std::cout << "consumer thread:" << id << "val: " << value << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  }
}

int main(int argc, char *argv[]) {
  Sync synced_queue;

  std::thread tp1(producer, std::ref(synced_queue), 1, 5);
  std::thread tc1(consumer, std::ref(synced_queue), 1);

  tp1.join();
  tc1.join();
}
