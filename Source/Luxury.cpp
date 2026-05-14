#include "Luxury.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

Luxury::Luxury(string id, string model, int year, int capacity, float rate, string features)
    : Vehicle(id, model, year, capacity, rate), luxuryFeatures(features) {}

string Luxury::getLuxuryFeatures() const {
    return luxuryFeatures;
}

/**
 * @brief Premium billing for luxury cars.
 */
float Luxury::calculateCost(int days) {
    return (getRentalRate() * Pricing::LUXURY_MULTIPLIER) * days;
}

/**
 * @brief Displays luxury-specific info including premium features.
 */


// void Luxury::displayInfo()
// {
//     cout << "[LUXURY]  ID: " << getID()
//          << " | Model: " << getModel()
//          << " | Year: " << getYear()
//          << " | Capacity: " << getCapacity()
//          << " | Rate: $" << getRentalRate() << "/hr (+50% Prem.)"
//          << " | Features: " << luxuryFeatures
//          << " | Status: " << (getAvailable() ? "Available" : "Rented")
//          << endl;
// }


void Luxury::displayInfo()
{
    cout << "\n";
    cout << Color::BOLD << Color::MAGENTA;
    cout << "+======================================================+\n";
    cout << "| [PREMIUM LUXURY CLASS]                               |\n";
    cout << "+======================================================+\n" << Color::RESET;
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Capacity      :  " << left << setw(28) << getCapacity() << " Person(s) |" << "\n";
    cout << "| Daily Rate    :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Features      :  " << left << setw(36) << luxuryFeatures << "|\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? Color::GREEN + "AVAILABLE" + Color::RESET : Color::RED + "RENTED" + Color::RESET) << "|\n";
    cout << "+======================================================+\n";
}

void Luxury::displayRow() const
{
    string coloredStatus = getAvailable() ? Color::GREEN + "Available " + Color::RESET : Color::RED + "Rented    " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| $" << left << setw(7) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << coloredStatus
         << " | " << left << Color::MAGENTA << setw(10) << "Luxury" << Color::RESET << " |" << endl;
}
