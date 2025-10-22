#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <fstream>
#include <cereal/archives/json.hpp>

// Saving to JSON
void saveJson() {
    std::ofstream os("data.json");
    cereal::JSONOutputArchive archive(os);
    
    MyData data{10, 20.5f, "hello"};
    archive(cereal::make_nvp("myData", data));
}

struct MyData {
    int x;
    float y;
    std::string z;
    
    // Serialization method
    template<class Archive>
    void serialize(Archive & archive) {
        archive(x, y, z);
    }
};

// Saving to a file
void save() {
    std::ofstream os("data.cereal", std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    
    MyData data{10, 20.5f, "hello"};
    archive(data);
}

// Loading from a file
void load() {
    std::ifstream is("data.cereal", std::ios::binary);
    cereal::BinaryInputArchive archive(is);
    
    MyData data;
    archive(data);
}

int main {


  return 0;
}
