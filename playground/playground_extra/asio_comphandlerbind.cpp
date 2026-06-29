#include <asio.hpp>
#include <asio/io_context.hpp>
#include <asio/steady_timer.hpp>
#include <functional>
#include <memory>
#include <print>
#include <system_error>
#include <vector>

// Member functions as completion handlers.
//
// A completion handler captured via std::bind(&Class::method, target, ...)
// holds `target` for as long as the async op is pending. With a raw `this` that
// op can outlive the object (it fires later, inside io_context::run()) -- a
// dangling pointer. Deriving from enable_shared_from_this and binding
// shared_from_this() keeps the object alive until the handler runs.
// shared_from_this() is not valid inside the constructor (no owning shared_ptr
// exists yet), so the async op is registered from a separate start() once the
// object is owned by a shared_ptr.
class FunctorAsExecHandler
    : public std::enable_shared_from_this<FunctorAsExecHandler> {
 public:
  FunctorAsExecHandler(asio::io_context& ioc, int id);

  FunctorAsExecHandler(const FunctorAsExecHandler&) = delete;
  FunctorAsExecHandler& operator=(const FunctorAsExecHandler&) = delete;
  ~FunctorAsExecHandler();

  // This is a utility memeber function that binds the thread to the completion
  // handler. could this have been done inside the constructor itself? Schedule
  // the wait. shared_from_this() forwards a shared_ptr into the bound handler,
  // so `this` stays alive until Print() runs.
  void start() {
    timer_.async_wait(std::bind(&FunctorAsExecHandler::Print,
                                shared_from_this(), std::placeholders::_1));
  }

  // Asio invokes a wait handler as void(const std::error_code&); the _1
  // placeholder forwards that code here.
  void Print(const std::error_code& e) {
    if (e) {
      std::println("id {} timer error: {}", id_, e.message());
      return;
    }
    std::println("id: {}", id_);
  }

 private:
  int id_;
  asio::steady_timer timer_;
};

FunctorAsExecHandler::FunctorAsExecHandler(asio::io_context& ioc, int id)
    : id_(id), timer_(ioc, asio::chrono::seconds(3)) {}

FunctorAsExecHandler::~FunctorAsExecHandler() {
  std::println("destroying id {}", id_);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  asio::io_context
      ioc;  // this io  context is expected to run in the main thread!
  std::println("Hello World from main.\n");

  // Each handler owns a 3s timer; the pending op keeps the object alive via the
  // shared_ptr bound into the handler.
  std::vector<std::shared_ptr<FunctorAsExecHandler>> handlers;
  for (int i = 0; i < 5; ++i) {
    auto h = std::make_shared<FunctorAsExecHandler>(ioc, i);
    h->start();
    handlers.push_back(std::move(h));
  }

  ioc.run();
  std::println("Bye World from main.\n");
  return 0;
}
