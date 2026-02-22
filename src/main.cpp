#include <iostream>
#include <string>
#include <vector>
#include "../analyzer.h"
using namespace std;

int main() {
    const string inputFileName = "input.txt";
    const string backupFileName = "frequency.dat";

    GroceryTracker tracker;

    if (!tracker.LoadFromFile(inputFileName)) {
        // if the file isn't found, tell the user and stop.
        cerr << "Error: Could not open input file: " << inputFileName << '\n';
        return 1;
    }

    // Create backup file at program start
    tracker.WriteBackupFile(backupFileName);

    while (true) {
        PrintMenu();
        int choice = ReadMenuChoice();

        if (choice == 1) {
            cout << "Enter the item to look for: ";
            string item;
            getline(cin, item);

            cout << tracker.GetFrequency(item) << '\n';
        }
        else if (choice == 2) {
            tracker.PrintAllFrequencies();
        }
        else if (choice == 3) {
            tracker.PrintHistogram('*');
        }
        else {
            cout << "Goodbye.\n";
            break;
        }
    }

    return 0;
}