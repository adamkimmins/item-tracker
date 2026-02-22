#pragma once

#include <map>
#include <string>
#include <iostream>

class GroceryTracker {
public:
    bool LoadFromFile(const std::string& filename);
    bool WriteBackupFile(const std::string& filename) const;

    // Option 1
    int GetFrequency(const std::string& item) const;

    // Option 2
    void PrintAllFrequencies(std::ostream& out = std::cout) const;

    // Option 3
    void PrintHistogram(char symbol = '*', std::ostream& out = std::cout) const;

private:
    struct ItemInfo {
        std::string displayName;
        int count = 0;
    };

    std::map<std::string, ItemInfo> items;

    static std::string Trim(const std::string& s);
    static std::string ToLower(std::string s);
};