#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct LogEntry {
    long long timestamp;
    std::string symbol;
    std::string subType;
};

struct AckData {
    long long requestTimestamp;
    long long ackLatency;
    std::string subType;
    std::string symbol;
};

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> elements;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        elements.push_back(item);
    }
    return elements;
}

int main() {
    std::unordered_map<int, std::vector<LogEntry>> requestMap;
    std::unordered_map<int, std::vector<LogEntry>> responseMap;
    std::vector<AckData> ackDataList;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty()) {
        std::vector<std::string> parts = split(line, '|');
        if (parts.size() != 5) {
            continue; // Skip invalid lines
        }

        std::string type = parts[0];
        std::string symbol = split(parts[1], ':')[1];
        long long timestamp = std::stoll(split(parts[2], ':')[1]);
        std::string subType = split(parts[3], ':')[1];
        int orderId = std::stoi(split(parts[4], ':')[1]);

        if (type.find("REQUEST") != std::string::npos) {
            requestMap[orderId].push_back({timestamp, symbol, subType});
        } else {
            responseMap[orderId].push_back({timestamp, symbol, subType});
        }
    }

    for (auto& reqPair : requestMap) {
        int orderId = reqPair.first;
        auto& reqList = reqPair.second;
        auto& resList = responseMap[orderId];

        for (size_t i = 0; i < reqList.size(); ++i) {
            if (i < resList.size()) {
                // Calculate the ack latency
                long long latency = resList[i].timestamp - reqList[i].timestamp;
                ackDataList.push_back({reqList[i].timestamp, latency, reqList[i].subType, reqList[i].symbol});
            }
        }
    }

    // Sort the ack data list by request timestamp
    std::sort(ackDataList.begin(), ackDataList.end(), [](const AckData& a, const AckData& b) {
        return a.requestTimestamp < b.requestTimestamp;
    });

    // Output the total number of latencies and the details
    std::cout << ackDataList.size() << std::endl;
    for (const auto& ack : ackDataList) {
        std::cout << ack.requestTimestamp << ',' << ack.ackLatency << ',' << ack.subType << ',' << ack.symbol << std::endl;
    }

    return 0;
}

