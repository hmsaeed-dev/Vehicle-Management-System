#include "InspectionReport.h"
#include "Vehicle.h"
#include "Customer.h"
#include "InputHandler.h"
#include "Colors.h"
#include "Validator.h"
#include "Constants.h"

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Constructor linking a vehicle and customer to a report.
 */

InspectionReport::InspectionReport(Vehicle* v, User* u)
    : inspectedVehicle(v), inspector(u), mileage(0.0f) {}

/**
 * @brief Interactively fills the inspection report via console.
 */
void InspectionReport::fillReport()
{
    cout << "\n" << Color::SUBHEADER << "================== INSPECTION REPORT FORM ===================" << Color::RESET << endl;
    cout << "  > Vehicle ID: " << (inspectedVehicle ? inspectedVehicle->getID() : "Unknown") << endl;

    while (true) {
        date = InputHandler::getString("  > Enter Return Date (DD-MM-YYYY)");
        if (Validator::isValidDate(date)) break;
        cout << Color::ERR << "[ERROR] Please enter date in DD-MM-YYYY format." << Color::RESET << endl;
    }

    fuelLevel = InputHandler::getString("  > Enter Fuel Level (e.g., Full, Half, 10%)");
    mileage = InputHandler::getFloat("  > Enter Current Mileage", 0.0f, 1000000.0f);
    damageNotes = InputHandler::getString("  > Enter Damage Notes (type 'None' if clear)");

    while (true) {
        condition = InputHandler::getString("  > Enter Vehicle Condition (Good / Fair / Poor)");
        // Normalize condition for easier checking
        if (condition == "Good" || condition == "Fair" || condition == "Poor") break;
        cout << Color::ERR << "[ERROR] Invalid condition. Use: Good, Fair, or Poor." << Color::RESET << endl;
    }

    evaluationRemarks = InputHandler::getString("  > Enter Additional Evaluator Remarks");
}


float InspectionReport::getDamageFee() const
{
    if (!inspectedVehicle) return 0.0f;

    float baseRate = inspectedVehicle->getRentalRate();

    // Dynamic fee based on daily rate and constants
    if (condition == "Poor") return baseRate * Pricing::DAMAGE_FEE_POOR;
    if (condition == "Fair") return baseRate * Pricing::DAMAGE_FEE_FAIR;
    return 0.0f;
}



/**
 * @brief Displays the report details to the console.
 */

void InspectionReport::displayReport() const
{
    cout << "\n";
    cout << Color::SUBHEADER << "+----------------------------------------------------------+\n";
    cout << "|                 VEHICLE INSPECTION REPORT                |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "| " << left << setw(20) << "Return Date" << ": " << setw(35) << date << "|\n";
    cout << "| " << left << setw(20) << "Vehicle Model" << ": " << setw(35) << (inspectedVehicle ? inspectedVehicle->getModel() : "N/A") << "|\n";
    cout << "| " << left << setw(20) << "Customer/Inspector" << ": " << setw(35) << (inspector ? inspector->getName() : "N/A") << "|\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| " << left << setw(20) << "Fuel Level" << ": " << setw(35) << fuelLevel << "|\n";
    cout << "| " << left << setw(20) << "Mileage" << ": " << setw(32) << (int)mileage << " km" << " |\n";
    cout << "| " << left << setw(20) << "Vehicle Condition" << ": " << setw(35) << condition << "|\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| " << left << setw(20) << "Damage Notes" << ": " << setw(35) << damageNotes << "|\n";
    cout << "| " << left << setw(20) << "Eval. Remarks" << ": " << setw(35) << evaluationRemarks << "|\n";
    cout << Color::SUBHEADER << "+----------------------------------------------------------+\n" << Color::RESET << "\n";
}


/**
 * @brief Saves the report data to an output file stream.
 */
void InspectionReport::saveToFile(ofstream& out) const
{
    if (out.is_open())
    {
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
