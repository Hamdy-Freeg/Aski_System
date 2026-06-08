# Aski_Sytem
A command-line interface application written in C++ that simulates the core features of the Ask.fm platform. The system allows users to ask questions publicly or anonymously, answer questions, and view nested discussion threads, utilizing a CSV-based data persistence layer.

---

## Project Structure

The project is structured following modern C++ best practices, separating interfaces (Headers) from execution logic (Implementation):

```text
.
├── CMakeLists.txt        # CMake build configuration file
|
├── include/              # Header files (.h)
│   ├── AskiSystem.h      # Main system coordinator and menu loop
│   ├── DatabaseManager.h # Handles I/O operations for CSV files
│   ├── User.h            # User data structure (User Struct)
│   └── Question.h        # Question data structure (Question Struct)
├── src/                  # Implementation files (.cpp)
│   ├── AskiSystem.cpp    # Implementation of menus and validation logic
│   └── DatabaseManager.cpp # Implementation of CSV read/write operations
|   |__ main.cpp            # Application entry point
|
└── data/                 # storage directory
    ├── users.csv         # Stores user account information
    └── questions.csv     # Stores questions, answers, and threads
```


## Build and Run Instructions

The project uses CMake to manage the compilation process, making it cross-platform compatible.

To build and run the application, open your terminal in the project's root directory and run the following commands:

``` bash 
mkdir build && cd build
cmake ..
make
./Aski_System
```
---

## Application Features

The application provides a straightforward two-tier menu system based on the user's state:

### Guest Options
* Access your personal profile "Login".
* Register a new account on the system "Sign up".
* Terminate the program

### Registered User Options
* Coming Questions: View and manage questions sent to your profile.
* Questions From Me: Track all questions you have sent to others.
* Answer Question: Respond to pending questions directed to you.
* Delete Question: Remove a question along with all its nested thread replies.
* Ask Question: Send a question to another user, with an optional anonymous flag.
* List System Users: Browse registered profiles to discover user IDs.
* Feed: View a public wall of all answered questions across the system.
* Logout: Securely sign out and save your progress.

---

## Technical Implementations and Highlights

This project applies core programming concepts and optimized data structures to ensure clean memory management and reliable performance:

* Object-Oriented Programming (OOP): Designed with strict encapsulation and separation of concerns, decoupling interface management from data access.

* In-Memory Indexing: Utilizes index mapping to retrieve question positions instantly, achieving O(1) lookup times and avoiding expensive sequential scans.

* Thread Tracking via Graphs: Models nested discussion threads using an adjacency list structure. This optimizes feed generation and thread traversal to linear time O(N), eliminating nested loops.

* Binary Search Validation: Leverages sorted user records to validate recipient IDs efficiently in O(log N) time before sending questions.

* Data Persistence: Implements robust file handling using append modes for efficient entry creation and safe full overwrites to prevent data corruption during edits.

* Input Validation: Protects the application from unexpected crashes and infinite loops by filtering invalid input types.
