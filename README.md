# Vehicle Management System

![C++](https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square) ![Platform](https://img.shields.io/badge/Platform-Windows-brightgreen?style=flat-square)

A comprehensive console-based vehicle rental and sales management platform built in C++17. Manage fleet inventory, handle customer rentals, conduct vehicle inspections, and process sales transactions with role-based access control.

**Table of Contents**
- [Overview](#overview)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [Getting Started](#getting-started)
- [Usage Guide](#usage-guide)
- [Vehicle Categories](#vehicle-categories)
- [System Requirements](#system-requirements)
- [Project Structure](#project-structure)
- [Author](#author)

---

## Overview

The Vehicle Management System is a full-featured platform designed for managing vehicle fleets across rental and sales operations. It supports multiple user roles (Admins and Customers), maintains persistent data storage, provides advanced vehicle search capabilities, and includes comprehensive transaction tracking with inspection reports. The system handles complex workflows including rentals with dynamic pricing, vehicle sales, trip planning assistance, and post-rental inspections.

---
### ⚡ Live Interactive Demo

You don't need to download this repository or configure a local C++ compiler to test it. You can interact with the live console interface directly in your web browser:

👉 **[Run the Vehicle Management System Live on Replit](https://replit.com/@hmsaeed/Vehicle-Management-System)**

*(Once the Replit window loads, simply hit the big green **Run** button at the very top of the interface to initialize the console database menu!)*

---

## Key Features

- **🚗 Vehicle Inventory Management** – Add, remove, and track vehicles
- **💳 Rental System** – With dynamic pricing, duration tracking, and automatic cost calculation
- **🛒 Sales Module** – Process vehicle purchases with transaction recording and fleet status updates
- **🔍 Advanced Search** – Multi-criteria filtering by category, price range, availability, and passenger capacity
- **📋 Vehicle Inspections** – Post-rental assessments _ fuel level, mileage, damage evaluation, and condition grading
- **📍 Trip Planner** – Recommendations based on trip distance, budget constraints, and passenger requirements
- **💰 Dynamic Pricing & Discounts** – Category-based rate multipliers with tiered discounts
- **👥 Dual-Role Authentication** – Separate admin and customer login systems with secure credentials
- **💾 Data Persistence** – All system data automatically saved to files

---


## System Architecture

```
                        ┌──────────────────────────────────────────────────────────┐
                        │           MenuHandler (UI Orchestration)                 │
                        │      Manages menus, login, user sessions, workflows      │
                        └──────────────────────┬───────────────────────────────────┘
                                               │
                                  ┌────────────┼────────────────────┐
                                  │            │                    │
                             ┌────▼──────┐   ┌─▼──────────┐   ┌─────▼──────────┐
                             │   Admin   │   │  Customer  │   │  SearchEngine  │
                             │  Session  │   │  Session   │   │  TripPlanner   │
                             └───────────┘   └────────────┘   └────────────────┘
                                  │             │                   │
                                  │             └────────┬──────────┘
                                  │                      │
                                  │                      │
                              ┌───▼──────────────┐    ┌──▼──────────────┐
                              │  Admin Features  │    │  Transactions   │
                              │ - Dashboard      │    │ - Rentals       │
                              │ - Fleet CRUD     │    │ - Sales         │
                              │ - User Manag     │    │ - Inspections   │
                              └──────────────────┘    └─────────────────┘
```

**Core Components:**
- **FileHandler** – Persistent data layer; reads/writes all system data to text files
- **Vehicle Hierarchy** – Abstract Vehicle class with specialized types
- **User Hierarchy** – Abstract User class with Admin and Customer implementations
- **Transaction Modules** – RentalTransaction and SaleTransaction for tracking vehicles
- **SearchEngine** – Multi-criteria filtering and advanced query execution
- **InspectionReport** – Post-rental condition assessment and damage documentation

---

## Getting Started

### Prerequisites
- **Compiler:** GCC with C++17 support
- **OS:** Windows (uses ANSI terminal processing via Windows API)
- **Build Tools:** Either g++ command-line or batch script

### Installation & Build

**Using build.bat (Recommended for Windows)**
```batch
cd Vehicle Manag Sys
build.bat
```

### Running the System
```bash
VehicleManagementSystem.exe
```

---

## Usage Guide

### **Admin Workflow**
1. **Login** – Enter admin credentials at startup
2. **Access Dashboard** – View fleet statistics and system status
3. **Manage Fleet** – Add new vehicles, remove vehicles from inventory
4. **Manage Users** – Remove user accounts and manage customer records
5. **Process Sales** – Execute vehicle purchase transactions
6. **View Records** – Review all transactions, inspections, and system reports

### **Customer Workflow**
1. **Register/Login** – Create new account or log in with existing credentials
2. **Search Vehicles** – Filter by category, price range, year, availability, or passenger capacity
3. **Plan Trip** – Use Trip Planner for vehicle recommendations based on distance and budget
4. **Rent Vehicle** – Select vehicle and complete rental transaction
5. **Return & Inspect** – Return vehicle and complete post-rental inspection report
6. **View History** – Review rental history and inspection records
7. **Purchase Option** – Buy vehicle outright (Sales transaction)

---

## Vehicle Categories

| Category | Model Type | Base Rate (PKR) | Best For |
|----------|-----------|-----------------|----------|
| **Economy** | Budget sedans, basic comfort | 200/day | Budget-conscious renters |
| **Luxury** | Premium vehicles, special features | 500/day | High-end clients, special occasions |
| **SUV** | Sports utility, off-road capable | 350/day | Outdoor trips, family groups |
| **Van** | Passenger vans, minibuses | 250/day | Group travel, large parties |

---

## System Requirements

| Requirement | Specification |
|-------------|---------------|
| **Language** | C++17 Standard |
| **Compiler** | GCC (g++) with C++17 support |
| **OS** | Windows (primary) |
| **Memory** | ~50 MB (minimal requirements) |
| **Disk Space** | ~5 MB (including data files) |
| **Dependencies** | Standard C++ Library (STL) only |

---

## Project Structure

```
Vehicle Manag Sys/
├── Include/                        # Header files (class definitions)
│   ├── Admin.h                     # Admin user role and features
│   ├── Customer.h                  # Customer user role and features
│   ├── Vehicle.h                   # Abstract vehicle base class
│   ├── Economy.h, Luxury.h         # Vehicle category implementations
│   ├── SUV.h, Van.h                #
│   ├── RentalTransaction.h         # Rental workflow handling
│   ├── SaleTransaction.h           # Sales workflow handling
│   ├── InspectionReport.h          # Post-rental inspection logic
│   ├── SearchEngine.h              # Multi-criteria vehicle search
│   ├── TripPlanner.h               # Trip recommendation engine
│   ├── FileHandler.h               # Data persistence layer
│   ├── MenuHandler.h               # UI orchestration
│   └── [Other utility headers]
│
├── Source/                         # Implementation files (.cpp)
│   ├── main.cpp                    # Application entry point
│   ├── Admin.cpp                   # Admin implementation
│   ├── Customer.cpp                # Customer implementation
│   └── [Other .cpp files]
│
├── Data/                           # Persistent storage (text files)
│   ├── Vehicle.txt                 # Fleet inventory database
│   ├── Users.txt                   # User accounts database
│   ├── Transactions.txt            # Transaction history
│   └── Inspections.txt             # Inspection reports
│
├── build.bat                       # Windows build script
└── README.md                       # This file
```

---

## Author

Developed by **[Hafiz Muhammad Saeed](https://github.com/HMSaeed101)**
