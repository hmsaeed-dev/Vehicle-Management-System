# 🚗 Vehicle Management System (VMS)

A high-performance, console-based vehicle rental and sales orchestration platform built using core **Object-Oriented Programming (OOP)** principles in C++17.

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=for-the-badge&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![Platform Compatibility](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-brightgreen.svg?style=for-the-badge)](https://github.com/hmsaeed-dev)
[![Documentation](https://img.shields.io/badge/Documentation-GitHub%20Wiki-orange.svg?style=for-the-badge)](https://github.com/hmsaeed-dev/Vehicle-Management-System/wiki)
[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/hmsaeed-dev/Vehicle-Management-System)

---

## ⚡ Live Interactive Demo

Test the live console interface directly inside your web browser without installing local compilers or dependencies:

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/hmsaeed-dev/Vehicle-Management-System)

Once the Codespace loads, the system is automatically pre-built and ready. Simply execute:

```bash
./build.sh
# or using Make:
make run
```

---

## 📖 Deep-Dive Documentation Hub
Comprehensive step-by-step guides, usage parameters, and edge-case behaviors are hosted in the project repository wiki.

* 🏠 **[Project Overview & Architecture Core](https://github.com/hmsaeed-dev/Vehicle-Management-System/wiki/Home)**
* 🚀 **[Installation & Local Compilation Matrix](https://github.com/hmsaeed-dev/Vehicle-Management-System/wiki/Getting-Started)**
* 👥 **[Customer Dashboard & Trip Planner Guide](https://github.com/hmsaeed-dev/Vehicle-Management-System/wiki/Customer-User-Guide)**
* ⚙️ **[Admin Panel & Fleet Inventory Control](https://github.com/hmsaeed-dev/Vehicle-Management-System/wiki/Admin-Guide)**
* 🛡️ **[Input Stream Validation & Structural FAQs](https://github.com/hmsaeed-dev/Vehicle-Management-System/wiki/Input-Validation-Rules)**

---

## 🔥 Key Architectural Features

* **Dual-Role Authentication:** Isolated session management wrappers for Administrators (IDs `1001+`) and Customers (IDs `2001+`).
* **Automated Financial Engine:** Native pricing logic incorporating tiered long-term rental discounts (**10%** for 4–7 days, **20%** for 8+ days) and post-rental inspection damage modifiers (**50%** or **200%** daily rate adjustments based on structural tier checks).
* **Trip Planner Engine:** Advanced multi-criteria search algorithms filtering the dynamic fleet array relative to client budget caps, target mileage distances, and minimum passenger tolerances.
* **Persistent Flat-File Database:** Scalable abstract I/O file tracking modules mapping live structures back into pipe-delimited (`|`) local system text sheets dynamically upon stream termination.

---

## 📐 System Architecture

```mermaid
graph TD
    %% Define Styles
    classDef main fill:#1f6feb,stroke:#58a6ff,stroke-width:2px,color:#fff;
    classDef sub fill:#21262d,stroke:#30363d,stroke-width:1px,color:#c9d1d9;
    classDef feat fill:#161b22,stroke:#30363d,stroke-width:1px,color:#8b949e;

    Menu[MenuHandler <br><i>UI Orchestration & Session Workflow</i>]:::main

    AdminS[Admin Session]:::sub
    CustS[Customer Session]:::sub
    Eng[SearchEngine & <br>TripPlanner]:::sub

    AdminF[Admin Features<br>• Dashboard<br>• Fleet CRUD<br>• User Management]:::feat
    Trans[Transactions Layer<br>• Rentals<br>• Sales<br>• Post-Return Inspections]:::feat

    %% Connections
    Menu --> AdminS
    Menu --> CustS
    Menu --> Eng

    AdminS --> AdminF
    CustS --> Trans
    Eng --> Trans
```

---

## 📊 Fleet Segmentation Matrix

| Category | Tracking Range | Base Rate Scale (PKR) | Representative Core Implementations |
| :--- | :--- | :--- | :--- |
| 🚗 **Economy** | IDs `3000 - 3999` | Rs. 3,000 - 6,500 | Suzuki Alto, Cultus, Toyota Corolla GLI, Honda City |
| 💎 **Luxury** | IDs `4000 - 4999` | Rs. 45,000 - 80,000 | Audi A6 Prestige, BMW 7 Series, Land Cruiser V8 |
| ⛰️ **SUV** | IDs `5000 - 5999` | Rs. 12,000 - 25,000 | Kia Sportage, Hyundai Tucson, Toyota Fortuner |
| 🚌 **Van** | IDs `6000 - 6999` | Rs. 3,500 - 35,000 | Suzuki Bolan, Toyota Hiace, Luxury Coaster |

---

## 🛠️ Compilation & Quick Start

### 🐧 Linux / GitHub Codespaces
Compile and run in one command:
```bash
./build.sh
```
Or use the included Makefile:
```bash
make
make run
```
Or press `Ctrl+Shift+B` in VS Code / Codespaces to trigger the build task.

### 🪟 Windows
Execute the included Windows batch script from CMD or PowerShell:
```cmd
build.bat
```
Or compile manually:
```cmd
g++ -std=c++17 -IInclude Source/*.cpp -o VehicleManagSys.exe
VehicleManagSys.exe
```

---

## 📁 Repository File Tree

```text
Vehicle Manag Sys/
├── .devcontainer/        # GitHub Codespaces & VS Code DevContainer configurations
│   └── devcontainer.json # Pre-configured Ubuntu 22.04 container with C++17 tools
├── .vscode/              # Editor tasks and debugging profiles
│   ├── launch.json       # Interactive console debugging (GDB) configuration
│   └── tasks.json        # Build and Run tasks mapped to Ctrl+Shift+B
├── Include/              # Abstract blueprints and header compilation modules (.h)
│   ├── Admin.h           # Admin privilege configurations & control dashboard
│   ├── Colors.h          # ANSI color definitions for rich console UI
│   ├── Constants.h       # Business logic pricing, discount tiers, & file paths
│   ├── Customer.h        # Customer operations interface & historical profiling
│   ├── Economy.h         # Specialized vehicle subtype implementations
│   ├── FileHandler.h     # Core I/O serialization & flat-file mapping logic
│   ├── InputHandler.h    # Secure type validation & stream clear functions
│   ├── InspectionReport.h# Return damage inspection structure & reporting
│   ├── Luxury.h          # Specialized vehicle subtype implementations
│   ├── MenuHandler.h     # UI navigation menus and dispatch logic
│   ├── RentalTransaction.h # Rental billing & date calculations
│   ├── SaleTransaction.h # Direct vehicle purchase contracts
│   ├── SearchEngine.h    # Multivariant evaluation matching arrays
│   ├── SUV.h             # Specialized vehicle subtype implementations
│   ├── Transaction.h     # Polymorphic base class for transactions
│   ├── TripPlanner.h     # Multi-criteria route & budget fleet recommendations
│   ├── User.h            # Polymorphic base user authentication model
│   ├── Validator.h       # String, number, and date format sanitization
│   ├── Van.h             # Specialized vehicle subtype implementations
│   └── Vehicle.h         # Polymorphic base class for vehicle fleet data structures
│
├── Source/               # Implementation modules containing raw application logic (.cpp)
│   ├── Admin.cpp         # Code block parsing for system dashboard access controls
│   ├── Customer.cpp      # Interface handling for rentals and trip planner pipelines
│   ├── Economy.cpp       # Economy vehicle class methods
│   ├── FileHandler.cpp   # File storage parsing and serialization
│   ├── InputHandler.cpp  # Safe user input retrieval
│   ├── InspectionReport.cpp # Vehicle damage audit reports
│   ├── Luxury.cpp        # Luxury vehicle methods
│   ├── main.cpp          # Runtime system orchestration and file validation entry
│   ├── MenuHandler.cpp   # Menu dispatching and interactive loops
│   ├── RentalTransaction.cpp # Rental processing
│   ├── SaleTransaction.cpp   # Sales processing
│   ├── SearchEngine.cpp  # Search algorithms
│   ├── SUV.cpp           # SUV vehicle methods
│   ├── Transaction.cpp   # Base transaction methods
│   ├── TripPlanner.cpp   # Trip planning logic
│   ├── User.cpp          # Base user methods
│   ├── Validator.cpp     # Regex and boundary checks
│   ├── Van.cpp           # Van vehicle methods
│   └── Vehicle.cpp       # Vehicle core methods
│
├── Docs/                 # Structural asset modeling sheets & Mermaid graphs
│   ├── Flowchart.mmd     # Process pipeline mapping for application logic tracking
│   └── UML-2.mmd         # Object inheritance relationship architectures
│
├── Data/                 # Protected application persistence layer text files (.txt)
│   ├── Vehicle.txt       # Dynamic live fleet inventory array configurations
│   ├── Users.txt         # Pipe-separated credential strings for safe login parsing
│   ├── Transactions.txt  # Cumulative chronological purchase and rental histories
│   └── Inspections.txt   # Mechanical evaluation checklists generated upon returns
│
├── CMakeLists.txt        # Cross-platform CMake build configuration
├── Makefile              # Native Linux/Codespaces fast build rules
├── build.sh              # Unix/Linux one-click build and execution script
├── build.bat             # Automation script for rapid compilation and environment boot
└── README.md             # This core documentation tracking module
```

---

## 👨‍💻 Engineering Lead

* **Hafiz Muhammad Saeed** – Web Developer & Computer Science Student
* Team Members: Wajeeh-ul-Hassan, Muhammad Irfan Yasir, Hamza Khurram
