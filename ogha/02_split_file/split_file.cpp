#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Record {
    std::string type;
    std::string symbol;
    std::string id;
    std::string parentid;
    std::string record_data; //this has the record

    Record(string type_, string symbol_, string id_, string parentid_, string record_data_):type(type_),symbol(symbol_),id(id_),parentid(parentid_),record_data(record_data_){
    }

    Record():type(""),symbol(""),id(""),parentid(""),record_data(""){
    }
};


bool isParentRecord(const Record& record){
   return record.type == "T";
}

void splitFile(const std::string& filePath, int X) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open input file\n";
        return;
    }

    std::unordered_map<std::string, std::vector<Record>> parentChildRecordLookup;
    int totalRecordsToWrite{};

    // Read and save records to an in-memory cache!
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string type, symbol, price, id, parentid;
        std::getline(ss, type, ',');
        std::getline(ss, symbol, ',');
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        std::getline(ss, id, ',');
        std::getline(ss, parentid);

        Record rcrd{type,symbol,id,parentid,line};

        if (isParentRecord(rcrd)) {
            parentChildRecordLookup[rcrd.id].push_back(rcrd);
        }else{
            parentChildRecordLookup[rcrd.parentid].push_back(rcrd);
        }

        ++totalRecordsToWrite;
    }
    inFile.close();

    int fileIdx = 0;
    int recordCount = 0;
    std::ofstream outFile;

    for (const auto& rcrds : parentChildRecordLookup) {
        if ((recordCount == 0 || recordCount >= X) && totalRecordsToWrite  >= X ) { //check for creating a new output file!
            if (outFile.is_open()) {
                outFile.close();
            }
            outFile.open("output" + std::to_string(fileIdx) + ".txt");
            if (!outFile.is_open()) {
                std::cerr << "Failed to open output file\n";
                return;
            }
            fileIdx++;
            recordCount = 0;
        }

        for(auto rcrd: rcrds.second){
            outFile << rcrd.record_data << '\n';
            recordCount++;
            totalRecordsToWrite -= recordCount;
        }

    }

    if (outFile.is_open()) {
        outFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file path> <minimum number of records in a file>\n";
        return 1;
    }

    splitFile(argv[1], std::stoi(argv[2]));
    return 0;
}


