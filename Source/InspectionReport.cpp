#include "InspectionReport.h"
#include "Vehicle.h"
#include "Customer.h"

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Constructor linking a vehicle and customer to a report.
 */

InspectionReport::InspectionReport(Vehicle* v, Customer* c)
    : inspectedVehicle(v), inspector(c), mileage(0.0f) {}

/**
 * @brief Interactively fills the inspection report via console.
 */
void InspectionReport::fillReport() {
    cout << "\n--- FILLING INSPECTION REPORT ---" << endl;
    cout << "Vehicle ID: " << (inspectedVehicle ? inspectedVehicle->getID() : "Unknown") << endl;

    cout << "Enter Return Date (DD/MM/YYYY): ";
    cin.ignore();
    getline(cin, date);

    cout << "Enter Fuel Level (e.g., Full, Half, 10%): ";
    getline(cin, fuelLevel);

    cout << "Enter Current Mileage: ";
    cin >> mileage;

    cout << "Enter Damage Notes (type 'None' if clear): ";
    getline(cin, damageNotes);

    cout << "Enter Vehicle Condition (Good / Fair / Poor): ";
    getline(cin, condition);

    cout << "Enter Additional Evaluator Remarks: ";
    getline(cin, evaluationRemarks);

    cout << "[SYSTEM] Inspection report completed successfully." << endl;
}

float InspectionReport::getDamageFee() const
{
    if (condition == "Poor") return 100.0f;
    if (condition == "Fair") return 50.0f;
    return 0.0f;
}

/**
 * @brief Displays the report details to the console.
 */

void InspectionReport::displayReport() const
{
    cout << "\n";
    cout << "+==========================================================+\n";
    cout << "|                 VEHICLE INSPECTION REPORT                |\n";
    cout << "+==========================================================+\n";
    cout << "| Date           :  " << left << setw(39) << date << "|\n";
    cout << "| Vehicle        :  " << left << setw(39) << (inspectedVehicle ? inspectedVehicle->getModel() : "N/A") << "|\n";
    cout << "| Customer       :  " << left << setw(39) << (inspector ? inspector->getName() : "N/A") << "|\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| Fuel Level     :  " << left << setw(39) << fuelLevel << "|\n";
    cout << "| Condition      :  " << left << setw(39) << condition << "|\n";
    cout << "| Mileage        :  " << left << setw(36) << mileage << " km |" << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| Damage Notes   :  " << left << setw(39) << damageNotes << "|\n";
    cout << "| Remarks        :  " << left << setw(39) << evaluationRemarks << "|\n";
    cout << "+==========================================================+\n\n";
}


/**
 * @brief Saves the report data to an output file stream.
 */
void InspectionReport::saveToFile(ofstream& out) const
{
    if (out.is_open()) {
        out << (inspectedVehicle ? inspectedVehicle->getID() : "N/A") << "|"
            << (inspector ? inspector->getID() : "N/A") << "|"
            << date << "|"
            << fuelLevel << "|"
            << damageNotes << "|"
            << mileage << "|"
            << condition << "|"
            << evaluationRemarks << endl;
    }
}
