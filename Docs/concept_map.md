# Vehicle Management System (VMS) - Architectural & Language Concept Map

This document outlines the software engineering principles, C++ core features, and architectural design patterns utilized in the **Vehicle Management System (VMS)**. It serves as a detailed reference mapping abstract programming concepts to their concrete implementations in the codebase.

---

## Table of Contents
1. [Fundamental C++ Syntax](#1-fundamental-c-syntax)
2. [Object-Oriented Programming (OOP) - Core](#2-object-oriented-programming-oop---core)
3. [Memory Management](#3-memory-management)
4. [Standard Template Library (STL)](#4-standard-template-library-stl)
5. [Modern C++ Features (C++11 and Later)](#5-modern-c-features-c11-and-later)
6. [Project Architecture & Engineering](#6-project-architecture-ux-engineering)

---

## 1. Fundamental C++ Syntax

### Data Types & Variables
*   **What it is:** The basic building blocks for representing and storing data in memory (e.g., `int` for integers, `float` for fractional values, `bool` for conditions, and `std::string` for text).
*   **Where it is used:** Under the `Vehicle` abstract base class declared in [Include/Vehicle.h](../Include/Vehicle.h), variables like `vehicleID` and `model` are stored as `std::string`, `capacity` as `int`, and `rentalRate` as `float`.
*   **Why it is used:** Enforces standard memory allocations and compiler optimizations for distinct properties, ensuring type safety.

### Control Flow
*   **What it is:** Logic structures (`if/else`, `while` loops, `for` loops) that control the execution path of the application.
*   **Where it is used:** 
    *   `if/else` is used inside [Source/MenuHandler.cpp](../Source/MenuHandler.cpp#L144) to evaluate user credentials and route them to either the Admin panel or Customer dashboard.
    *   `while` loops are used in `MenuHandler::runMainMenu()` to sustain the interactive console loop until the user exits.
    *   `for` loops are used in `MenuHandler::handleSearch()` to iterate over the active inventory vector.
*   **Why it is used:** Essential for managing console workflows, validating credentials, routing menu screens, and executing searches.

### Function Overloading
*   **What it is:** Defining multiple functions with the same name but different parameter lists (signatures) in the same scope.
*   **Where it is used:** Under the `Validator` class inside [Source/Validator.cpp](../Source/Validator.cpp#L10-L17):
    ```cpp
    bool Validator::isNonNegative(int value);
    bool Validator::isNonNegative(float value);
    ```
*   **Why it is used:** Provides a unified interface for validation. The compiler automatically calls the correct version based on the data type being checked (e.g., passenger count vs. rental rates), reducing function name bloat.

### Default Arguments
*   **What it is:** Pre-defined values assigned to function parameters in their declaration, allowing callers to omit these arguments.
*   **Where it is used:** Inside the `InputHandler` declarations in [Include/InputHandler.h](../Include/InputHandler.h#L31):
    ```cpp
    int getInt(const std::string& prompt, int min = 0, int max = 1000000, bool allowCancel = false);
    ```
*   **Why it is used:** Simplifies code by providing sensible defaults (like a standard range check and cancel ability) for general inputs, while keeping the flexibility to restrict inputs for specific prompts (e.g., limiting capacity to 1-20 in trip planning).

### Static Members
*   **What it is:** Class members (variables or functions) associated with the class itself rather than individual instances.
*   **Where it is used:**
    *   Every utility function in the `Validator` class (e.g., `Validator::isValidDate`).
    *   All helper methods in `InputHandler` (e.g., `InputHandler::getInt`).
*   **Why it is used:** Groups utility functions logically without forcing the developer to instantiate classes like `Validator` or `InputHandler` repeatedly.

---

## 2. Object-Oriented Programming (OOP) - Core

### Encapsulation
*   **What it is:** Bundling data and methods into a single class unit, restricting direct access via access modifiers (`private` / `protected`), and exposing control via public getters and setters.
*   **Where it is used:** Defined across the base class [Include/Vehicle.h](../Include/Vehicle.h) where state fields like `status` and `rentalRate` are `private`, but exposed through public interfaces like `Vehicle::getStatus()` and `Vehicle::setStatus()`.
*   **Why it is used:** Protects the internal system states from accidental or illegal modification by external components, forcing changes to occur through controlled validation methods.

### Inheritance
*   **What it is:** Creating new classes based on existing ones to establish hierarchical relationships and reuse code logic.
*   **Where it is used:** The core inheritance relationships in VMS are:
    *   `Vehicle` (Base) $\rightarrow$ `Economy`, `Luxury`, `SUV`, `Van` (Derived Categories).
    *   `User` (Base) $\rightarrow$ `Admin`, `Customer` (Derived Roles).
    *   `Transaction` (Base) $\rightarrow$ `RentalTransaction`, `SaleTransaction` (Derived Operations).
*   **Why it is used:** Models real-world entities naturally. It places common parameters (like IDs, models, or names) in the base class while permitting derived classes to introduce specific traits (e.g., specialized features in `Luxury`).

### Polymorphism & Virtual Functions
*   **What it is:** The capability of a single base pointer to execute distinct derived behaviors at runtime, implemented using `virtual` functions and virtual method tables (Vtables).
*   **Where it is used:** Under [Include/Vehicle.h](../Include/Vehicle.h#L46):
    ```cpp
    virtual float calculateCost(int days) = 0;
    ```
    This function is overridden by derived classes to implement distinct billing logic (e.g., `Luxury` might apply rates differently than `Economy`).
*   **Why it is used:** Enables writing generalized client code. Algorithms like searching, trip planning, or billing can operate on generic pointers (`Vehicle*`) without knowing the concrete class type, resolving correct execution paths dynamically.

### Abstract Base Classes
*   **What it is:** A class containing at least one pure virtual function (declared with `= 0`), which cannot be instantiated directly.
*   **Where it is used:** Both `Vehicle` and `User` are abstract base classes, containing pure virtual functions like `Vehicle::getCategory()` and `User::showMenu()`.
*   **Why it is used:** Enforces a interface contract. It guarantees that any subclass added to the fleet or user base implements the mandated system hooks.

### Override Keyword
*   **What it is:** A compiler directive ensuring that a member function overrides a virtual function declared in a base class.
*   **Where it is used:** Inside [Include/Customer.h](../Include/Customer.h#L24):
    ```cpp
    void showMenu() override;
    ```
*   **Why it is used:** Prevents typos or signature mismatches. If the signature of the derived class does not match the base class, the compiler throws an error, averting runtime logical bugs.

### Virtual Destructors
*   **What it is:** A destructor declared as `virtual` in a base class, ensuring subclass destructors are invoked during polymorphic deletions.
*   **Where it is used:** Declared in both [Include/Vehicle.h](../Include/Vehicle.h#L30) and [Include/User.h](../Include/User.h#L32):
    ```cpp
    virtual ~Vehicle();
    ```
*   **Why it is used:** Crucial for preventing memory leaks. If the compiler deletes a `Luxury` car object stored in a `Vehicle*` pointer, a virtual destructor ensures that both the `Luxury` and `Vehicle` scopes are deleted correctly.

---

## 3. Memory Management

### Pointers (Raw Pointers)
*   **What it is:** Variables that store memory addresses of objects rather than the object values.
*   **Where it is used:** Used to build polymorphic collections in [Include/MenuHandler.h](../Include/MenuHandler.h#L22):
    ```cpp
    std::vector<Vehicle*>& fleet;
    ```
*   **Why it is used:** Standard vectors cannot hold abstract objects or objects of varying sizes. Pointers bypass this by holding uniform address lengths, enabling polymorphic behavior in loops and searches.

### References (&)
*   **What it is:** An alias for an existing variable, allowing functions to interact with objects directly without creating copies.
*   **Where it is used:** Passing the fleet or user databases into engines, such as:
    ```cpp
    MenuHandler(std::vector<Vehicle*>& fleet, std::vector<User*>& users, FileHandler& fh);
    ```
*   **Why it is used:** Improves performance. Passing large dynamic arrays or objects by value triggers deep copying, consuming CPU cycles and RAM. References ensure variables are read and edited in-place efficiently.

### Dynamic Memory Allocation (new / delete)
*   **What it is:** Allocating and freeing memory on the system Heap at runtime rather than relying on automatic Stack memory.
*   **Where it is used:**
    *   `new` is used inside [Source/FileHandler.cpp](../Source/FileHandler.cpp#L90) when parsing user or vehicle text files into memory.
    *   `delete` is executed in [Source/Admin.cpp](../Source/Admin.cpp#L154) when customer profiles or vehicles are permanently removed from the system.
*   **Why it is used:** Allows objects to survive beyond the function scope in which they were created. Heap-allocated variables persist until explicitly deleted, which is necessary for databases that remain loaded throughout the application session.

### Const Correctness
*   **What it is:** Using the `const` keyword to declare variables or functions as read-only, preventing unintended modifications.
*   **Where it is used:** Getters like `Vehicle::getID() const` and inspect logs like `InspectionReport::displayReport() const`.
*   **Why it is used:** Enhances code security and debugging. It ensures getters only read variables and allows objects to be passed around as constant references safely.

---

## 4. Standard Template Library (STL)

### STL Containers (vector & string)
*   **What it is:** Safe, pre-designed templates for storing data (`std::vector` for dynamic arrays, `std::string` for character arrays).
*   **Where it is used:**
    *   `std::vector` is used globally to maintain user registries and active fleet structures.
    *   `std::string` is utilized for CNICs, dates, passwords, models, and notes.
*   **Why it is used:** Replaces standard C-arrays, eliminating memory management vulnerabilities (like buffer overflows) and introducing automatic resizing.

### STL Algorithms
*   **What it is:** Standard library functions designed to perform operations on container segments.
*   **Where it is used:**
    *   `std::all_of` is used inside `Validator::isAlphanumeric()` to scan string properties.
    *   `std::sort` is used inside [Source/TripPlanner.cpp](../Source/TripPlanner.cpp#L45) to sort matching vehicles based on real daily prices.
*   **Why it is used:** Prevents writing custom sorting or searching loops, utilizing compiler-optimized algorithms to keep code clean and readable.

### File Input/Output (fstream)
*   **What it is:** Classes (`ifstream` for reading, `ofstream` for writing) that manage data streams to and from persistent storage disks.
*   **Where it is used:** Heavily utilized within [Source/FileHandler.cpp](../Source/FileHandler.cpp) to read and save data from text database files inside the `Data/` folder.
*   **Why it is used:** Allows project data to remain persistent across application sessions without requiring complex external SQL database engines.

### Formatting Manipulators (setw & setfill)
*   **What it is:** Stream formatting tools in `<iomanip>` that configure text padding and alignment.
*   **Where it is used:** Used inside `Vehicle::displayRow()` to construct tabular terminal displays.
*   **Why it is used:** Formats text into neat, readable terminal columns, which is essential for a professional CLI look.

---

## 5. Modern C++ Features (C++11 and Later)

### Enum Classes (Scoped Enums)
*   **What it is:** Scoped and type-safe enums that prevent implicit conversions to other types.
*   **Where it is used:** Declared in [Include/Vehicle.h](../Include/Vehicle.h#L14):
    ```cpp
    enum class VehicleStatus { Available, Rented, Sold };
    ```
*   **Why it is used:** Prevents namespace pollution and coding mistakes (such as comparing a vehicle status enum directly to an unrelated integer value).

### Lambda Expressions
*   **What it is:** Inline anonymous functions defined at the point of call.
*   **Where it is used:** Inside [Source/TripPlanner.cpp](../Source/TripPlanner.cpp#L47) to sort matching vehicles by cost:
    ```cpp
    [](Vehicle* a, Vehicle* b) { return a->calculateCost(1) < b->calculateCost(1); }
    ```
*   **Why it is used:** Simplifies code by eliminating the need to write separate helper functions for simple, local comparison algorithms.

### Range-based for loops
*   **What it is:** A cleaner loop syntax that automatically iterates through all items in a container.
*   **Where it is used:** Used extensively across the project:
    ```cpp
    for (Vehicle* v : fleet) { v->displayRow(); }
    ```
*   **Why it is used:** Eliminates manual iterator boilerplate and protects the code from index boundary ("off-by-one") errors.

### Regular Expressions (std::regex)
*   **What it is:** Standard classes used to run pattern-matching searches against strings.
*   **Where it is used:** Declared inside [Source/Validator.cpp](../Source/Validator.cpp#L54-L59) to validate Pakistani CNIC patterns:
    ```cpp
    const regex pattern(R"(^\d{5}-\d{7}-\d{1}$)");
    ```
*   **Why it is used:** Permits validation of date structures (`DD-MM-YYYY`) and CNIC registration blocks with minimal code.

### Type Casting (static_cast)
*   **What it is:** C++ style casts that convert pointers or enums under compiler checks.
*   **Where it is used:** Used to cast enums or base user pointers to specific roles in [Source/MenuHandler.cpp](../Source/MenuHandler.cpp#L175):
    ```cpp
    Customer* customer = static_cast<Customer*>(currentUser);
    ```
*   **Why it is used:** Safer and more explicit than legacy C-style casts, allowing the compiler to verify basic type compatibility during compilation.

---

## 6. Project Architecture & Engineering

### Header Guards
*   **What it is:** Preprocessor macros (#ifndef, #define, #endif) ensuring header files are compiled only once.
*   **Where it is used:** Placed at the top of every `.h` file in the `Include/` folder.
*   **Why it is used:** Prevents double definition conflicts when files transitively import multiple dependent headers.

### Forward Declarations
*   **What it is:** Declaring a class name before fully importing its header, notifying the compiler of the class's existence.
*   **Where it is used:** Used in [Include/MenuHandler.h](../Include/MenuHandler.h#L7-L12):
    ```cpp
    class Vehicle;
    class User;
    ```
*   **Why it is used:** Breaks circular import loops (e.g. A depends on B, B depends on A) and improves compilation speed by limiting header dependencies.

### Persistence Logic
*   **What it is:** A lightweight database layer parsing structured text rows into run-time memory objects.
*   **Where it is used:** Handled by `FileHandler` loading pipe-separated fields (`3|3001|Suzuki Alto|4|3000|0`) into polymorphic vectors.
*   **Why it is used:** Recreates the state of the system on boot and writes updates to disk on changes, making the application fully persistent.

### Exception Handling (try-catch)
*   **What it is:** Code blocks that catch run-time parse faults, preventing system crashes.
*   **Where it is used:** Implemented in [Source/FileHandler.cpp](../Source/FileHandler.cpp#L78-L102) when parsing numeric values from external text files.
*   **Why it is used:** Ensures robustness. If a database file is edited manually and introduces corrupt formatting, the system reports a skipped item instead of crashing.
