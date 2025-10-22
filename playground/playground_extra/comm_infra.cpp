#include <iostream>
#include <event_loop.h>
#include <event_source.h>
#include <event_callback.h>
#include <event_publisher.h>
#include <memory>

using namespace std;
using namespace elaeo::foundation::events;

class MyEvent{
public:
  std::string data{"dummy-data"};
};

int main() {
  elaeo::foundation::events::EventLoop event_loop;
  // event_loop.setCoreID(0); // Pin to CPU core 0 (optional)

  // auto socket_fd = /* create socket */;
  auto socket_fd = 3;
  auto fd_source = std::make_shared<MySocketFDEventSource>(socket_fd);
  auto sub_id =
      event_loop.registerFDEventSource(fd_source, EventLoop::EventType::READ);
  auto timer_source = make_polling_event_source([&]() {
    return check_timer_expired(); // Returns true if timer fired
  });
  event_loop.registerPollingEventSource(timer_source);

  auto callback = make_lambda_callback<MyEvent>([](const MyEvent &e) {
    std::cout << "Event received: " << e.data << std::endl;
  });
  event_publisher.registerCallback(callback, PRIORITY_HIGH);
  event_loop.loop(); // Blocking main loop
  
  // OR
  // while (!event_loop.nonBlockingLoop()) { /* Do other work */
  //}
  return 0;
}
