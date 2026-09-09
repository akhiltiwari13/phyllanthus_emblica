/**
 * @file q01_packet_receiver.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief tt-guj-2026 q01 — PacketReceiver implementation.
 *
 * @version 0.2
 * @date 2026-09-10
 * @copyright Copyright (c) 2026
 */

#include "q01_packet_receiver.h"

#include <functional>
#include <utility>

void PacketReceiver::StartPacket() { packets_.emplace_back(); }

bool PacketReceiver::ReceivePart(std::uint16_t id, std::size_t controlsum,
                                 const std::string& data) {
  if (packets_.empty()) {  // no StartPacket() yet: nothing to collect into
    ++failed_parts_;
    return false;
  }

  // Verify BEFORE storing, so a corrupt repeat is counted as failed and leaves
  // the good part it would have replaced untouched — letting corruption clobber
  // already-verified data would be a defect.
  if (ControlSumOf(data) != controlsum) {
    ++failed_parts_;
    return false;
  }

  packets_.back()[id] = data;  // a repeated id overwrites
  return true;
}

std::vector<std::string> PacketReceiver::GetCollectedPackets() const {
  std::vector<std::string> collected;
  collected.reserve(packets_.size());

  // The packet currently open is included: the alternative — returning only
  // packets closed by a later StartPacket() — would make the ordinary
  // StartPacket/ReceivePart/GetCollectedPackets sequence return nothing.
  for (const Packet& packet : packets_) {
    std::size_t total = 0;
    for (const auto& part : packet) total += part.second.size();

    std::string merged;
    merged.reserve(total);  // one allocation per packet, not one per part
    for (const auto& part : packet) merged += part.second;

    collected.push_back(std::move(merged));
  }
  return collected;
}

std::size_t PacketReceiver::GetNumOfFailedParts() const noexcept {
  return failed_parts_;
}

std::size_t PacketReceiver::ControlSumOf(const std::string& data) {
  return std::hash<std::string>{}(data);
}
