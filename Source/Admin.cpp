#include "Admin.h"
#include "Vehicle.h"
#include "Economy.h"
#include "Luxury.h"
#include "SUV.h"
#include "Van.h"
#include "FileHandler.h"

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
    cout << "+----------------------------------------------------------+\n";
    cout << "|                  ADMIN CONTROL PANEL                     |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|  Logged in as : " << left << setw(40)
            << (getName() + " (ID: " + getID() + ")") << "|\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|   [1]  Add New Vehicle                                   |\n";
    cout << "|   [2]  Remove Vehicle                                    |\n";
    cout << "|   [3]  Sale / Purchase Module                            |\n";
    cout << "|   [4]  View All Records                                  |\n";
    cout << "|   [5]  Logout                                            |\n";
    cout << "+----------------------------------------------------------+\n\n";
    cout << "Enter your choice (1-5): ";
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

    cout << "\n========= ADD NEW VEHICLE =========\n====================================" << endl;
    cout << "Categories: \nE: Economy\nL: Luxury\nS: SUV\nV: Van/Bus\n" << endl << endl;
    cout << "Selection: ";
    cin >> type;
    type = toupper(type);

    cout << "Enter Vehicle ID (e.g., V001): ";
    cin >> id;

    // Check if ID already exists or NOT
    for (Vehicle* v : fleet)
    {
        if (v->getID() == id)
        {
            cout << "[ERROR] Vehicle ID already exists!" << endl;
            return;
        }
    }

    cout << "Enter Model Name: ";
    cin.ignore();
    getline(cin, model);
    cout << "Enter Year: "; cin >> year;
    cout << "Enter Capacity: "; cin >> capacity;
    cout << "Enter Rental Rate per Day: "; cin >> rate;

    Vehicle* v = nullptr;

    if (type == 'E') v = new Economy(id, model, year, capacity, rate);
    else if (type == 'L')
    {
        string features;
        cout << "Enter Luxury Features: ";
        cin.ignore();
        getline(cin, features);
        v = new Luxury(id, model, year, capacity, rate, features);
    }
    else if (type == 'S'){v = new SUV(id, model, year, capacity, rate);}
    else if (type == 'V'){v = new Van(id, model, year, capacity, rate);}
    if (v)
    {
        fleet.push_back(v);
        cout << "\n[SYSTEM] Vehicle " << model << " added successfully!" << endl;
    }
    else {cout << "[ERROR] Invalid category selected." << endl;}
}



/**
 * @brief REMOVE A VEHICLE from the fleet by ID
 */
void Admin::removeVehicle(vector<Vehicle*>& fleet)
{
    string id;
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                   REMOVE VEHICLE FROM FLEET              |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "  Please enter the unique ID of the vehicle to delete:\n\n";
    cout << "  > Vehicle ID to Remove : "; cin >> id;
    cout << "\n+----------------------------------------------------------+\n";
    for (auto it = fleet.begin(); it != fleet.end(); ++it) {
        if ((*it)->getID() == id) {
            cout << "  [SYSTEM] Removing " << (*it)->getModel() << "...\n";
            delete *it;      // Free memory
            fleet.erase(it); // Remove from vector
            cout << "  [SUCCESS] Vehicle has been purged from the system.\n";
            cout << "+----------------------------------------------------------+\n";
            return;
        }
    }
    cout << "  [ERROR] Vehicle ID '" << id << "' not found.\n";
    cout << "+----------------------------------------------------------+\n";
}



/**
 * @brief Sub-menu for SELL & PURCHASE vehicles.
 */



void Admin::salePurchaseModule(vector<Vehicle*>& fleet, vector<User*>& users, FileHandler& fh)
{
    int choice = 0;
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                SALE / PURCHASE MODULE                    |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                                                          |\n";
    cout << "|   [1]   Sell Vehicle                                     |\n";
    cout << "|   [2]   Purchase Vehicle                                 |\n";
    cout << "|   [3]   Back to Admin Menu                               |\n";
    cout << "|                                                          |\n";
    cout << "+----------------------------------------------------------+\n\n";
    cout << "Selection: ";
    cin >> choice;


    // Sell Vehicle
    if (choice == 1)
    {
        string vID, cID;
        float price;

        cout << "Enter Vehicle ID to sell: "; cin >> vID;
        cout << "Enter Buyer Customer ID: "; cin >> cID;
        cout << "Enter Sale Price: "; cin >> price;

        Vehicle* targetV = nullptr;
        for (Vehicle* v : fleet) if (v->getID() == vID) { targetV = v; break; }

        User* targetC = nullptr;
        for (User* u : users) if (u->getID() == cID) { targetC = u; break; }

        if (targetV && targetC && targetV->getStatus() == VehicleStatus::Available)
        {
            targetV->setStatus(VehicleStatus::Sold);
            cout << "\n";
            cout << "+======================================================+\n";
            cout << "|                   SALE RECEIPT                       |\n";
            cout << "+======================================================+\n";
            cout << "| Transaction Type     :  VEHICLE SALE                 |\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| Vehicle ID           :  " << left << setw(35) << vID << "|\n";
            cout << "| Vehicle Model        :  " << left << setw(35) << targetV->getModel() << "|\n";
            cout << "| Buyer                :  " << left << setw(35) << targetC->getName() << "|\n";
            cout << "| Selling Price        :  $" << left << setw(34) << price << "|\n";
            cout << "+======================================================+\n";
            cout << "|                TRANSACTION SUCCESSFUL                |\n";
            cout << "|          Vehicle has been marked as SOLD             |\n";
            cout << "+======================================================+\n\n";

            // Log Transaction immediately using FileHandler
            fh.appendTransaction("SALE", vID, cID, price, "14/05/2026");
            cout << "[SYSTEM] Sale record archived in Transactions.txt via FileHandler" << endl;
        }


        else
        {
            cout << "[ERROR] Sale failed. Check ID validity and vehicle availability." << endl;
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
        cout << "+----------------------------------------------------------+\n";
        cout << "|                VEHICLE ACQUISITION & PURCHASE            |\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "  Enter procurement details below:\n\n";
        cout << "  > Supplier Name    : "; cin.ignore(); getline(cin, supplier);
        cout << "  > Category (E/L/S/V): "; cin >> type;
        cout << "  > New Vehicle ID   : "; cin >> id;
        cout << "  > Model Name       : "; cin.ignore(); getline(cin, model);
        cout << "  > Release Year     : "; cin >> year;
        cout << "  > Passenger Cap.   : "; cin >> capacity;
        cout << "  > Purchase Price   : "; cin >> price;
        cout << "  > Rental Rate/Day  : "; cin >> rentRate;

        Vehicle* v = nullptr;
        type = toupper(type);

        if (type == 'E') v = new Economy(id, model, year, capacity, rentRate);
        else if (type == 'L') v = new Luxury(id, model, year, capacity, rentRate, "Purchased Luxury");
        else if (type == 'S') v = new SUV(id, model, year, capacity, rentRate);
        else if (type == 'V') v = new Van(id, model, year, capacity, rentRate);

        cout << "+----------------------------------------------------------+\n";


        if (v)
        {
            fleet.push_back(v);

            cout << "\n";
            cout << "+======================================================+\n";
            cout << "|                  PURCHASE RECEIPT                    |\n";
            cout << "+======================================================+\n";
            cout << "| Transaction   :  VEHICLE PURCHASE                    |\n";
            cout << "| Supplier      :  " << left << setw(36) << supplier << "|\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| Vehicle ID    :  " << left << setw(36) << id << "|\n";
            cout << "| Model         :  " << left << setw(36) << model << "|\n";
            cout << "| Cost Price    :  $" << left << setw(35) << price << "|\n";
            cout << "| Rental Rate   :  $" << left << setw(35) << rentRate << "|\n";
            cout << "+======================================================+\n";
            cout << "|        [SUCCESS] New vehicle added to fleet.         |\n";
            cout << "+======================================================+\n\n";
        }

        else
        {
            cout << "[ERROR] Invalid category." << endl;
        }
    }
}


/**
 * @brief Displays all system records.
 */

void Admin::viewAllRecords(const vector<Vehicle*>& fleet, const vector<User*>& users)
{
    cout << "\n";
    cout << "+===========================================================+\n";
    cout << "|                   FULL SYSTEM RECORDS                     |\n";
    cout << "+===========================================================+\n\n";

    cout << "+------------------- VEHICLE FLEET --------------------------+\n";
    cout << "| Total Vehicles : " << left << setw(41) << fleet.size() << "|\n";

    if (fleet.empty())
    {
        cout << "| No vehicles available in the fleet.                   |\n";
    }

    else
    {
        cout << "+----------+--------------------------+--------+-------------+\n";
        cout << "|    ID    |        Model             |  Year  |   Status    |\n";
        cout << "+----------+--------------------------+--------+-------------+\n";

        for (Vehicle* v : fleet)
        {
            cout << "| " << left << setw(9)  << v->getID()
                << "| " << left << setw(25) << v->getModel()
                << "| " << left << setw(7)  << v->getYear()
                << "| " << left << setw(12)
                << (v->getStatus() == VehicleStatus::Available ? "Available" :
                    (v->getStatus() == VehicleStatus::Rented    ? "Rented"    : "Sold"))
                << "|\n";
        }
        cout << "+----------+--------------------------+--------+-------------+\n";
    }

    cout << "\n";

    cout << "+------------------- REGISTERED USERS ---------------------+\n";
    cout << "| Total Users    : " << left << setw(41) << users.size() << "|\n";

    if (users.empty())
    {
        cout << "| No registered users found.                            |\n";
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
                << "| " << left << setw(11) << (u->getID()[0] == 'A' ? "Admin" : "Customer")
                << "|\n";
        }
        cout << "+----------+--------------------------------+------------+\n";
    }
}
