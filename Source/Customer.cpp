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
    cout << "|                                                          |\n";
    cout << "|                   CUSTOMER DASHBOARD                     |\n";
    cout << "|                                                          |\n";
    cout << "+==========================================================+\n" << Color::RESET;
    cout << "| Welcome, " << Color::CYAN << left << setw(48) << getName() << Color::RESET << "|\n";
    cout << Color::BOLD << Color::GREEN << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "|                                                          |\n";
    cout << "|   [1]   Search for a Vehicle                             |\n";
    cout << "|   [2]   Rent a Vehicle                                   |\n";
    cout << "|   [3]   Return a Vehicle                                 |\n";
    cout << "|   [4]   Plan a Trip                                      |\n";
    cout << "|   [5]   View My Rental History                           |\n";
    cout << "|   [Z]   Logout                                           |\n";
    cout << "|                                                          |\n";
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




#include "Validator.h"
#include "Constants.h"

/**
 * @brief Logic for renting a vehicle.
 */


void Customer::rentVehicle(vector<Vehicle*>& fleet, FileHandler& fh)
{
    cout << Color::BOLD << Color::GREEN;
    cout << "\n==========================================================\n                   RENT A VEHICLE \n==========================================================" << Color::RESET << endl ;

    // Show available vehicles first
    cout << "\n" << Color::INFO << "Currently Available Vehicles:" << Color::RESET << "\n";
    cout << "+-------+-------------------+-------+-------+------------+------------+------------+\n";
    cout << "| ID    | Model             | Year  | Cap.  | Rate       | Status     | Category   |\n";
    cout << "+-------+-------------------+-------+-------+------------+------------+------------+\n";
    bool anyAvailable = false;
    for (Vehicle* v : fleet) {
        if (v->getStatus() == VehicleStatus::Available) {
            v->displayRow();
            anyAvailable = true;
        }
    }
    cout << "+-------+-------------------+-------+-------+------------+------------+------------+\n";

    if (!anyAvailable) {
        cout << Color::WARNING << "[SYSTEM] No vehicles are currently available for rent." << Color::RESET << endl;
        return;
    }

    string id = InputHandler::getString("Enter Vehicle ID to rent", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    processRental(id, fleet, fh);
}

bool Customer::processRental(string id, vector<Vehicle*>& fleet, FileHandler& fh)
{
    for (Vehicle* v : fleet)
    {
        if (v->getID() == id)
        {
            if (v->getStatus() == VehicleStatus::Sold)
            {
                cout << Color::ERR << "[ERROR] This vehicle has been SOLD and cannot be rented." << Color::RESET << endl;
                return false;
            }
            if (v->getStatus() == VehicleStatus::Rented)
            {
                cout << Color::ERR << "[ERROR] This vehicle is already rented." << Color::RESET << endl;
                return false;
            }

            string date;
            while(true) {
                date = InputHandler::getString("Enter Rental Date (DD-MM-YYYY)");
                if (Validator::isValidDate(date)) break;
                cout << Color::ERR << "[ERROR] Invalid date format." << Color::RESET << endl;
            }

            // Generate Transaction
            RentalTransaction* txn = new RentalTransaction("RTX-" + id, v, this, date, "10:00 AM");
            txn->finalise();

            // Log Transaction immediately
            fh.appendTransaction("RENT_START", v->getID(), this->getID(), 0.0, date);

            addToHistory("Started Rental of " + v->getModel() + " (ID: " + v->getID() + ") on " + date);
            cout << Color::SUCCESS;
            cout << "[SUCCESS] You have successfully rented the " << v->getModel() << "!" << Color::RESET << endl;
            delete txn;
            return true;
        }
    }
    cout << Color::ERR << "[ERROR] Vehicle ID not found." << Color::RESET << endl;
    return false;
}



/**
 * @brief Logic for returning a vehicle.
 */


void Customer::returnVehicle(vector<Vehicle*>& fleet, FileHandler& fh)
{
    string id;

    cout << Color::BOLD << Color::GREEN;
    cout << "\n==========================================================\n                   RETURN A VEHICLE \n==========================================================" << Color::RESET << endl ;

    id = InputHandler::getString("Enter Vehicle ID you are returning", false, true);
    if (id == InputHandler::CANCEL_STR) return;

    for (Vehicle* v : fleet)
    {
        if (v->getID() == id)
        {
            if (v->getStatus() != VehicleStatus::Rented)
            {
                cout << Color::ERR << "[ERROR] This vehicle is not currently rented." << Color::RESET << endl;
                return;
            }

            // 1. Generate Inspection Report
            InspectionReport report(v, this);
            report.fillReport();
            fh.saveInspection(report); 

            // 2. Finalize Billing
            int days = InputHandler::getInt("Enter total days used", 1, 365, true);
            if (days == InputHandler::CANCEL_INT) return;

            float baseBill = v->calculateCost(days);
            float discountPerc = v->getDiscountPercentage(days);
            float discountAmt = baseBill * discountPerc;
            float discountedBill = baseBill - discountAmt;

            float damageFee = report.getDamageFee();
            float totalBill = discountedBill + damageFee;

            cout << "\n" << Color::WARNING << "[CONFIRM] Final Total Bill will be " << Pricing::CURRENCY << fixed << setprecision(2) << totalBill << ". Finalize return? (Y/N): " << Color::RESET;
            if (InputHandler::getChar("", "YN") == 'N') {
                cout << Color::INFO << "[SYSTEM] Return process suspended." << Color::RESET << endl;
                return;
            }

            v->setStatus(VehicleStatus::Available); 

            // Log Transaction immediately
            fh.appendTransaction("RENT_RETURN", v->getID(), this->getID(), totalBill, report.getDate());

            cout << Color::BOLD << Color::GREEN;
            cout << "\n";
            cout << "+======================================================+\n";
            cout << "|                  FINAL RENTAL RECEIPT                |\n";
            cout << "+======================================================+\n"<< Color::RESET;
            cout << "| Vehicle          :  " << left << setw(33) << v->getModel() << "|\n";
            cout << "| Duration         :  " << left << setw(28) << days << " days |" << "\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| Base Rental Cost :  " << Pricing::CURRENCY << left << setw(32-Pricing::CURRENCY.length()) << fixed << setprecision(2) << baseBill << "|\n";
            if (discountAmt > 0) {
                cout << "| Promo Discount   : -" << Pricing::CURRENCY << left << setw(31-Pricing::CURRENCY.length()) << discountAmt << " (" << (int)(discountPerc * 100) << "%)" << "|\n";
            }
            cout << "| Damage Fees      :  " << Pricing::CURRENCY << left << setw(32-Pricing::CURRENCY.length()) << damageFee << "|\n";
            cout << "+------------------------------------------------------+\n";
            cout << "| TOTAL AMOUNT     :  " << Pricing::CURRENCY << left << setw(32-Pricing::CURRENCY.length()) << totalBill << "|\n";
            cout << "+======================================================+\n";
            cout << "|           [SUCCESS] Vehicle Returned                 |\n";
            cout << "+======================================================+\n\n";

            addToHistory("Returned " + v->getModel() + " (Final Bill: " + Pricing::CURRENCY + to_string((int)totalBill) + ") on " + report.getDate());
            return;
        }
    }
    cout << Color::ERR;
    cout << "[ERROR] Vehicle ID not found in system." << Color::RESET << endl;
}

