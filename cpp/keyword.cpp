#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

// Keywords vector formatted for readability
vector<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "inline", "int", "long", "register", "restrict", "return", "short", 
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", 
    "unsigned", "void", "volatile", "while", "class", "public", "private", 
    "protected", "virtual", "template", "typename", "try", "catch", "new", 
    "delete", "namespace", "using", "this", "throw", "bool", "true", "false"
};

bool isKeyword(const string &word) {
    for (const string &kw : keywords) {
        if (word == kw) return true;
    }
    return false;
}

bool isValidIdentifier(const string &id) {
    if (id.empty()) return false;

    // Check first character (must be a letter or underscore)
    if (!isalpha(id[0]) && id[0] != '_') return false;

    // Check remaining characters (must be alphanumeric or underscore)
    for (size_t i = 1; i < id.length(); i++) {
        if (!isalnum(id[i]) && id[i] != '_') return false;
    }

    // Check against reserved keywords
    if (isKeyword(id)) return false;

    return true;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open input.txt\n";
        return 1;
    }

    string line;
    cout << "Identifier Check Results:\n";

    while (getline(file, line)) {
        size_t start = line.find_first_not_of(" \t\n\r");
        size_t end = line.find_last_not_of(" \t\n\r");

        if (start == string::npos) {
            continue;
        }

        // Extract the trimmed string (corrected '‐' to '-')
        string identifier = line.substr(start, end - start + 1);

        if (isValidIdentifier(identifier)) {
            cout << identifier << " --> VALID IDENTIFIER\n";
        } else {
            cout << identifier << " --> INVALID IDENTIFIER\n";
        }
    }

    file.close();
    return 0;
}
