#include "Admin.h"
#include "Vehicle.h"
#include "Economy.h"
#include "Luxury.h"
#include "SUV.h"
#include "Van.h"
#include "FileHandler.h"
#include "Colors.h"
#include "InputHandler.h"

#include <iostream>
#include <iomanip>
using namespace std;

// Admin Class Constructor
Admin::Admin(string id, string username, string name, string phone, string password)
    : User(id, username, name, phone, password) {}

/**
* @brief Displays the Admin-specific console menu.
*/


void Admin::showMenu()
{
    cout << "\n";
    cout << Color::BOLD << Color::RED;
    cout << "+----------------------------------------------------------+\n";
    cout << "|                  ADMIN CONTROL PANEL                     |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "|  Logged in as : " << left << setw(40)
            << (getName() + " (ID: " + getID() + ")") << "|\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|   [1]  Add New Vehicle                                   |\n";
    cout << "|   [2]  Remove Vehicle                                    |\n";
    cout << "|   [3]  Sale / Purchase Module                            |\n";
    cout << "|   [4]  View All Records                                  |\n";
    cout << "|   [5]  Logout                                            |\n";
    cout << "+----------------------------------------------------------+\n\n";
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

    cout << "\n" << Color::BOLD << Color::BLUE << "========= ADD NEW VEHICLE =========" << Color::RESET << endl;
    
    type = InputHandler::getChar("Categories (E: Economy, L: Luxury, S: SUV, V: Van/Bus)", "ELSV", true);
    if (type == '0') return;

    id = InputHandler::getString("Enter Vehicle ID (e.g., V001): ", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    // Check if ID already exists or NOT
    for (Vehicle* v : fleet)
    {
        if (v->getID() == id)
        {
            cout << Color::ERROR << "[ERROR] Vehicle ID already exists!" << Color::RESET << endl;
            return;
        }
    }

    model = InputHandler::getString("Enter Model Name: ", true, true);
    if (model == InputHandler::CANCEL_STR) return;

    year = InputHandler::getInt("Enter Year: ", 1900, 2026, true);
    if (year == InputHandler::CANCEL_INT) return;

    capacity = InputHandler::getInt("Enter Capacity: ", 1, 100, true);
    if (capacity == InputHandler::CANCEL_INT) return;

    rate = InputHandler::getFloat("Enter Rental Rate per Day: ", 0.0f, 1000000.0f, true);
    if (rate == InputHandler::CANCEL_FLOAT) return;

    Vehicle* v = nullptr;

    if (type == 'E') v = new Economy(id, model, year, capacity, rate);
    else if (type == 'L')
    {
        string features = InputHandler::getString("Enter Luxury Features: ", true, true);
        if (features == InputHandler::CANCEL_STR) return;
        v = new Luxury(id, model, year, capacity, rate, features);
    }
    else if (type == 'S'){v = new SUV(id, model, year, capacity, rate);}
    else if (type == 'V'){v = new Van(id, model, year, capacity, rate);}

    if (v)
    {
        fleet.push_back(v);
        cout << "\n" << Color::SUCCESS << "[SYSTEM] Vehicle " << model << " added successfully!" << Color::RESET << endl;
    }
}



/**
 * @brief REMOVE A VEHICLE from the fleet by ID
 */
void Admin::removeVehicle(vector<Vehicle*>& fleet)
{
    string id;
    cout << "\n";
    cout << Color::BOLD << Color::RED;
    cout << "+----------------------------------------------------------+\n";
    cout << "|                   REMOVE VEHICLE FROM FLEET              |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "  Please enter the unique ID of the vehicle to delete:\n\n";
    
    id = InputHandler::getString("  > Vehicle ID to Remove: ", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    cout << "\n+----------------------------------------------------------+\n";
    for (auto it = fleet.begin(); it != fleet.end(); ++it) {
        if ((*it)->getID() == id) {
            cout << "  [SYSTEM] Removing " << (*it)->getModel() << "...\n";
            delete *it;      // Free memory
            fleet.erase(it); // Remove from vector
            cout << Color::SUCCESS << "  [SUCCESS] Vehicle has been purged from the system.\n" << Color::RESET;
            cout << "+----------------------------------------------------------+\n";
            return;
        }
    }
    cout << Color::ERROR << "  [ERROR] Vehicle ID '" << id << "' not found.\n" << Color::RESET;
    cout << "+----------------------------------------------------------+\n";
}



/**
 * @brief Sub-menu for SELL & PURCHASE vehicles.
 */



void Admin::salePurchaseModule(vector<Vehicle*>& fleet, vector<User*>& users, FileHandler& fh)
{
    int choice = 0;
    cout << "\n";
    cout << Color::BOLD << Color::CYAN;
    cout << "+----------------------------------------------------------+\n";
    cout << "|                SALE / PURCHASE MODULE                    |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "|                                                          |\n";
    cout << "|   [1]   Sell Vehicle                                     |\n";
    cout << "|   [2]   Purchase Vehicle                                 |\n";
    cout << "|   [3]   Back to Admin Menu                               |\n";
    cout << "|                                                          |\n";
    cout << Color::CYAN << "+----------------------------------------------------------+\n\n" << Color::RESET;
    
    choice = InputHandler::getInt("Selection: ", 1, 3);


    // Sell Vehicle
    if (choice == 1)
    {
        string vID, cID;
        float price;

        vID = InputHandler::getString("Enter Vehicle ID to sell: ", false, true);
        if (vID == InputHandler::CANCEL_STR) return;

        cID = InputHandler::getString("Enter Buyer Customer ID: ", false, true);
        if (cID == InputHandler::CANCEL_STR) return;

        price = InputHandler::getFloat("Enter Sale Price: ", 0, 10000000, true);
        if (price == InputHandler::CANCEL_FLOAT) return;

        Vehicle* targetV = nullptr;
        for (Vehicle* v : fleet) if (v->getID() == vID) { targetV = v; break; }

        User* targetC = nullptr;
        for (User* u : users) if (u->getID() == cID) { targetC = u; break; }

        if (targetV && targetC && targetV->getStatus() == VehicleStatus::Available)
        {
            targetV->setStatus(VehicleStatus::Sold);
            cout << "\n";
            cout << Color::BOLD << Color::SUCCESS;
            cout << "+======================================================+\n";
            cout << "|                   SALE RECEIPT                       |\n";
            cout << "+======================================================+\n" << Color::RESET;
            cout << "| Transaction Type     :  VEHICLE SALE                 |\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| Vehicle ID           :  " << left << setw(35) << vID << "|\n";
            cout << "| Vehicle Model        :  " << left << setw(35) << targetV->getModel() << "|\n";
            cout << "| Buyer                :  " << left << setw(35) << targetC->getName() << "|\n";
            cout << "| Selling Price        :  $" << left << setw(34) << price << "|\n";
            cout << Color::SUCCESS << "+======================================================+\n";
            cout << "|                TRANSACTION SUCCESSFUL                |\n";
            cout << "|          Vehicle has been marked as SOLD             |\n";
            cout << "+======================================================+\n" << Color::RESET << endl;

            // Log Transaction immediately using FileHandler
            fh.appendTransaction("SALE", vID, cID, price, "14/05/2026");
            cout << Color::INFO << "[SYSTEM] Sale record archived in Transactions.txt via FileHandler" << Color::RESET << endl;
        }


        else
        {
            cout << Color::ERROR << "[ERROR] Sale failed. Check ID validity and vehicle availability." << Color::RESET << endl;
        }
    }

    // Purchase Vehicle
    else if (choice == 2)
    {
        string supplier, id, model;
        float price, rentRate;
        char type;
        int year, capacity;

        cout << "\n";
        cout << Color::BOLD << Color::BLUE;
        cout << "+----------------------------------------------------------+\n";
        cout << "|                VEHICLE ACQUISITION & PURCHASE            |\n";
        cout << "+----------------------------------------------------------+\n" << Color::RESET;
        cout << "  Enter procurement details below:\n\n";
        
        supplier = InputHandler::getString(Color::INFO + "  > Supplier Name    : " + Color::RESET, true, true);
        if (supplier == InputHandler::CANCEL_STR) return;

        type = InputHandler::getChar(Color::INFO + "  > Category (E/L/S/V): " + Color::RESET, "ELSV", true);
        if (type == '0') return;

        id = InputHandler::getString(Color::INFO + "  > New Vehicle ID   : " + Color::RESET, false, true);
        if (id == InputHandler::CANCEL_STR) return;

        model = InputHandler::getString(Color::INFO + "  > Model Name       : " + Color::RESET, true, true);
        if (model == InputHandler::CANCEL_STR) return;

        year = InputHandler::getInt(Color::INFO + "  > Release Year     : " + Color::RESET, 1900, 2026, true);
        if (year == InputHandler::CANCEL_INT) return;

        capacity = InputHandler::getInt(Color::INFO + "  > Passenger Cap.   : " + Color::RESET, 1, 100, true);
        if (capacity == InputHandler::CANCEL_INT) return;

        price = InputHandler::getFloat(Color::INFO + "  > Purchase Price   : " + Color::RESET, 0, 10000000, true);
        if (price == InputHandler::CANCEL_FLOAT) return;

        rentRate = InputHandler::getFloat(Color::INFO + "  > Rental Rate/Day  : " + Color::RESET, 0, 1000000, true);
        if (rentRate == InputHandler::CANCEL_FLOAT) return;

        Vehicle* v = nullptr;

        if (type == 'E') v = new Economy(id, model, year, capacity, rentRate);
        else if (type == 'L') v = new Luxury(id, model, year, capacity, rentRate, "Purchased Luxury");
        else if (type == 'S') v = new SUV(id, model, year, capacity, rentRate);
        else if (type == 'V') v = new Van(id, model, year, capacity, rentRate);

        cout << Color::BLUE << "+----------------------------------------------------------+\n" << Color::RESET;


        if (v)
        {
            fleet.push_back(v);

            cout << "\n";
            cout << Color::BOLD << Color::SUCCESS;
            cout << "+======================================================+\n";
            cout << "|                  PURCHASE RECEIPT                    |\n";
            cout << "+======================================================+\n" << Color::RESET;
            cout << "| Transaction   :  VEHICLE PURCHASE                    |\n";
            cout << "| Supplier      :  " << left << setw(36) << supplier << "|\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| Vehicle ID    :  " << left << setw(36) << id << "|\n";
            cout << "| Model         :  " << left << setw(36) << model << "|\n";
            cout << "| Cost Price    :  $" << left << setw(35) << price << "|\n";
            cout << "| Rental Rate   :  $" << left << setw(35) << rentRate << "|\n";
            cout << Color::SUCCESS << "+======================================================+\n";
            cout << "|        [SUCCESS] New vehicle added to fleet.         |\n";
            cout << "+======================================================+\n" << Color::RESET << endl;
        }

        else
        {
            cout << Color::ERROR << "[ERROR] Invalid category." << Color::RESET << endl;
        }
    }
}


/**
 * @brief Displays all system records.
 */

void Admin::viewAllRecords(const vector<Vehicle*>& fleet, const vector<User*>& users)
{
    cout << "\n";
    cout << Color::BOLD << Color::BLUE;
    cout << "+===========================================================+\n";
    cout << "|                   FULL SYSTEM RECORDS                     |\n";
    cout << "+===========================================================+\n" << Color::RESET;

    cout << Color::CYAN << "\n+------------------- VEHICLE FLEET --------------------------+\n" << Color::RESET;
    cout << "| Total Vehicles : " << left << setw(41) << fleet.size() << "|\n";

    if (fleet.empty())
    {
        cout << Color::WARNING << "| No vehicles available in the fleet.                   |\n" << Color::RESET;
    }

    else
    {
        cout << "+----------+--------------------------+--------+-------------+\n";
        cout << "|    ID    |        Model             |  Year  |   Status    |\n";
        cout << "+----------+--------------------------+--------+-------------+\n";

        for (Vehicle* v : fleet)
        {
            string coloredStatus = (v->getStatus() == VehicleStatus::Available ? Color::GREEN + "Available " + Color::RESET :
                                   (v->getStatus() == VehicleStatus::Rented    ? Color::RED + "Rented    " + Color::RESET : Color::YELLOW + "Sold      " + Color::RESET));

            cout << "| " << left << setw(9)  << v->getID()
                << "| " << left << setw(25) << v->getModel()
                << "| " << left << setw(7)  << v->getYear()
                << "| " << left << coloredStatus
                << "|\n";
        }
        cout << "+----------+--------------------------+--------+-------------+\n";
    }

    cout << "\n";

    cout << Color::MAGENTA << "+------------------- REGISTERED USERS ---------------------+\n" << Color::RESET;
    cout << "| Total Users    : " << left << setw(41) << users.size() << "|\n";

    if (users.empty())
    {
        cout << Color::WARNING << "| No registered users found.                            |\n" << Color::RESET;
    }
    else
    {
        cout << "+----------+--------------------------------+------------+\n";
        cout << "| User ID  |            Name                |    Type    |\n";
        cout << "+----------+--------------------------------+------------+\n";

        for (User* u : users)
        {
            cout << "| " << left << setw(9)  << u->getID()
                << "| " << left << setw(31) << u->getName()
                << "| " << left << setw(11) << (u->getID()[0] == 'A' ? Color::RED + "Admin" + Color::RESET : Color::GREEN + "Customer" + Color::RESET)
                << "|\n";
        }
        cout << "+----------+--------------------------------+------------+\n";
    }
}
