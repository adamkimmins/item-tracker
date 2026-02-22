# Item Tracker  
This project is a C++ console application that analyzes a grocery purchase list from a text file and reports how often each item appears.
It supports three user actions:  
1) Look up a single item’s frequency
2) Print all item frequencies
3) Display a histogram of item counts
### How to Build and Run  
```
git clone https://github.com/adamkimmins/item-tracker.git  
```
From repo root:
```
g++ tracker.cpp src/main.cpp -o item-tracker  
.\item-tracker.exe  
```
### Output Files  
`frequency.dat` is generated on program start.  

### Reflection  
This project solves the problem of turning a raw list of grocery items into meaningful data. 
Instead of manually counting how many times each item appears, the program reads the file, normalizes input to handle different capitalization, stores results in a map, 
and provides an interactive menu so a user can query and visualize item counts.

#### "What does this program do particularly well?"
I designed the program to be easy to use and resilient to common input issues. 
Item lookups are case-insensitive, and whitespace is trimmed so user input like " spinach " still works. 
I also separated the core tracking logic (file parsing, counting, reporting) into tracker.h/.cpp and kept UI concerns in main.cpp, 
which makes the code cleaner and easier to maintain.

#### "Where could you enhance your code?"
There are several improvements I could make:  
Performance / scalability: For very large inputs, switching from std::map to std::unordered_map would reduce average lookup/insert time from O(log n) to O(1) and improve speed. 
Although not necessary at this scale, when considering future use this would make the program much more robust.

Testing: Adding unit tests for normalization (Trim, ToLower) and counting logic would improve reliability and make future refactors safer.

#### "Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?"
The most challenging part was making user input behave consistently. Mixing cin >> with getline() can cause skipped input because of leftover newline characters in the stream. 
I overcame this by validating menu input and clearing the input buffer using cin.ignore(...) after reading the menu choice.

To strengthen my support network, I’m using:
  - C++ reference resources: cppreference documentation, stackoverflow, student resources (zyBooks)  
  - Compiler warnings (-Wall -Wextra) as a standard habit  
  - Debugging tools and practices (stepping through logic in a debugger, using consistent input validation patterns)

#### "What skills from this project will be particularly transferable to other projects or course work?"
Building a clean, menu-driven CLI program  
File I/O and error handling  
Using data structures appropriately (maps for counting/frequency tables)  
Input sanitation and normalization (trimming, case folding)  
Separating logic into reusable components (.h/.cpp) for maintainability  

#### "How did you make this program maintainable, readable, and adaptable?"  
I focused on readability by using clear function names, small single-purpose methods, and consistent formatting. 
The tracking logic is encapsulated in a GroceryTracker class with a simple public interface, so main.cpp doesn’t need to know implementation details. 
By splitting declarations into tracker.h and implementation into tracker.cpp, it becomes easier to expand the program later without rewriting the core logic.
