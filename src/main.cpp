#include <iostream>
#include <string>
#include <limits>
#include "../tracker.h"

static void PrintMenu() {
    std::cout << "\n===== Corner Grocer Menu =====\n";
    std::cout << "1. Look up an item frequency\n";
    std::cout << "2. Print all item frequencies\n";
    std::cout << "3. Print histogram\n";
    std::cout << "4. Exit\n";
    std::cout << "Select an option (1-4): ";
}

static int ReadMenuChoice() {
    int choice;
    while (true) {
        if (std::cin >> choice && choice >= 1 && choice <= 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Enter a number 1-4: ";
    }
}

int main() {
    const std::string inputFileName = "input.txt";
    const std::string backupFileName = "frequency.dat";

    GroceryTracker tracker;

    if (!tracker.LoadFromFile(inputFileName)) {
        std::cerr << "Error: Could not open input file: " << inputFileName << '\n';
        return 1;
    }

    if (!tracker.WriteBackupFile(backupFileName)) {
        std::cerr << "Warning: Could not write backup file: " << backupFileName << '\n';
    }

    while (true) {
        PrintMenu();
        int choice = ReadMenuChoice();

        if (choice == 1) {
            std::cout << "Enter the item to look for: ";
            std::string item;
            std::getline(std::cin, item);

            std::cout << tracker.GetFrequency(item) << '\n';
        }
        else if (choice == 2) {
            tracker.PrintAllFrequencies();
        }
        else if (choice == 3) {
            tracker.PrintHistogram('*');
        }
        else {
            std::cout << "Goodbye.\n";
            break;
        }
    }

    return 0;
}