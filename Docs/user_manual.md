# Vehicle Management System (VMS) - User Manual

Welcome to the **Vehicle Management System (VMS)**. This manual provides comprehensive instructions on how to set up, launch, navigate, and utilize the console-based VMS application. 

---

## 1. Title & Introduction

The **Vehicle Management System (VMS)** is a high-performance, console-based C++ application designed to orchestrate vehicle rental and sales operations. By utilizing Object-Oriented Programming (OOP) principles, the system implements a dual-role access control structure that allows both customers and administrators to interact securely with a shared virtual vehicle fleet.

### Core System Features
*   **Dual-Role Authentication:** Dedicated dashboards and session handlers for Admins (IDs starting from `1001`) and Customers (IDs starting from `2001`).
*   **Fleet Inventory Management:** Real-time tracking of vehicle statuses (Available, Rented, Sold) and technical specifications (Capacity, Daily Rate) using purely numeric IDs (e.g., `3001` for Economy, `4001` for Luxury, `5001` for SUV, and `6001` for Van/Bus).
*   **Automated Rental Module:** Calculation of rental rates, planned duration tracking, and pre-rental price estimation.
*   **Dynamic Rental Discounts:** Integrated discount tiers for long-term rentals:
    *   **10% Discount** for rentals lasting 4 to 7 days.
    *   **20% Discount** for rentals lasting 8 days or more.
*   **Post-Rental Inspection & Billing:** Automated damage fee assessment during returns based on condition reports:
    *   **Good:** Rs. 0 damage fee.
    *   **Fair:** Damage fee equal to **50%** of the vehicle's daily rate.
    *   **Poor:** Damage fee equal to **200%** of the vehicle's daily rate.
*   **Trip Planner Engine:** Suggests vehicles matching target budget, passenger requirements, and distance.
*   **Fleet Sales Module:** Safe execution of customer purchases and supplier restock transactions.
*   **Persistent File Storage:** Seamless preservation of fleet records, transaction histories, user credentials, and inspection reports.

---

## 2. Getting Started

The VMS application is compiled as a standalone command-line executable. Follow these instructions to launch it on your local system:

### Prerequisites
*   A C++ compiler supporting the **C++17** standard (such as GCC/g++).
*   Windows Command Prompt (cmd) or PowerShell.

### Compilation & Launch
1.  Open your terminal/command prompt and navigate to the project directory: `D:/UET/HMS Code/Vehicle Manag Sys`
2.  Compile the source code using the provided Windows build script [build.bat](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/build.bat) or run the command manually:
    ```bash
    g++ -IInclude Source/*.cpp -o VehicleManagSys.exe
    ```
3.  Launch the compiled executable:
    ```bash
    VehicleManagSys.exe
    ```
    Alternatively, you can just run [build.bat](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/build.bat) directly to automatically compile and launch the program.

> [!TIP]
> **Live Web Demo:** You can test the application instantly without installing local compilers by opening the [Live Replit Demo](https://replit.com/@hmsaeed/Vehicle-Management-System) and clicking **Run**.

---

## 3. Menu Navigation

The interface uses interactive numbered and lettered options. To invoke an option, type the option key (e.g. **1**, **2**, **Z**) and press **Enter**.

### System Main Menu
Upon launching the application through [main.cpp](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Source/main.cpp), you will be greeted by the Main Menu:
*   **[1] Register New Account:** Registers a new Customer profile.
*   **[2] Login to System:** Logs in using existing Customer or Admin credentials.
*   **[Z] Exit System:** Closes the program.

### Customer Dashboard
Once authenticated as a customer, the console switches to the [Customer Dashboard](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Source/Customer.cpp#L19):
*   **[1] Search for a Vehicle:** Browse fleet or filter by category.
*   **[2] Rent a Vehicle:** Rent an available vehicle by entering its numeric ID.
*   **[3] Return a Vehicle:** Return a currently rented vehicle and complete the inspection form.
*   **[4] Plan a Trip:** Input travel specifications to obtain recommendations.
*   **[5] View My Rental History:** View your persistent activity records.
*   **[Z] Logout:** Exit session and return to the Main Menu.

### Admin Control Panel
Authenticated administrators are redirected to the [Admin Control Panel](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Source/Admin.cpp#L102):
*   **[1] Add New Vehicle:** Interactively add a new vehicle (with automatically assigned numeric ID).
*   **[2] Remove a Vehicle:** Remove a vehicle permanently from the active fleet.
*   **[3] Delete Customer Account:** Delete a customer profile (only permitted if the customer has no active rentals).
*   **[4] Sale / Purchase Module:** Access the Sales menu to execute vehicle sales or purchase supplier stock.
*   **[5] View Full Fleet & User Records:** Read complete database statistics.
*   **[6] View Transaction History:** Review all transactions logged in the system.
*   **[Z] Logout:** Close the Admin session.

---

## 4. Step-by-Step Guides

Here are instructions for primary tasks inside the Vehicle Management System.

### A. Customer: Creating an Account
1.  From the **Main Menu**, select **Option 1** (type **1** and press **Enter**).
2.  At the prompt `Full Name (Min 3 characters)`, enter your legal name (e.g., **Ahmad Khan**). Letters and spaces only.
3.  Enter a unique **Login Username** (e.g., **ahmad_k**).
4.  Enter your CNIC number in the format **XXXXX-XXXXXXX-X** (e.g., **35201-1234567-1**).
5.  Type a secure password and press **Enter**.
6.  The system will output a message confirming registration and showing your assigned numeric **Account ID** (e.g., `2006`). Press **Enter** to return to the Main Menu.

### B. Customer: Searching & Filtering Vehicles
1.  From the **Customer Dashboard**, select **Option 1**.
2.  Choose your search mode:
    *   Select **Option 1** to browse the entire fleet.
    *   Select **Option 2** to filter by category (**1. Economy**, **2. Luxury**, **3. SUV**, or **4. Van / Bus**).
3.  The system outputs a detailed table showing Vehicle ID, Model, Passenger Capacity, Rental Rate, Status, and Category.
4.  To rent one of the listed vehicles directly, enter its numeric **Vehicle ID** (e.g., `3001` or `4002`) when prompted; otherwise, press **Enter** to return to the dashboard.

### C. Customer: Renting a Vehicle
1.  From the **Customer Dashboard**, select **Option 2**.
2.  A list of available fleet vehicles is shown.
3.  Type the numeric **Vehicle ID** of your choice (e.g., `3002`) and press **Enter**.
4.  Type the **Rental Start Date** in `DD-MM-YYYY` format (e.g., `25-06-2026`).
5.  Type the number of days you plan to rent the vehicle (between **1** and **365**) and press **Enter**.
6.  Review the **Estimated Rental Quote** showing the base cost, applied dynamic discounts, and calculated total.
7.  Type **Y** and press **Enter** to finalize the transaction. Entering **N** will cancel the process.

### D. Customer: Returning a Vehicle & Finalizing Bill
1.  From the **Customer Dashboard**, select **Option 3**.
2.  Type the numeric **Vehicle ID** of the rented car (e.g., `3002`) and press **Enter**.
3.  Enter the **Return Date** in `DD-MM-YYYY` format (e.g., `30-06-2026`).
4.  Specify the current **Fuel Level** (e.g., `Full` or `Half`), current **Odometer/Mileage** (e.g., `150500`), and write any damage notes (type `None` if clear).
5.  State the condition of the returned vehicle by typing exactly **Good**, **Fair**, or **Poor** (case-sensitive).
6.  Write any additional evaluator remarks and press **Enter**.
7.  The system automatically calculates the rental duration and displays pending charges including base rates and damage fees.
8.  Type **Y** and press **Enter** to process payment and finalize the return. The vehicle status changes back to `Available`.

### E. Customer: Planning a Trip
1.  From the **Customer Dashboard**, select **Option 4**.
2.  Input your **Starting Point** (e.g., `Lahore`) and **Destination** (e.g., `Islamabad`). Letters and spaces only.
3.  Provide the trip **Distance in km** (range: **1.0** to **20000.0**), your **Maximum Budget** in Rs. (range: **100.0** to **1000000.0**), and the **Passenger Count** (range: **1** to **20**).
4.  The system filters the active fleet and displays matching options sorted by daily rate.
5.  To rent a recommended vehicle immediately, enter its ID; otherwise, press **Enter** to return to your dashboard.

### F. Admin: Selling a Fleet Vehicle
1.  From the **Admin Control Panel**, select **Option 4** (Sale / Purchase Module) and then choose **Option 1** (Sell Vehicle).
2.  Input the numeric **Vehicle ID** (must be currently marked as `Available`).
3.  Input the buying **Customer ID** (e.g., `2001`).
4.  Provide the final sale price and the transaction date (`DD-MM-YYYY`).
5.  Review the transaction details and confirm by entering **Y**. The vehicle status will update to `Sold`.

### G. Admin: Purchasing/Restocking a Vehicle
1.  From the **Admin Control Panel**, select **Option 4** (Sale / Purchase Module) and then choose **Option 2** (Purchase Vehicle).
2.  Enter the **Supplier Name** (e.g., `Toyo Cars`).
3.  Enter the category character: **E** for Economy, **L** for Luxury, **S** for SUV, or **V** for Van/Bus.
4.  Enter the numeric **New Vehicle ID** manually when prompted (e.g., `3025`).
5.  Provide the **Model Name**, passenger **Capacity** (range: **1** to **100**), **Purchase Price** in Rs., **Initial Rental Rate/Day** in Rs., and the **Purchase Date** (`DD-MM-YYYY`).
6.  Confirm the details by entering **Y** to register the vehicle as `Available` in the fleet.

---

## 5. Input Guidelines

To prevent parsing errors or console stream glitches, inputs must adhere strictly to the following validation rules enforced by the [InputHandler](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Source/InputHandler.cpp) namespace and [Validator](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Source/Validator.cpp) class:

| Input Field | Expected Format / Constraint | Example (Valid) | Example (Invalid) |
| :--- | :--- | :--- | :--- |
| **CNIC** | Must be 15 characters exactly: 5 digits, hyphen, 7 digits, hyphen, 1 digit. | `35201-1234567-1` | `3520112345671` (no hyphens) |
| **Dates** | Must be in `DD-MM-YYYY` format. Year must be between `2000` and `2100` inclusive. | `28-06-2026` | `28-06-1999` (out of year range) |
| **Names / Cities** | Alphabetic letters and spaces only. Cannot be left blank. | `Muhammad Saeed` | `Ali123` (contains digits) |
| **Decimals (Floats)** | Numbers with optional decimal points. Cannot contain text. | `150.75` | `150,75` or `150km` |
| **Vehicle ID** | Must be strictly numeric digits. | `3001` | `E101` (contains character prefix) |
| **User ID** | Must be strictly numeric digits. | `2001` | `U002` (contains character prefix) |
| **Vehicle Condition** | Case-sensitive condition status. Must be exactly `Good`, `Fair`, or `Poor`. | `Good` | `good` (incorrect capitalization) |
| **Selections** | Numbers or characters listed inside options. Case-insensitive. | `1` or `y` or `Z` | `9` (out of menu range) |

> [!IMPORTANT]
> **Canceling Prompts:** You can type **Z** or **z** at almost any console input prompt to abort the operation and return to the previous screen.

---

## 6. Troubleshooting & FAQs

### Q: Why does the compiler say `g++: error: Source/*.cpp: No such file or directory`?
*   **Reason:** Your terminal is not opened in the root directory containing the `Source` folder.
*   **Solution:** Check your terminal path. Ensure it is inside the project root (`D:\UET\HMS Code\Vehicle Manag Sys`) before running `build.bat` or compilation commands.

### Q: I typed numeric options but the screen outputted `[ERROR] Invalid numeric input.`
*   **Reason:** The system uses robust stream parsing. Entering spaces, punctuation, or alphabetic characters in a strictly numeric prompt will trigger this warning.
*   **Solution:** Input only integer digits (e.g. **2**, **5**) without letters or commas.

### Q: Why can't I delete a customer account?
*   **Reason:** The customer currently has an active rental transaction logged in [Inspections.txt](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/Inspections.txt) or [Transactions.txt](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/Transactions.txt).
*   **Solution:** The customer must return all vehicles and complete post-rental inspections before their account can be removed. Admins are also blocked from deleting other Admins.

### Q: Where are the database text files saved?
*   All information is stored in the [Data/](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/) directory under:
    *   [Data/Vehicle.txt](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/Vehicle.txt) (Fleet lists and prices)
    *   [Data/Users.txt](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/Users.txt) (Admin and Customer login details)
    *   [Data/Transactions.txt](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/Transactions.txt) (Rental/sales records)
    *   [Data/Inspections.txt](file:///D:/UET/HMS%20Code/Vehicle%20Manag%20Sys/Data/Inspections.txt) (Inspection logs)
*   Do not edit these files manually unless you are familiar with pipe-delimited (`|`) records, as formatting errors will corrupt database loading.
