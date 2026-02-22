#include "tracker.h"

#include <fstream>
#include <cctype>

bool GroceryTracker::LoadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }

    items.clear();

    std::string line;
    while (std::getline(inFile, line)) {
        line = Trim(line);
        if (line.empty()) {
            continue;
        }

        std::string key = ToLower(line);

        auto it = items.find(key);
        if (it == items.end()) {
            items[key] = { line, 1 };
        } else {
            it->second.count += 1;
        }
    }

    return true;
}

bool GroceryTracker::WriteBackupFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }

    for (const auto& kv : items) {
        outFile << kv.second.displayName << " " << kv.second.count << '\n';
    }
    return true;
}

int GroceryTracker::GetFrequency(const std::string& item) const {
    std::string key = ToLower(Trim(item));
    auto it = items.find(key);
    if (it == items.end()) {
        return 0;
    }
    return it->second.count;
}

void GroceryTracker::PrintAllFrequencies(std::ostream& out) const {
    for (const auto& kv : items) {
        out << kv.second.displayName << " " << kv.second.count << '\n';
    }
}

void GroceryTracker::PrintHistogram(char symbol, std::ostream& out) const {
    for (const auto& kv : items) {
        out << kv.second.displayName << " " << std::string(kv.second.count, symbol) << '\n';
    }
}

std::string GroceryTracker::Trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }

    return s.substr(start, end - start);
}

std::string GroceryTracker::ToLower(std::string s) {
    for (char& ch : s) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return s;
}