#include "Customer.h"
#include "RentalTransaction.h"
#include "InspectionReport.h"
#include "FileHandler.h"
#include "Colors.h"
#include "InputHandler.h"
#include "Validator.h"
#include "Constants.h"

#include <iostream>
#include <iomanip>

using namespace std;

Customer::Customer(string id, string username, string name, string cnic, string password)
    : User(id, username, name, cnic, password) {}


void Customer::showMenu()
{
    cout << "\n";
    cout << Color::HEADER;
    cout << "+======================================================================+\n";
    cout << "|                                                                      |\n";
    cout << "|                         CUSTOMER DASHBOARD                           |\n";
    cout << "|                                                                      |\n";
    cout << "+======================================================================+\n" << Color::RESET;
    cout << "| Welcome, " << Color::HIGHLIGHT << left << setw(60) << getName() << Color::RESET << "|\n";
    cout << Color::HEADER << "+----------------------------------------------------------------------+\n" << Color::RESET;
    cout << "|                                                                      |\n";
    cout << "|   [1]   Search for a Vehicle                                         |\n";
    cout << "|   [2]   Rent a Vehicle                                               |\n";
    cout << "|   [3]   Return a Vehicle                                             |\n";
    cout << "|   [4]   Plan a Trip                                                  |\n";
    cout << "|   [5]   View My Rental History                                       |\n";
    cout << "|   [Z]   Logout                                                       |\n";
    cout << "|                                                          |\n";
    cout << Color::HEADER << "+----------------------------------------------------------------------+\n" << Color::RESET;
}


void Customer::viewRentalHistory()
{
    cout << "\n" << Color::SUBHEADER << "================== YOUR RENTAL ACTIVITY HISTORY ==================" << Color::RESET << "\n";

    if (rentalHistory.empty())
    {
        cout << Color::INFO << "  No previous records found." << Color::RESET << endl;
    }
    else
    {
        cout << "+----------------------------------------------------------------------+\n";
        cout << "| " << left << setw(68) << "Activity Record" << " |\n";
        cout << "+----------------------------------------------------------------------+\n";
        for (const string& record : rentalHistory)
        {
            string coloredRecord = record;
            if (record.find("Purchased") != string::npos) coloredRecord = Color::TABLE_HEADER + record + Color::RESET;
            else if (record.find("Started") != string::npos) coloredRecord = Color::WARNING + record + Color::RESET;
            else if (record.find("Returned") != string::npos) coloredRecord = Color::SUCCESS + record + Color::RESET;

            // Manual padding for colored strings is tricky, so we keep it simple
            cout << "| - " << left << coloredRecord << string(max(0, (int)(66 - record.length())), ' ') << " |\n";
        }
        cout << "+----------------------------------------------------------------------+\n";
    }
}

void Customer::addToHistory(const string& record)
{
    rentalHistory.push_back(record);
}


void Customer::rentVehicle(vector<Vehicle*>& fleet, FileHandler& fh)
{
    cout << Color::HEADER;
    cout << "\n==========================================================\n                   RENT A VEHICLE \n==========================================================" << Color::RESET << endl ;

    // Show available vehicles first
    cout << "\n" << Color::INFO << "Currently Available Vehicles:" << Color::RESET << "\n";
    cout << "+-------+-------------------+-------+------------+------------+\n";
    cout << "| ID    | Model             | Cap.  | Rate       | Category   |\n";
    cout << "+-------+-------------------+-------+------------+------------+\n";
    bool anyAvailable = false;
    for (Vehicle* v : fleet) {
        if (v->getStatus() == VehicleStatus::Available) {
            v->displayRowSimple();
            anyAvailable = true;
        }
    }
    cout << "+-------+-------------------+-------+------------+------------+\n";

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
                date = InputHandler::getString("Enter Rental Start Date (DD-MM-YYYY)", false, true);
                if (date == InputHandler::CANCEL_STR) return false;
                if (Validator::isValidDate(date)) break;
                cout << Color::ERR << "[ERROR] Invalid date format." << Color::RESET << endl;
            }

            // --- PRE-RENTAL COST ESTIMATION ---
            int plannedDays = InputHandler::getInt("How many days do you plan to rent this vehicle?", 1, 365, true);
            if (plannedDays == InputHandler::CANCEL_INT) return false;

            float estBase = v->calculateCost(plannedDays);
            float estTotal = v->calculateDiscountedCost(plannedDays);
            float estDiscount = estBase - estTotal;
            float discPerc = v->getDiscountPercentage(plannedDays);

            cout << "\n";
            cout << Color::SUBHEADER << "+====================================================================+\n";
            cout << "|                       ESTIMATED RENTAL QUOTE                       |\n";
            cout << "+====================================================================+\n" << Color::RESET;
            string rateVal = Pricing::CURRENCY + to_string((int)v->getRentalRate());
            string totalVal = Pricing::CURRENCY + to_string((int)estTotal);
            string discountVal = "-" + Pricing::CURRENCY + to_string((int)estDiscount) + " (" + to_string((int)(discPerc * 100)) + "%)";

            cout << "| Vehicle          :  " << left << setw(47) << v->getModel() << "|\n";
            cout << "| Daily Rate       :  " << left << setw(47) << rateVal << "|\n";
            cout << "| Planned Duration :  " << left << setw(47) << plannedDays << "|\n";
            cout << "+--------------------------------------------------------------------+\n";
            cout << "| ESTIMATED TOTAL  :  " << left << setw(47) << totalVal << "|\n";
            
            if (estDiscount > 0) {
                cout << Color::SUCCESS << "| Incl. Discount   :  " << left << setw(47) << discountVal << Color::RESET << "|\n";
            }
            
            cout << Color::SUBHEADER << "+====================================================================+\n" << Color::RESET;
            cout << Color::WARNING << "[CONFIRM] Proceed with this rental? (Y/N): " << Color::RESET;
            if (InputHandler::getChar("", "YN") == 'N') {
                cout << Color::INFO << "[SYSTEM] Rental request cancelled." << Color::RESET << endl;
                return false;
            }

            // Generate Transaction
            RentalTransaction* txn = new RentalTransaction(id, v, this, date, "10:00 AM");
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


void Customer::returnVehicle(vector<Vehicle*>& fleet, FileHandler& fh)
{
    string id;

    cout << Color::HEADER;
    cout << "\n==========================================================\n                   RETURN A VEHICLE \n==========================================================" << Color::RESET << endl ;

    id = InputHandler::getString("> Enter Vehicle ID : ", false, true);
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

            // 2. Automated Billing Duration
            string startDate = fh.getRentalStartDate(v->getID(), this->getID());
            string endDate = Validator::getCurrentDate();
            int days = 1; // Default to 1

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
            float discountAmt = baseBill - discountedBill;
            float discountPerc = v->getDiscountPercentage(days);

            float damageFee = report.getDamageFee();
            float totalBill = discountedBill + damageFee;

            cout << "\n" << Color::NOTICE << "[!] PENDING CHARGES: " << Pricing::CURRENCY << (int)totalBill << Color::RESET << "\n";
            cout << Color::WARNING << "[CONFIRM] Finalize return and process payment? (Y/N/Z:Back): " << Color::RESET;
            char confirm = InputHandler::getChar("", "YN", true);
            if (confirm == 'N' || confirm == 'Z') {
                cout << Color::INFO << "[SYSTEM] Return process suspended." << Color::RESET << endl;
                return;
            }

            v->setStatus(VehicleStatus::Available);
            fh.saveInspection(report);

            // Log Transaction
            fh.appendTransaction("RENT_RETURN", v->getID(), this->getID(), totalBill, report.getDate());

            cout << "\n";
            cout << Color::SUBHEADER << "+====================================================================+\n";
            cout << "|                          RENTAL RECEIPT                            |\n";
            cout << "+====================================================================+\n" << Color::RESET;
            string rateVal = Pricing::CURRENCY + to_string((int)v->getRentalRate());
            string baseVal = Pricing::CURRENCY + to_string((int)baseBill);
            string calcVal = "(" + to_string((int)v->getRentalRate()) + " x " + to_string(days) + " days)";
            string discountVal = (discountAmt > 0) ? ("-" + Pricing::CURRENCY + to_string((int)discountAmt) + " (" + to_string((int)(discountPerc * 100)) + "%)") : "None Applied";
            string feeVal = (damageFee > 0) ? (Pricing::CURRENCY + to_string((int)damageFee)) : "None";
            string totalVal = Pricing::CURRENCY + to_string((int)totalBill);

            cout << "| Vehicle          :  " << left << setw(47) << v->getModel() << "|\n";
            cout << "| Daily Rental Rate:  " << left << setw(47) << rateVal << "|\n";
            cout << "| Total Days Rented:  " << left << setw(47) << days << "|\n";
            cout << "+--------------------------------------------------------------------+\n";
            cout << "| BASE RENTAL COST :  " << left << setw(47) << baseVal << "|\n";
            cout << "| Calculation      :  " << left << setw(47) << calcVal << "|\n";

            if (discountAmt > 0) {
                cout << Color::WARNING << "| Promo Discount   :  " << left << setw(47) << discountVal << Color::RESET << "|\n";
            } else {
                cout << "| Promo Discount   :  " << left << setw(47) << discountVal << "|\n";
            }

            if (damageFee > 0) {
                cout << Color::ERR << "| Damage Fees      :  " << left << setw(47) << feeVal << Color::RESET << "|\n";
            } else {
                cout << Color::SUCCESS << "| Damage Fees      :  " << left << setw(47) << feeVal << Color::RESET << "|\n";
            }

            cout << "+--------------------------------------------------------------------+\n";
            cout << Color::TABLE_HEADER << "| TOTAL AMOUNT     :  " << left << setw(47) << totalVal << Color::RESET << "|\n";
            cout << Color::SUBHEADER << "+====================================================================+\n";
            cout << "|                [SUCCESS] Transaction Finalized                     |\n";
            cout << "+====================================================================+\n\n" << Color::RESET;

            addToHistory("Returned " + v->getModel() + " (Final Bill: " + Pricing::CURRENCY + to_string((int)totalBill) + ") on " + report.getDate());
            cout << Color::SUCCESS << "[SYSTEM] Vehicle returned to fleet successfully." << Color::RESET << endl;
            return;
        }
    }
    cout << Color::ERR << "[ERROR] Vehicle ID not found in system." << Color::RESET << endl;
}
