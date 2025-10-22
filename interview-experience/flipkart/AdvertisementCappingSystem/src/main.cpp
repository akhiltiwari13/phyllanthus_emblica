#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include <ostream>

/* #include <CampaignProcessor.h> */

using json = nlohmann::json;
using namespace std;

enum class eventType { EDIT, SERVED, VIEWED };

struct vsVal {
  unsigned int count;
};

struct editVal {
  unsigned long budget;
  unsigned int cost;
  unsigned int count;
  std::string campId;
};

union eventVal {
  struct vsVal;
  struct editVal;
};

struct campaign {
  unsigned long timestamp; //@todo- may need to change to chrono::time
  unsigned int id;
  std::string event;
  eventVal val; // union for value type.
};
std::ostream &operator<<(std::ostream &out, const campaign &cmpgn) {
  return out << cmpgn.timestamp << " | " << cmpgn.id << " | " << cmpgn.event
             << " | ";
}

void parseCampaignInfo(nlohmann::json j) {}

class AdCapProcessor {
public:
  void ParsePacket(nlohmann::json ad_pkt) {
    campaign cmpgn;
    from_json(ad_pkt, cmpgn);
    std::cout << cmpgn << std::endl;
  }

private:
  /* parse campaign data and update the budget map. */
  std::unordered_map<std::string, unsigned long> bugdet_map;

  void from_json(const nlohmann::json &j, campaign &cmpgn) {
    j.at("timeStamp").get_to(cmpgn.timestamp);
    j.at("id").get_to(cmpgn.id);
    j.at("eventType").get_to(cmpgn.event);
  }
};

int main() {
  // read a JSON file
  /* std::ifstream i("input.json"); */
  std::ifstream i("sample.json");
  json j;
  i >> j;

  // write prettified JSON to another file
  std::cout << "log json" << std::endl;
  /* std::ofstream o("pretty.json"); */
  /* o << std::setw(4) << j << std::endl; */
  /* std::cout << std::setw(4) << j << std::endl; */
  cap_proc::AdCapProcessor capProcessor;
  for (auto i : j) {
    /* std::cout << "element" << std::endl; */
    /* std::cout << std::setw(4) << i << std::endl; */
      capProcessor.ParsePacket(i);
  }
  return 0;
}
