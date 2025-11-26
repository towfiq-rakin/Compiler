#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void trimLeading(string &str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start != string::npos) {
        str = str.substr(start);
    } else {
        str.clear();
    }
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    bool flag = false; // Tracks state inside multi-line comments
    string line;

    cout << "Analyzing lines from input.txt:\n" << endl;

    while (getline(file, line)) {
        trimLeading(line);
        
        if (line.empty()) continue;

        if (line.substr(0, 2) == "//") {
            cout << "Line: \"" << line 
                 << "\"\n This is a single-line comment.\n" << endl;
        } 
        else if (line.substr(0, 2) == "/*" && line.find("*/") != string::npos) {
            cout << "Line: \"" << line 
                 << "\"\n This is a complete multi-line comment in one line.\n" << endl;
        } 
        else if (line.substr(0, 2) == "/*") {
            cout << "Line: \"" << line 
                 << "\"\n This is the start of a multi-line comment.\n" << endl;
            flag = true;
        } 
        else if (line.find("*/") != string::npos) {
            cout << "Line: \"" << line 
                 << "\"\n This is the end of a multi-line comment.\n" << endl;
            flag = false;
        } 
        else if (flag) {
            cout << "Line: \"" << line 
                 << "\"\n This is a comment inside a multi-line comment.\n" << endl;
        } 
        else {
            cout << "Line: \"" << line 
                 << "\"\n This is NOT a comment.\n" << endl;
        }
    }

    file.close();
    return 0;
}
