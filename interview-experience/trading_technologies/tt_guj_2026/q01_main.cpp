/**
 * @file q01_main.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief tt-guj-2026 q01 — tests for PacketReceiver.
 *
 * Control sums are COMPUTED with std::hash<std::string>, never hardcoded:
 * std::hash is not specified to be stable across implementations, and it
 * genuinely is not. For "hello", libstdc++ gives 2762169579135187400 while
 * libc++ gives 235368941344721064, so a literal here would pass under
 * conan-profiles/debug-omarchy-x86-gcc and fail under debug-omarchy-x86-clang.
 *
 * @version 0.2
 * @date 2026-09-10
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "q01_packet_receiver.h"

namespace {

using Packets = std::vector<std::string>;

/// The control sum a well-formed sender would attach to @p data.
std::size_t Sum(const std::string& data) {
  return std::hash<std::string>{}(data);
}

/// A control sum that does not match @p data — i.e. a corrupt part.
std::size_t BadSum(const std::string& data) { return Sum(data) ^ 0x5a5a5a5aU; }

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

bool doTestsPass() {
  bool passed = true;

  // Parts arriving before any StartPacket() have nowhere to go.
  {
    PacketReceiver rx;
    passed &= expect("part before StartPacket is rejected",
                     !rx.ReceivePart(0, Sum("a"), "a"));
    passed &= expect("rejected part counted as failed",
                     rx.GetNumOfFailedParts() == 1);
    passed &= expect("nothing collected", rx.GetCollectedPackets().empty());
  }

  // The worked example from the statement:
  //   Start, id1, id0, Start, id2, id1
  {
    PacketReceiver rx;
    rx.StartPacket();
    passed &= expect("p0 id1", rx.ReceivePart(1, Sum("world"), "world"));
    passed &= expect("p0 id0", rx.ReceivePart(0, Sum("hello "), "hello "));
    rx.StartPacket();
    passed &= expect("p1 id2", rx.ReceivePart(2, Sum("!"), "!"));
    passed &= expect("p1 id1", rx.ReceivePart(1, Sum("bye"), "bye"));

    passed &=
        expect("two packets, merged by id",
               rx.GetCollectedPackets() == (Packets{"hello world", "bye!"}));
    passed &= expect("no failures", rx.GetNumOfFailedParts() == 0);
  }

  // Ordering is by id, regardless of arrival order.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(3, Sum("D"), "D");
    rx.ReceivePart(1, Sum("B"), "B");
    rx.ReceivePart(0, Sum("A"), "A");
    rx.ReceivePart(2, Sum("C"), "C");
    passed &= expect("reversed arrival still merges in id order",
                     rx.GetCollectedPackets() == Packets{"ABCD"});
  }

  // A repeated id overwrites, and is not a failure.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(0, Sum("first"), "first");
    passed &=
        expect("repeat accepted", rx.ReceivePart(0, Sum("second"), "second"));
    passed &= expect("repeat overwrote",
                     rx.GetCollectedPackets() == Packets{"second"});
    passed &=
        expect("overwrite is not a failure", rx.GetNumOfFailedParts() == 0);
  }

  // A bad control sum fails and stores nothing.
  {
    PacketReceiver rx;
    rx.StartPacket();
    passed &= expect("corrupt part rejected",
                     !rx.ReceivePart(0, BadSum("payload"), "payload"));
    passed &= expect("corrupt part counted", rx.GetNumOfFailedParts() == 1);
    passed &= expect("corrupt part not stored",
                     rx.GetCollectedPackets() == Packets{""});
  }

  // Corruption must not clobber a part already verified under the same id.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(0, Sum("good"), "good");
    passed &= expect("corrupt repeat rejected",
                     !rx.ReceivePart(0, BadSum("evil"), "evil"));
    passed &= expect("good part survives",
                     rx.GetCollectedPackets() == Packets{"good"});
    passed &= expect("corrupt repeat counted", rx.GetNumOfFailedParts() == 1);
  }

  // StartPacket() twice with no parts in between.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.StartPacket();
    passed &= expect("two starts, no parts -> empty packets",
                     rx.GetCollectedPackets() == (Packets{"", ""}));

    rx.ReceivePart(0, Sum("late"), "late");
    passed &= expect("part lands in the packet still open",
                     rx.GetCollectedPackets() == (Packets{"", "late"}));
  }

  // Failures accumulate across packets, not per packet.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(0, BadSum("x"), "x");
    rx.StartPacket();
    rx.ReceivePart(0, BadSum("y"), "y");
    rx.ReceivePart(1, BadSum("z"), "z");
    passed &= expect("failures counted across all packets",
                     rx.GetNumOfFailedParts() == 3);
    passed &= expect("both packets empty",
                     rx.GetCollectedPackets() == (Packets{"", ""}));
  }

  // Sparse / non-contiguous ids still concatenate in ascending order.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(1000, Sum("Z"), "Z");
    rx.ReceivePart(7, Sum("M"), "M");
    rx.ReceivePart(0, Sum("A"), "A");
    passed &= expect("gaps in ids are fine",
                     rx.GetCollectedPackets() == Packets{"AMZ"});
  }

  // GetCollectedPackets() is const and must not consume state.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(0, Sum("stable"), "stable");
    const Packets first = rx.GetCollectedPackets();
    const Packets second = rx.GetCollectedPackets();
    passed &= expect("repeated collection is identical", first == second);
    passed &= expect("collection did not consume", second == Packets{"stable"});
  }

  // An empty payload is a legitimate part.
  {
    PacketReceiver rx;
    rx.StartPacket();
    passed &= expect("empty payload accepted", rx.ReceivePart(1, Sum(""), ""));
    rx.ReceivePart(0, Sum("only"), "only");
    passed &= expect("empty payload adds nothing",
                     rx.GetCollectedPackets() == Packets{"only"});
    passed &=
        expect("empty payload is not a failure", rx.GetNumOfFailedParts() == 0);
  }

  // uint16_t boundary ids must order correctly.
  {
    PacketReceiver rx;
    rx.StartPacket();
    rx.ReceivePart(65535, Sum("last"), "last");
    rx.ReceivePart(0, Sum("first "), "first ");
    passed &= expect("uint16 bounds order correctly",
                     rx.GetCollectedPackets() == Packets{"first last"});
  }

  return passed;
}

}  // namespace

#ifndef RunTests
int main() {
  if (doTestsPass()) {
    std::cout << "ALL TESTS PASS." << std::endl;
  } else {
    std::cout << "TESTS FAILED." << std::endl;
  }
  return 0;
}
#endif
