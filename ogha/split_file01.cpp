#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Record {
    string type;
    string symbol;
    int price;
    int quantity;
    string expirydate;
    int strikeprice;
    string amendtime;
    int id;
    int parentid;
};

void splitFile(const string& filePath, int X) {
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cout << "Failed to open input file." << endl;
        return;
    }

    string line;
    vector<Record> records;
    map<int, vector<Record>> parentToChildren;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string type, symbol, expirydate, amendtime;
        int price, quantity, strikeprice, id, parentid;
        char comma;
        if (iss >> type >> comma >> symbol >> comma >> price >> comma >> quantity >> comma
            >> expirydate >> comma >> strikeprice >> comma >> amendtime >> comma
            >> id >> comma >> parentid) {
            Record record = { type, symbol, price, quantity, expirydate, strikeprice, amendtime, id, parentid };
            records.push_back(record);
            if (type == "P") {
                parentToChildren[parentid].push_back(record);
            }
        } else {
            cout << "Failed to parse line: " << line << endl;
        }
    }
    inFile.close();

    int numFiles = (records.size() + X - 1) / X;
    for (int i = 0; i < numFiles; i++) {
        stringstream ss;
        ss << "output_" << i + 1 << ".txt";
        string outputFile = ss.str();
        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cout << "Failed to create output file: " << outputFile << endl;
            continue;
        }

        int count = 0;
        int start = i * X;
        int end = min(start + X, static_cast<int>(records.size()));
        for (int j = start; j < end; j++) {
            const Record& record = records[j];
            outFile << record.type << "," << record.symbol << "," << record.price << ","
                    << record.quantity << "," << record.expirydate << "," << record.strikeprice << ","
                    << record.amendtime << "," << record.id << "," << record.parentid << endl;
            count++;
            if (record.type == "T" && parentToChildren.find(record.id) != parentToChildren.end()) {
                const vector<Record>& children = parentToChildren[record.id];
                for (const Record& child : children) {
                    outFile << child.type << "," << child.symbol << "," << child.price << ","
                            << child.quantity << "," << child.expirydate << "," << child.strikeprice << ","
                            << child.amendtime << "," << child.id << "," << child.parentid << endl;
                    count++;
                }
            }
        }

        outFile.close();
        cout << "Created output file: " << outputFile << " with " << count << " records." << endl;
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
