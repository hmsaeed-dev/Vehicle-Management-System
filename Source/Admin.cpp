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

#include <iostream>
#include <iomanip>
using namespace std;

// Admin Class Constructor
Admin::Admin(string id, string username, string name, string phone, string password)
    : User(id, username, name, phone, password) {}

void Admin::showDashboard(const vector<Vehicle*>& fleet)
{
    int available = 0, rented = 0, sold = 0;
    for (Vehicle* v : fleet) {
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
    cout << "|  Logged in as " << left << setw(43) << getName() << "|\n";
    cout << Color::HEADER << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "|                                                          |\n";
    cout << "|   [1]  Add New Vehicle                                   |\n";
    cout << "|   [2]  Remove Vehicle                                    |\n";
    cout << "|   [3]  Delete Customer Account                           |\n";
    cout << "|   [4]  Sale / Purchase Module                            |\n";
    cout << "|   [5]  View All Records                                  |\n";
    cout << "|   [Z]  Logout                                            |\n";
    cout << "|                                                          |\n";
    cout << Color::RED << "+----------------------------------------------------------+\n\n" << Color::RESET;
}

void Admin::removeUser(vector<User*>& users, FileHandler& fh)
{
    string id;
    cout << "\n" << Color::SUBHEADER << "========= DELETE CUSTOMER ACCOUNT =========" << Color::RESET << endl;
    id = InputHandler::getString("Enter User ID to remove", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    if (id == this->getID()) {
        cout << Color::ERR << "[ERROR] You cannot delete your own admin account." << Color::RESET << endl;
        return;
    }

    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getID() == id) {
            if ((*it)->getID()[0] == 'A') {
                cout << Color::ERR << "[ERROR] Security Breach: Admins cannot delete other Admins." << Color::RESET << endl;
                return;
            }

            cout << Color::WARNING << "[CONFIRM] Are you sure you want to PERMANENTLY delete account: " << (*it)->getName() << " (ID: " << id << ")? (Y/N): " << Color::RESET;
            if (InputHandler::getChar("", "YN") == 'N') {
                cout << Color::INFO << "[SYSTEM] Deletion cancelled." << Color::RESET << endl;
                return;
            }

            cout << "[SYSTEM] Purging user data...\n";
            delete *it;
            users.erase(it);
            fh.saveUsers(users); // Persist immediately
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
    int year, capacity;

    cout << "\n" << Color::SUBHEADER << "========= ADD NEW VEHICLE =========" << Color::RESET << endl;

    type = InputHandler::getChar("Categories (E: Economy, L: Luxury, S: SUV, V: Van/Bus)", "ELSV", true);
    if (type == 'Z') return;

    while (true) {
        id = InputHandler::getString("Enter Vehicle ID (e.g., E001)", false, true);
        if (id == InputHandler::CANCEL_STR) return;

        bool exists = false;
        for (Vehicle* v : fleet) if (v->getID() == id) { exists = true; break; }
        if (!exists) break;
        cout << Color::ERR << "[ERROR] Vehicle ID already exists!" << Color::RESET << endl;
    }

    model = InputHandler::getString("Enter Model Name", true, true);
    if (model == InputHandler::CANCEL_STR) return;

    year = InputHandler::getInt("Enter Year", 1900, 2100, true);
    if (year == InputHandler::CANCEL_INT) return;

    capacity = InputHandler::getInt("Enter Capacity", 1, 100, true);
    if (capacity == InputHandler::CANCEL_INT) return;

    rate = InputHandler::getFloat("Enter Rental Rate per Day (" + Pricing::CURRENCY + ")", 0.0f, 1000000.0f, true);
    if (rate == InputHandler::CANCEL_FLOAT) return;

    Vehicle* v = nullptr;
    if      (type == 'E') v = new Economy(id, model, year, capacity, rate);
    else if (type == 'L') {
        string features = InputHandler::getString("Enter Luxury Features", true, true);
        if (features != InputHandler::CANCEL_STR) v = new Luxury(id, model, year, capacity, rate, features);
    }
    else if (type == 'S') v = new SUV(id, model, year, capacity, rate);
    else if (type == 'V') v = new Van(id, model, year, capacity, rate);

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

        int year = InputHandler::getInt("Year", 1900, 2100, true);
        if (year == InputHandler::CANCEL_INT) return;

        int capacity = InputHandler::getInt("Capacity", 1, 100, true);
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
        if      (type == 'E') v = new Economy(id, model, year, capacity, rentRate);
        else if (type == 'L') v = new Luxury(id, model, year, capacity, rentRate, "Purchased Luxury");
        else if (type == 'S') v = new SUV(id, model, year, capacity, rentRate);
        else if (type == 'V') v = new Van(id, model, year, capacity, rentRate);

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
    cout << Color::TABLE_HEADER << "+----------+--------------------+------+------------+-------------+\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "| ID       | Model              | Year | Category   | Status      |\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "+----------+--------------------+------+------------+-------------+\n" << Color::RESET;

    for (Vehicle* v : fleet)
    {
        string status = (v->getStatus() == VehicleStatus::Available ? Color::STATUS_AVAILABLE + "Available" + Color::RESET :
                v->getStatus() == VehicleStatus::Rented    ? Color::STATUS_RENTED + "Rented   " + Color::RESET : Color::STATUS_SOLD + "Sold     " + Color::RESET);
        cout << "| " << left << setw(9) << v->getID() << "| " << setw(19) << v->getModel() << "| " << setw(5) << v->getYear() << "| " << setw(11) << v->getCategory() << "| " << status << " |\n";
    }
    cout << "+----------+--------------------+------+------------+-------------+\n";

    cout << Color::NOTICE << "\n[REGISTERED USERS - " << users.size() << " Accounts]" << Color::RESET << "\n";
    cout << Color::TABLE_HEADER << "+----------+--------------------------+------------+\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "| User ID  | Name                     | Type       |\n" << Color::RESET;
    cout << Color::TABLE_HEADER << "+----------+--------------------------+------------+\n" << Color::RESET;
    for (User* u : users) {
        string type = (u->getID()[0] == 'A' ? Color::RED + "Admin   " + Color::RESET : Color::HIGHLIGHT + "Customer" + Color::RESET);
        cout << "| " << left << setw(9) << u->getID() << "| " << setw(25) << u->getName() << "| " << type << " |\n";
    }
    cout << "+----------+--------------------------+------------+\n";
}
