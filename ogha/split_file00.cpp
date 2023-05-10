#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

struct Record {
    std::string type;
    std::string symbol;
    double price;
    int quantity;
    std::string expirydate;
    double strikeprice;
    std::string amendtime;
    int id;
    int parentid;
};

bool isParentRecord(const Record& record){
    return record.type == "T";
}

void parseRecord(const std::string& line, Record& record) {
    std::stringstream ss(line);
    std::string field;

    std::getline(ss, field, ',');
    record.type = field;

    std::getline(ss, field, ',');
    record.symbol = field;

    std::getline(ss, field, ',');
    record.price = std::stod(field);

    std::getline(ss, field, ',');
    record.quantity = std::stoi(field);

    std::getline(ss, field, ',');
    record.expirydate = field;

    std::getline(ss, field, ',');
    record.strikeprice = std::stod(field);

    std::getline(ss, field, ',');
    record.amendtime = field;

    std::getline(ss, field, ',');
    record.id = std::stoi(field);

    std::getline(ss, field, ',');
    record.parentid = std::stoi(field);
}

void writeRecord(const Record& record, std::ofstream& file) {
    file << record.type << ','
         << record.symbol << ','
         << record.price << ','
         << record.quantity << ','
         << record.expirydate << ','
         << record.strikeprice << ','
         << record.amendtime << ','
         << record.id << ','
         << record.parentid << '\n';
}

void splitFile(const std::string& filepath, int X) {
    std::ifstream infile(filepath);
    if (!infile) {
        std::cerr << "Failed to open input file\n";
        return;
    }

    std::unordered_map<int, std::vector<Record>> groups;
    std::string line;
    while (std::getline(infile, line)) {
        Record record;
        parseRecord(line, record);
        if(isParentRecord(record))
            groups[record.id].push_back(record);
        else
            groups[record.parentid].push_back(record);
    }

    int i = 0;
    for (const auto& [parentid, records] : groups) {
        std::string outfilepath = "output_" + std::to_string(i) + ".csv";
        std::ofstream outfile(outfilepath);
        if (!outfile) {
            std::cerr << "Failed to create output file\n";
            return;
        }

        int j = 0;
        for (const auto& record : records) {
            writeRecord(record, outfile);
            j++;
            if (j >= X && isParentRecord(record)) {
                // Start a new file if we have written X records and
                // the current record is a parent
                outfile.close();
                i++;
                outfilepath = "output_" + std::to_string(i) + ".csv";
                outfile.open(outfilepath);
                if (!outfile) {
                    std::cerr << "Failed to create output file\n";
                    return;
                }
                j = 0;
            }
        }

        outfile.close();
        i++;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <file> <X>\n";
        return 1;
    }

    std::string filepath{argv[1]};

    // perform splitting
    splitFile(filepath, int{*argv[2]});

    return 0;
}
