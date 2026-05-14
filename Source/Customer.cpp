#include "Customer.h"
#include "RentalTransaction.h"
#include "InspectionReport.h"
#include "FileHandler.h"
#include "Colors.h"
#include "InputHandler.h"

#include <iostream>
#include <iomanip>

using namespace std;

Customer::Customer(string id, string username, string name, string phone, string password)
    : User(id, username, name, phone, password) {}

/**
* @brief Displays the Customer-specific console menu.
*/


void Customer::showMenu()
{
    cout << "\n";
    cout << Color::BOLD << Color::GREEN;
    cout << "+==========================================================+\n";
    cout << "|                   CUSTOMER DASHBOARD                     |\n";
    cout << "+==========================================================+\n" << Color::RESET;
    cout << "| Welcome, " << Color::CYAN << left << setw(48) << getName() << Color::RESET << "|\n";
    cout << Color::BOLD << Color::GREEN << "+----------------------------------------------------------+\n" << Color::RESET;

    cout << "|   [1]   Search for a Vehicle                             |\n";
    cout << "|   [2]   Rent a Vehicle                                   |\n";
    cout << "|   [3]   Return a Vehicle                                 |\n";
    cout << "|   [4]   Plan a Trip                                      |\n";
    cout << "|   [5]   View My Rental History                           |\n";
    cout << "|   [6]   Logout                                           |\n";
    cout << Color::BOLD << Color::GREEN << "+----------------------------------------------------------+\n" << Color::RESET;
}

/**
* @brief Displays the customer's past rental transactions.
*/

void Customer::viewRentalHistory()
{
    cout << Color::BOLD << Color::GREEN;
    cout << "\n";
    cout << "+==========================================================+\n";
    cout << "|                 YOUR RENTAL HISTORY                      |\n";
    cout << "+==========================================================+\n"<< Color::RESET;

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
    cout << Color::BOLD << Color::GREEN;
    cout << "+==========================================================+\n"<< Color::RESET ;
}


void Customer::addToHistory(const string& record)
{
    rentalHistory.push_back(record);
}




/**
 * @brief Logic for renting a vehicle.
 */


void Customer::rentVehicle(vector<Vehicle*>& fleet, FileHandler& fh)
{
    string id;
    cout << Color::BOLD << Color::GREEN;
    cout << "\n==========================================================\n                   RENT A VEHICLE \n==========================================================" << Color::RESET << endl ;

    id = InputHandler::getString("Enter Vehicle ID to rent: ", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    for (Vehicle* v : fleet)
    {
        if (v->getID() == id)
        {
            if (!v->getAvailable())
            {
                cout << Color::ERROR << "[ERROR] This vehicle is already rented." << Color::RESET << endl;
                return;
            }

            // Generate Transaction
            RentalTransaction* txn = new RentalTransaction("RTX-" + id, v, this, "14/05/2026", "10:00 AM");
            txn->finalise();

            // Log Transaction immediately
            fh.appendTransaction("RENT_START", v->getID(), this->getID(), 0.0, "14/05/2026");

            addToHistory("Started Rental of " + v->getModel() + " (ID: " + v->getID() + ")");
            cout << Color::SUCCESS;
            cout << "[SUCCESS] You have successfully rented the " << v->getModel() << "!" << Color::RESET << endl;
            delete txn;
            return;
        }
    }
    cout << Color::ERROR << "[ERROR] Vehicle ID not found." << Color::RESET << endl;
}



/**
 * @brief Logic for returning a vehicle.
 */


void Customer::returnVehicle(vector<Vehicle*>& fleet, FileHandler& fh)
{
    string id;

    cout << Color::BOLD << Color::GREEN;
    cout << "\n==========================================================\n                   RETURN A VEHICLE \n==========================================================" << Color::RESET << endl ;

    id = InputHandler::getString("Enter Vehicle ID you are returning: ", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    for (Vehicle* v : fleet)
    {
        if (v->getID() == id)
        {
            if (v->getStatus() != VehicleStatus::Rented)
            {
                cout << Color::ERROR;
                cout << "[ERROR] This vehicle was never rented out." << endl;
                cout << Color::RESET;
                return;
            }

            // 1. Generate Inspection Report
            InspectionReport report(v, this);
            report.fillReport();
            fh.saveInspection(report); // Save to file

            // 2. Finalize Billing
            int days = InputHandler::getInt("Enter total days used: ", 1, 365, true);
            if (days == InputHandler::CANCEL_INT) return;

            float baseBill = v->calculateCost(days);
            float discountPerc = v->getDiscountPercentage(days);
            float discountAmt = baseBill * discountPerc;
            float discountedBill = baseBill - discountAmt;

            float damageFee = report.getDamageFee();
            float totalBill = discountedBill + damageFee;

            v->setStatus(VehicleStatus::Available); // Return to garage

            // Log Transaction immediately
            fh.appendTransaction("RENT_RETURN", v->getID(), this->getID(), totalBill, "14/05/2026");

            cout << Color::BOLD << Color::GREEN;
            cout << "\n";
            cout << "+======================================================+\n";
            cout << "|                  FINAL RENTAL RECEIPT                |\n";
            cout << "+======================================================+\n"<< Color::RESET;
            cout << "| Vehicle          :  " << left << setw(33) << v->getModel() << "|\n";
            cout << "| Duration         :  " << left << setw(28) << days << " days |" << "\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| Base Rental Cost :  $" << left << setw(32) << fixed << setprecision(2) << baseBill << "|\n";
            if (discountAmt > 0) {
                cout << "| Promo Discount   : -$" << left << setw(31) << discountAmt << " (" << (int)(discountPerc * 100) << "%)" << "|\n";
            }
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
    cout << Color::ERROR;
    cout << "[ERROR] You do not have a vehicle with that ID." << Color::RESET << endl;
}
