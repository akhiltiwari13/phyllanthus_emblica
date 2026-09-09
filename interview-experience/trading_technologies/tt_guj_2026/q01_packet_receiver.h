/**
 * @file q01_packet_receiver.h
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief tt-guj-2026 q01 — reassemble multi-part packets arriving out of order.
 *
 * Messages arrive over a network split into parts. The application is notified
 * when a new packet starts, then receives that packet's parts in ANY order; the
 * next start notification ends the current packet and opens the next. Parts
 * carry a control sum and may be corrupt, or may arrive with no packet open —
 * either way they count as failed.
 *
 * The public API was given by the interviewer and is reproduced verbatim.
 * Control sum is std::hash<std::string>.
 *
 * @version 0.2
 * @date 2026-09-10
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class PacketReceiver {
 public:
  /// Ends the packet currently being assembled and opens a new one. Must be
  /// called at least once before any part can be collected.
  void StartPacket();

  /// Verifies one part and files it under the open packet.
  ///
  /// @param id          the part's position within the final packet
  /// @param controlsum  std::hash<std::string> of @p data
  /// @param data        the part's payload
  /// @return true if the part was accepted, false if it failed — either no
  ///         packet is open, or the control sum did not match.
  ///
  /// A repeated @p id overwrites the part already held.
  bool ReceivePart(std::uint16_t id, std::size_t controlsum,
                   const std::string& data);

  /// Builds every packet by concatenating its parts in ascending id order.
  std::vector<std::string> GetCollectedPackets() const;

  /// Failed parts across ALL packets, not just the one currently open.
  std::size_t GetNumOfFailedParts() const noexcept;

 private:
  // Ordered by id, so the merge order is free, a repeated id is a plain
  // assignment, and sparse or non-contiguous ids cost nothing extra.
  //
  // Trade-off, if asked: std::map is O(log n) per part with a pointer chase per
  // node. With dense ids a std::vector<std::string> indexed by id would be O(1)
  // and cache-friendly; with sparse ids an unordered_map plus a single sort at
  // collection time would beat both. std::map is chosen here because it stays
  // correct for any id distribution without special-casing.
  using Packet = std::map<std::uint16_t, std::string>;

  static std::size_t ControlSumOf(const std::string& data);

  // Non-empty exactly when StartPacket() has been called at least once, so no
  // separate "started" flag is needed.
  std::vector<Packet> packets_;
  std::size_t failed_parts_ = 0;
};
