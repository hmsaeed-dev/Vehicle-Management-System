#include "Admin.h"
#include "Vehicle.h"
#include "Economy.h"
#include "Luxury.h"
#include "SUV.h"
#include "Van.h"
#include "FileHandler.h"
#include "Colors.h"
#include "InputHandler.h"
#include "Validator.h"
#include "Constants.h"
#include "InspectionReport.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// Admin Class Constructor
Admin::Admin(string id, string username, string name, string cnic, string password)
    : User(id, username, name, cnic, password) {}

void Admin::showDashboard(const vector<Vehicle*>& fleet)
{
    int available = 0, rented = 0, sold = 0;
    for (Vehicle* v : fleet)
    {
        if (v->getStatus() == VehicleStatus::Available) available++;
        else if (v->getStatus() == VehicleStatus::Rented) rented++;
        else if (v->getStatus() == VehicleStatus::Sold) sold++;
    }

    cout << "\n" << Color::HEADER << " [ DASHBOARD SUMMARY ] " << Color::RESET << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| " << Color::STATUS_AVAILABLE << "Available: " << left << setw(5) << available << Color::RESET;
    cout << "| " << Color::STATUS_RENTED << "Rented: " << left << setw(5) << rented << Color::RESET;
    cout << "| " << Color::STATUS_SOLD << "Sold: " << left << setw(5) << sold << Color::RESET;
    cout << "| " << Color::TABLE_HEADER << "Total: " << left << setw(5) << fleet.size() << Color::RESET << " |\n";
    cout << "+----------------------------------------------------------+\n";
}


/**
* @brief Displays the Admin-specific console menu.
*/
void Admin::showMenu()
{
    cout << Color::HEADER;
    cout << "+==========================================================+\n";
    cout << "|                  ADMIN CONTROL PANEL                     |\n";
    cout << "+==========================================================+\n" << Color::RESET;
    cout << "|                                                          |\n";
    cout << "|   [1]  Add New Vehicle                                   |\n";
    cout << "|   [2]  Remove a Vehicle                                  |\n";
    cout << "|   [3]  Delete Customer Account                           |\n";
    cout << "|   [4]  Sale / Purchase Module                            |\n";
    cout << "|   [5]  View All Records                                  |\n";
    cout << "|   [6]  Process Vehicle Return                            |\n";
    cout << "|   [Z]  Logout                                            |\n";
    cout << "|                                                          |\n";
    cout << Color::RED << "+----------------------------------------------------------+\n\n" << Color::RESET;
}


void Admin::removeUser(vector<User*>& users, FileHandler& fh)
{
    string id;
    cout << "\n" << Color::SUBHEADER << "========= DELETE CUSTOMER ACCOUNT =========" << Color::RESET << endl;
    id = InputHandler::getString("Enter User ID to remove (or 'Z' to go back)", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    if (id == this->getID()) {
        cout << Color::ERR << "[ERROR] You cannot delete your own admin account." << Color::RESET << endl;
        return;
    }

    if (hasActiveRentals(id, fh)) {
        cout << Color::ERR << "[ERROR] Cannot delete user. This customer has ACTIVE RENTALS." << Color::RESET << endl;
        cout << "        Please ensure all vehicles are returned before removing account." << Color::RESET << endl;
        return;
    }
for (auto it = users.begin(); it != users.end(); ++it) {
    if ((*it)->getID() == id) {
        if ((*it)->getRole() == "ADMIN") {
            cout << Color::ERR << "[ERROR] Security Breach: Admins cannot delete other Admins." << Color::RESET << endl;
            return;
        }


            cout << Color::WARNING << "[CONFIRM] Are you sure you want to PERMANENTLY delete account: " << (*it)->getName() << " (ID: " << id << ")? (Y/N/Z:Back): " << Color::RESET;
            char confirm = InputHandler::getChar("", "YN", true);
            if (confirm == 'N' || confirm == 'Z') {
                cout << Color::INFO << "[SYSTEM] Deletion cancelled." << Color::RESET << endl;
                return;
            }

            cout << "[SYSTEM] Purging user data...\n";
            delete *it;
            users.erase(it);
            fh.saveUsers(users);
            cout << Color::SUCCESS << "[SUCCESS] User account has been removed from the system." << Color::RESET << endl;
            return;
        }
    }
    cout << Color::ERR << "[ERROR] User ID not found." << Color::RESET << endl;
}


/**
 * @brief Interactively ADD NEW VEHICLE to the fleet.
 */
void Admin::addVehicle(vector<Vehicle*>& fleet)
{
    string id, model;
    char type;
    float rate;
    int capacity;

    cout << "\n" << Color::SUBHEADER << "========= ADD NEW VEHICLE =========" << Color::RESET << endl;

    type = InputHandler::getChar("Categories (E: Economy, L: Luxury, S: SUV, V: Van/Bus)", "ELSV", true);
    if (type == 'Z') return;

    // --- AUTOMATED NUMERIC ID GENERATION ---
    id = FileHandler::generateNextVehicleID(fleet);
    cout << Color::INFO << "[SYSTEM] Assigned Vehicle ID: " << Color::HIGHLIGHT << id << Color::RESET << endl;

    model = InputHandler::getString("Enter Model Name", true, true);
    if (model == InputHandler::CANCEL_STR) return;

    capacity = InputHandler::getInt("Enter Capacity", 1, 100, true);
    if (capacity == InputHandler::CANCEL_INT) return;

    rate = InputHandler::getFloat("Enter Rental Rate per Day (" + Pricing::CURRENCY + ")", 0.0f, 1000000.0f, true);
    if (rate == InputHandler::CANCEL_FLOAT) return;

    Vehicle* v = nullptr;
    if      (type == 'E') v = new Economy(id, model, capacity, rate);
    else if (type == 'L') {
        string features = InputHandler::getString("Enter Luxury Features", true, true);
        if (features == InputHandler::CANCEL_STR) return;
        v = new Luxury(id, model, capacity, rate, features);
    }
    else if (type == 'S') v = new SUV(id, model, capacity, rate);
    else if (type == 'V') v = new Van(id, model, capacity, rate);

    if (v) {
        fleet.push_back(v);
        cout << Color::SUCCESS << "[SUCCESS] Vehicle " << model << " added to fleet!" << Color::RESET << endl;
    }
}

/**
 * @brief REMOVE A VEHICLE from the fleet by ID
 */
void Admin::removeVehicle(vector<Vehicle*>& fleet)
{
    string id;
    cout << "\n" << Color::SUBHEADER << "========= REMOVE VEHICLE =========" << Color::RESET << endl;
    id = InputHandler::getString("Enter Vehicle ID to remove", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    for (auto it = fleet.begin(); it != fleet.end(); ++it) {
        if ((*it)->getID() == id) {
            if ((*it)->getStatus() == VehicleStatus::Rented) {
                cout << Color::ERR << "[ERROR] Cannot remove vehicle. It is currently RENTED." << Color::RESET << endl;
                cout << "        Please process the return before removing from fleet." << Color::RESET << endl;
                return;
            }

            cout << Color::WARNING << "[CONFIRM] Are you sure you want to PERMANENTLY delete " << (*it)->getModel() << "? (Y/N): " << Color::RESET;
            if (InputHandler::getChar("", "YN") == 'N') {
                cout << Color::INFO << "[SYSTEM] Deletion cancelled." << Color::RESET << endl;
                return;
            }

            cout << "[SYSTEM] Removing " << (*it)->getModel() << "...\n";
            delete *it;
            fleet.erase(it);
            cout << Color::SUCCESS << "[SUCCESS] Vehicle removed from system." << Color::RESET << endl;
            return;
        }
    }
    cout << Color::ERR << "[ERROR] Vehicle ID not found." << Color::RESET << endl;
}

/**
 * @brief Sub-menu for SELL & PURCHASE vehicles.
 */
void Admin::salePurchaseModule(vector<Vehicle*>& fleet, vector<User*>& users, FileHandler& fh)
{
    cout << "\n" << Color::SUBHEADER << "========= SALE / PURCHASE MODULE =========" << Color::RESET << endl;
    cout << "1. Sell Vehicle (to Customer)\n";
    cout << "2. Purchase Vehicle (from Supplier)\n";
    cout << "Z. Back\n";

    int choice = InputHandler::getInt("Selection", 1, 2, true);
    if (choice == InputHandler::CANCEL_INT) return;

    if (choice == 1) // Sell
    {
        string vID = InputHandler::getString("Vehicle ID to sell", false, true);
        if (vID == InputHandler::CANCEL_STR) return;

        string cID = InputHandler::getString("Customer ID (Buyer)", false, true);
        if (cID == InputHandler::CANCEL_STR) return;

        float price = InputHandler::getFloat("Sale Price (" + Pricing::CURRENCY + ")", 0, 100000000, true);
        if (price == InputHandler::CANCEL_FLOAT) return;

        string date;
        while(true) {
            date = InputHandler::getString("Sale Date (DD-MM-YYYY)");
            if (Validator::isValidDate(date)) break;
            cout << Color::ERR << "[ERROR] Invalid format." << Color::RESET << endl;
        }

        Vehicle* v = nullptr; for (Vehicle* x : fleet) if (x->getID() == vID) { v = x; break; }
        User* u = nullptr; for (User* x : users) if (x->getID() == cID) { u = x; break; }

        if (v && u && v->getStatus() == VehicleStatus::Available) {
            cout << Color::WARNING << "[CONFIRM] Finalize sale of " << v->getModel() << " to " << u->getName() << " for " << Pricing::CURRENCY << price << "? (Y/N): " << Color::RESET;
            if (InputHandler::getChar("", "YN") == 'N') return;

            v->setStatus(VehicleStatus::Sold);
            fh.appendTransaction("SALE", vID, cID, price, date);
            cout << Color::SUCCESS << "[SUCCESS] Sale finalized! Vehicle marked as SOLD." << Color::RESET << endl;
        } else {
            cout << Color::ERR << "[ERROR] Sale failed. Check IDs and vehicle availability." << Color::RESET << endl;
        }
    }

    else if (choice == 2) // Purchase
    {
        string supplier = InputHandler::getString("Supplier Name", true, true);
        if (supplier == InputHandler::CANCEL_STR) return;

        char type = InputHandler::getChar("Category (E/L/S/V)", "ELSV", true);
        if (type == 'Z') return;

        string id = InputHandler::getString("New Vehicle ID", false, true);
        if (id == InputHandler::CANCEL_STR) return;

        string model = InputHandler::getString("Model Name", true, true);
        if (model == InputHandler::CANCEL_STR) return;

        int capacity = InputHandler::getInt("Enter Capacity", 1, 100, true);
        if (capacity == InputHandler::CANCEL_INT) return;

        float price = InputHandler::getFloat("Purchase Price (" + Pricing::CURRENCY + ")", 0, 100000000, true);
        if (price == InputHandler::CANCEL_FLOAT) return;

        float rentRate = InputHandler::getFloat("Initial Rental Rate/Day (" + Pricing::CURRENCY + ")", 0, 1000000, true);
        if (rentRate == InputHandler::CANCEL_FLOAT) return;

        string date;
        while(true) {
            date = InputHandler::getString("Purchase Date (DD-MM-YYYY)");
            if (Validator::isValidDate(date)) break;
            cout << Color::ERR << "[ERROR] Invalid format." << Color::RESET << endl;
        }

        Vehicle* v = nullptr;
        if      (type == 'E') v = new Economy(id, model, capacity, rentRate);
        else if (type == 'L') v = new Luxury(id, model, capacity, rentRate, "Purchased Luxury");
        else if (type == 'S') v = new SUV(id, model, capacity, rentRate);
        else if (type == 'V') v = new Van(id, model, capacity, rentRate);

        if (v) {
            fleet.push_back(v);
            fh.appendTransaction("PURCHASE", id, "SUPPLIER", price, date);
            cout << Color::SUCCESS << "[SUCCESS] Vehicle purchased and added to fleet!" << Color::RESET << endl;
        }
    }
}

/**
 * @brief Displays all system records.
 */
void Admin::viewAllRecords(const vector<Vehicle*>& fleet, const vector<User*>& users)
{
    cout << "\n" << Color::SUBHEADER << "========= FULL SYSTEM RECORDS =========" << Color::RESET << endl;

    cout << Color::NOTICE << "\n[VEHICLE FLEET - " << fleet.size() << " Units]" << Color::RESET << "\n";
    cout << Color::TABLE_HEADER << "+----------+--------------------+------------+-------------+\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "| ID       | Model              | Category   | Status      |\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "+----------+--------------------+------------+-------------+\n" << Color::RESET;

    for (Vehicle* v : fleet)
    {
        string status = (v->getStatus() == VehicleStatus::Available ? Color::STATUS_AVAILABLE + "Available" + Color::RESET :
                v->getStatus() == VehicleStatus::Rented    ? Color::STATUS_RENTED + "Rented   " + Color::RESET : Color::STATUS_SOLD + "Sold     " + Color::RESET);
        cout << "| " << left << setw(9) << v->getID() << "| " << setw(19) << v->getModel() << "| " << setw(11) << v->getCategory() << "| " << status << " |\n";
    }
    cout << "+----------+--------------------+------------+-------------+\n";

    cout << Color::NOTICE << "\n[REGISTERED USERS - " << users.size() << " Accounts]" << Color::RESET << "\n";
    cout << Color::TABLE_HEADER << "+----------+--------------------------+-------------------+------------+\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "| User ID  | Name                     | CNIC              | Role       |\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "+----------+--------------------------+-------------------+------------+\n" << Color::RESET;
    for (User* u : users) {
        string type = (u->getRole() == "ADMIN" ? Color::RED + "Admin   " + Color::RESET : Color::HIGHLIGHT + "Customer" + Color::RESET);
        cout << "| " << left << setw(9) << u->getID() << "| " << setw(25) << u->getName() << "| " << setw(18) << u->getCNIC() << "| " << type << " |\n";
    }
    cout << "+----------+--------------------------+-------------------+------------+\n";
}

void Admin::processReturn(vector<Vehicle*>& fleet, vector<User*>& users, FileHandler& fh)
{
    cout << "\n" << Color::SUBHEADER << "========= ADMIN: PROCESS VEHICLE RETURN =========" << Color::RESET << endl;
    
    string vID = InputHandler::getString("Enter Vehicle ID to return", false, true);
    if (vID == InputHandler::CANCEL_STR) return;

    Vehicle* v = nullptr;
    for (Vehicle* x : fleet) if (x->getID() == vID) { v = x; break; }

    if (!v || v->getStatus() != VehicleStatus::Rented) {
        cout << Color::ERR << "[ERROR] Vehicle not found or not currently rented." << Color::RESET << endl;
        return;
    }

    string cID = InputHandler::getString("Enter Customer ID who is returning (if known)", false, true);
    if (cID == InputHandler::CANCEL_STR) return;

    User* customer = nullptr;
    for (User* u : users) if (u->getID() == cID) { customer = u; break; }

    // 1. Generate Inspection Report (Admin is the inspector)
    InspectionReport report(v, this); 
    report.fillReport();

    // 2. Automated Billing Duration
    string startDate = fh.getRentalStartDate(v->getID(), cID);
    string endDate = Validator::getCurrentDate();
    int days = 1;

    if (!startDate.empty()) {
        days = Validator::calculateDays(startDate, endDate);
        cout << Color::INFO << "[SYSTEM] Rental started on: " << startDate << Color::RESET << endl;
        cout << Color::INFO << "[SYSTEM] Today's Date      : " << endDate << Color::RESET << endl;
        cout << Color::INFO << "[SYSTEM] Total Days Calculated: " << days << Color::RESET << endl;
    } else {
        cout << Color::WARNING << "[WARNING] Rental start date not found in history." << Color::RESET << endl;
        days = InputHandler::getInt("> Please enter total days used manually", 1, 365, true);
        if (days == InputHandler::CANCEL_INT) return;
    }

    float baseBill = v->calculateCost(days);
    float discountedBill = v->calculateDiscountedCost(days);
    float damageFee = report.getDamageFee();
    float totalBill = discountedBill + damageFee;

    cout << "\n" << Color::NOTICE << "[!] TOTAL CHARGES: " << Pricing::CURRENCY << (int)totalBill << Color::RESET << "\n";
    if (InputHandler::getChar("[CONFIRM] Finalize return? (Y/N)", "YN", true) == 'N') return;

    v->setStatus(VehicleStatus::Available);
    fh.saveInspection(report);
    fh.appendTransaction("RENT_RETURN", vID, (customer ? customer->getID() : "ADMIN_FORCE"), totalBill, report.getDate());

    cout << Color::SUCCESS << "[SUCCESS] Vehicle " << vID << " returned and available." << Color::RESET << endl;
}

bool Admin::hasActiveRentals(const string& userID, FileHandler& fh)
{
    ifstream file(Config::TRANSACTIONS_FILE);
    if (!file.is_open()) return false;

    // Track unbalanced rentals per vehicle for this user
    struct RentalState { int starts = 0; int returns = 0; };
    vector<pair<string, RentalState>> state;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string type, vID, cID, amt, date;
        getline(ss, type, '|');
        getline(ss, vID, '|');
        getline(ss, cID, '|');
        
        if (cID == userID) {
            bool found = false;
            for (auto& p : state) {
                if (p.first == vID) {
                    if (type == "RENT_START") p.second.starts++;
                    else if (type == "RENT_RETURN") p.second.returns++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                RentalState rs;
                if (type == "RENT_START") rs.starts = 1;
                else if (type == "RENT_RETURN") rs.returns = 1;
                state.push_back({vID, rs});
            }
        }
    }
    file.close();

    for (const auto& p : state) {
        if (p.second.starts > p.second.returns) return true;
    }
    return false;
}
