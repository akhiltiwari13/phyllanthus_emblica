#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct OrderData {
  long long timestamp;
  std::string symbol;
  std::string subType;
  int orderId;
};

struct AckData {
  long long requestTimestamp;
  long long ackLatency;
  std::string subType;
  std::string symbol;
  int orderId;
};

// Function to extract substrings based on a delimiter
std::vector<std::string> split(const std::string &str, char delim) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delim)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Function to safely convert a string to a long long, with error handling
long long safe_stoll(const std::string &str) {
  try {
    return std::stoll(str);
  } catch (const std::exception &e) {
    std::cerr << "Conversion error: " << e.what() << " for string: " << str
              << std::endl;
    return 0;
  }
}

// Function to safely convert a string to an int, with error handling
int safe_stoi(const std::string &str) {
  try {
    return std::stoi(str);
  } catch (const std::exception &e) {
    std::cerr << "Conversion error: " << e.what() << " for string: " << str
              << std::endl;
    return 0;
  }
}

int main() {
  std::unordered_map<int, OrderData> requests;
  std::unordered_map<int, OrderData> responses;
  std::vector<AckData> latencies;
  std::string line;

  while (std::getline(std::cin, line) && !line.empty()) {
    auto tokens = split(line, '|');
    if (tokens.size() < 5) {
      /* std::cerr << "Invalid log entry: " << line << std::endl; */
      continue;
    }

    bool isRequest = tokens[0].find("REQUEST") != std::string::npos;
    std::string symbol = tokens[1].substr(tokens[1].find(':') + 1);
    long long timestamp = safe_stoll(tokens[2].substr(tokens[2].find(':') + 1));
    std::string subType = tokens[3].substr(tokens[3].find(':') + 1);
    int orderId = safe_stoi(tokens[4].substr(tokens[4].find(':') + 1));

    if (isRequest) {
      requests[orderId] = {timestamp, symbol, subType, orderId};
    } else {
      auto it = requests.find(orderId);
      // responses[orderId] = {timestamp, symbol, subType, orderId};
      if (it != requests.end()) {
        AckData ack = {it->second.timestamp, timestamp - it->second.timestamp,
                       it->second.subType, it->second.symbol, orderId};
        latencies.push_back(ack);
        requests.erase(it);
      }
    }
  }

  // Sort the latencies based on request timestamp
  std::sort(latencies.begin(), latencies.end(),
            [](const AckData &a, const AckData &b) {
              return a.requestTimestamp < b.requestTimestamp;
            });

  // Print the count of latencies and each latency in the specified format
  std::cout << latencies.size() << std::endl;
  for (const auto &ack : latencies) {
    std::cout << ack.requestTimestamp << ',' << ack.ackLatency << ','
              << ack.subType << ',' << ack.symbol << ',' << ack.orderId
              << std::endl;
  }

  return 0;
}
