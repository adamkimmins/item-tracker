#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

class GroceryTracker {
public:
    bool LoadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            return false;
        }

        string line;
        while (getline(inFile, line)) {
            line = Trim(line);
            if (line.empty()) {
                continue;
            }

            string key = ToLower(line);

            auto it = items.find(key);
            if (it == items.end()) {
                items[key] = { line, 1 };
            } else {
                it->second.count += 1;
            }
        }
        return true;
    }

    bool WriteBackupFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            return false;
        }

        for (const auto& kv : items) {
            outFile << kv.second.displayName << " " << kv.second.count << '\n';
        }
        return true;
    }
       
    // Option 1
    int GetFrequency(const string& item) const {
        string key = ToLower(Trim(item));
        auto it = items.find(key);
        if (it == items.end()) {
            return 0;
        }
        return it->second.count;
    }

    // Option 2
    void PrintAllFrequencies() const {
        for (const auto& kv : items) {
            cout << kv.second.displayName << " " << kv.second.count << '\n';
        }
    }

    // Option 3
    void PrintHistogram(char symbol = '*') const {
        for (const auto& kv : items) {
            cout << kv.second.displayName << " " << string(kv.second.count, symbol) << '\n';
        }
    }

private:
    struct ItemInfo {
        string displayName;
        int count;
    };

    map<string, ItemInfo> items;

    static string Trim(const string& s) {
        size_t start = 0;
        while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
            ++start;
        }
        size_t end = s.size();
        while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
            --end;
        }
        return s.substr(start, end - start);
    }

    static string ToLower(string s) {
        for (char& ch : s) {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
        return s;
    }
};

static void PrintMenu() {
    cout << "\n===== Corner Grocer Menu =====\n";
    cout << "1. Look up an item frequency\n";
    cout << "2. Print all item frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
    cout << "Select an option (1-4): ";
}

static int ReadMenuChoice() {
    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 4) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Enter a number 1-4: ";
    }
}