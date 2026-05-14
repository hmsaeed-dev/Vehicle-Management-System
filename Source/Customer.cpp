#include "Customer.h"
#include "RentalTransaction.h"
#include "InspectionReport.h"
#include "FileHandler.h"

#include <iostream>
#include <iomanip>

using namespace std;

Customer::Customer(string id, string name, string phone, string password)
    : User(id, name, phone, password) {}

/**
 * @brief Displays the Customer-specific console menu.
 */
void Customer::showMenu() {
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                   CUSTOMER DASHBOARD                     |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| Welcome, " << left << setw(48) << getName() << "|\n";
    cout << "+----------------------------------------------------------+\n\n";

    cout << "|   [1]   Search for a Vehicle                             |\n";
    cout << "|   [2]   Rent a Vehicle                                   |\n";
    cout << "|   [3]   Return a Vehicle                                 |\n";
    cout << "|   [4]   Plan a Trip                                      |\n";
    cout << "|   [5]   View My Rental History                           |\n";
    cout << "|   [6]   Logout                                           |\n";
    cout << "+----------------------------------------------------------+\n\n";
    cout << "Selection: ";
}

/**
 * @brief Displays the customer's past rental transactions.
 */

void Customer::viewRentalHistory()
{
    cout << "\n";
    cout << "+==========================================================+\n";
    cout << "|                 YOUR RENTAL HISTORY                      |\n";
    cout << "+==========================================================+\n";

    if (rentalHistory.empty())
    {
        cout << "| No previous records found.                               |\n";
    }

    else
    {
        for (const string& record : rentalHistory)
        {
            cout << "| - " << left << setw(53) << record << "|\n";
        }
    }
    cout << "+==========================================================+\n";
}



void Customer::addToHistory(const string& record) {
    rentalHistory.push_back(record);
}

/**
 * @brief Logic for renting a vehicle.
 */
void Customer::rentVehicle(vector<Vehicle*>& fleet, FileHandler& fh) {
    string id;
    cout << "\n--- RENT A VEHICLE ---" << endl;
    cout << "Enter Vehicle ID to rent: ";
    cin >> id;

    for (Vehicle* v : fleet) {
        if (v->getID() == id) {
            if (!v->getAvailable()) {
                cout << "[ERROR] This vehicle is already rented." << endl;
                return;
            }

            // Generate Transaction
            RentalTransaction* txn = new RentalTransaction("RTX-" + id, v, this, "14/05/2026", "10:00 AM");
            txn->finalise();

            // Log Transaction immediately
            fh.appendTransaction("RENT_START", v->getID(), this->getID(), 0.0, "14/05/2026");

            addToHistory("Started Rental of " + v->getModel() + " (ID: " + v->getID() + ")");
            cout << "[SUCCESS] You have successfully rented the " << v->getModel() << "!" << endl;
            delete txn;
            return;
        }
    }
    cout << "[ERROR] Vehicle ID not found." << endl;
}

/**
 * @brief Logic for returning a vehicle.
 */
void Customer::returnVehicle(vector<Vehicle*>& fleet, FileHandler& fh) {
    string id;
    cout << "\n--- RETURN A VEHICLE ---" << endl;
    cout << "Enter Vehicle ID you are returning: ";
    cin >> id;

    for (Vehicle* v : fleet) {
        if (v->getID() == id) {
            if (v->getStatus() != VehicleStatus::Rented) {
                cout << "[ERROR] This vehicle was never rented out." << endl;
                return;
            }

            // 1. Generate Inspection Report
            InspectionReport report(v, this);
            report.fillReport();
            fh.saveInspection(report); // Save to file

            // 2. Finalize Billing
            int days;
            cout << "Enter total days used: ";
            cin >> days;

            float baseBill = v->calculateCost(days);
            float damageFee = report.getDamageFee();
            float totalBill = baseBill + damageFee;

            v->setStatus(VehicleStatus::Available); // Return to garage

            // Log Transaction immediately
            fh.appendTransaction("RENT_RETURN", v->getID(), this->getID(), totalBill, "14/05/2026");

            cout << "\n";
            cout << "+======================================================+\n";
            cout << "|                  FINAL RENTAL RECEIPT                |\n";
            cout << "+======================================================+\n";
            cout << "| Vehicle          :  " << left << setw(33) << v->getModel() << "|\n";
            cout << "| Duration         :  " << left << setw(28) << days << " days |" << "\n";
            cout << "| Base Rental Cost :  $" << left << setw(32) << baseBill << "|\n";
            cout << "| Damage Fees      :  $" << left << setw(32) << damageFee << "|\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| TOTAL AMOUNT     :  $" << left << setw(32) << totalBill << "|\n";
            cout << "+======================================================+\n";
            cout << "|           [SUCCESS] Vehicle Returned                 |\n";
            cout << "+======================================================+\n\n";

            addToHistory("Returned " + v->getModel() + " (Final Bill: $" + to_string(totalBill) + ")");
            return;
        }
    }
    cout << "[ERROR] You do not have a vehicle with that ID." << endl;
}
