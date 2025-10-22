// #include <bits/stdc++.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'Paragraph' class below.
 * 
 * Paragraph(string text, int width)
 * output()
 * 
 */
class Paragraph{
  public: 
    vector<string>paragraph;
    Paragraph(string text, int width){
        // Complete the code
         for (int i = 0; i < static_cast<int>(text.size()); i += width) {
            paragraph.push_back(text.substr(i, width));
        }
    }
    vector<string>output(){
        //complete the code
        return paragraph;
    }
};

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string text;
    getline(cin, text);

    string width_temp;
    getline(cin, width_temp);

    int width = stoi(ltrim(rtrim(width_temp)));
    Paragraph object(text,width);
    vector<string> result = object.output();

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];
        cout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
            cout << std::endl;
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](char c){return !std::isspace(static_cast<unsigned char>(c));})
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](char c){return !std::isspace(static_cast<unsigned char>(c));}).base(),
        s.end()
    );

    return s;
}
