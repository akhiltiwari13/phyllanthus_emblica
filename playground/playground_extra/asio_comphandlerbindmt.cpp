#include <algorithm>
#include <asio.hpp>
#include <asio/io_context.hpp>
#include <asio/steady_timer.hpp>
#include <asio/strand.hpp>
#include <functional>
#include <memory>
#include <print>
#include <system_error>
#include <thread>
#include <vector>

// a note on asio::strand

// What a strand actually is
//
// A strand is an executor that guarantees the handlers submitted through it
// never run concurrently or overlapping — at most one runs at any instant,
// and each one finishes before the next begins. That's the whole job. It's
// a serialization domain, not a thread.
//
// Think of it as a lock-free alternative to a mutex for completion
// handlers:
//
// - Without a strand, in a thread pool (multiple threads on one
// io_context), two handlers can execute at the same time on different
// threads. If they touch shared state → data race → you reach for a mutex.
// - With a strand, you submit those handlers through it, and Asio
// guarantees they're run one-at-a-time. No mutex needed for state touched
// only inside strand handlers.
//
// The three guarantees (and the three non-guarantees)
//
// A strand gives you:
// 1. Mutual exclusion — no two of its handlers run simultaneously.
// 2. Ordering — handlers execute in the order they were submitted (FIFO for
// post).
// 3. Memory visibility — the end of one strand handler happens-before the
// start of the next, so writes from handler A are visible to handler B with
// no extra synchronization.
//
// A strand does not:
// 1. Pin to a thread — consecutive handlers may run on different pool
// threads; they just never overlap. (So "run it on its own thread" is the
// wrong mental model.)
// 2. Serialize across different strands — only handlers on the same strand
// are mutually excluded. Two different strands run in parallel.
// 3. Do anything if you don't route handlers through it — which is exactly
// your current bug: you constructed strand_ but built the timer on ioc and
// never wrapped the handler, so it's inert.

// Member functions as completion handlers.
//
// A completion handler captured via std::bind(&Class::method, target, ...)
// holds `target` for as long as the async op is pending. With a raw `this`
// that op can outlive the object (it fires later, inside io_context::run())
// -- a dangling pointer. Deriving from enable_shared_from_this and binding
// shared_from_this() keeps the object alive until the handler runs.
// shared_from_this() is not valid inside the constructor (no owning
// shared_ptr exists yet), so the async op is registered from a separate
// start() once the object is owned by a shared_ptr.
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
  asio::strand<asio::io_context::executor_type> strand_;
  asio::steady_timer timer_;
};

FunctorAsExecHandler::FunctorAsExecHandler(asio::io_context& ioc, int id)
    : id_(id),
      strand_(asio::make_strand(ioc)),
      timer_(strand_, asio::chrono::seconds(3)) {
}  // the timer i/o object executes in the strand_ thus garrentuing
   // non-overlapping runs.

FunctorAsExecHandler::~FunctorAsExecHandler() {
  std::println("destroying id {}", id_);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  asio::io_context ioc;
  std::println("Hello World from main.\n");

  // Each handler owns a 3s timer; the pending op keeps the object alive via the
  // shared_ptr bound into the handler.
  std::vector<std::shared_ptr<FunctorAsExecHandler>> handlers;
  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    auto h = std::make_shared<FunctorAsExecHandler>(ioc, i);
    h->start();
    handlers.push_back(std::move(h));
    std::thread t([&]() { ioc.run(); });
    threads.emplace_back(std::move(t));
  }
  ioc.run();
  std::println("Bye World from main.\n");

  std::println("Waiting for threads to join.\n");

  for (auto& t : threads) {
    t.join();
  }
  return 0;
}

// bug worth fixing.
//   The important bug: your strand is doing nothing
//
//   This is the crux of "am I using strands correctly" — you aren't using it at
//   all. Look:
//
//   strand_(asio::make_strand(ioc)),        // line 58: strand created...
//   timer_(ioc, asio::chrono::seconds(3))   // line 59: ...but timer built on
//   `ioc`, not strand_ timer_.async_wait(std::bind(&Print, shared_from_this(),
//   _1));  // line 37: no bind_executor either
//
//   strand_ is a constructed-but-orphaned member. The timer's executor is the
//   plain io_context executor, and the handler is never wrapped in the strand,
//   so nothing is serialized. To actually engage it, you'd either build the
//   timer on the strand (timer_(strand_, ...)) or wrap the handler
//   (asio::bind_executor(strand_, std::bind(...))). And recall from earlier: a
//   per-object strand guarding a single async_wait still serializes nothing —
//   a strand only earns its keep when it guards multiple ops or is shared
//   across handlers.
//
//   Minor things worth fixing
//
//   - Print can't show the threading. Add std::this_thread::get_id() (stream it
//   through an ostringstream) so you can actually observe which thread ran each
//   handler — otherwise the whole multi-threaded point is invisible.
//   - Threads are spawned inside the arming loop (line 78). Cleaner to arm all
//   5 handlers first, then start the pool; interleaving "post work" with "start
//   workers" is fragile (if a worker's run() ever sees an empty queue it
//   returns immediately).
//   - <algorithm> (line 1) is unused.
//   - Stale comment line 32–33 ("binds the thread to the completion handler") —
//   start() binds the object, not a thread.
//
//   If you want, I can apply the side-by-side concurrent-vs-serialized version
//   from the approved plan (prints thread ids, runs once with per-object
//   strands and once with one shared strand) so you can see the strand actually
//   serializing handlers across the pool. Want me to go ahead?
