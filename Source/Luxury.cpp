#include "Luxury.h"

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
 * Applies a 1.5x multiplier due to high maintenance.
 */
float Luxury::calculateCost(int hours) {
    return (getRentalRate() * 1.5f) * hours;
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
    cout << "+======================================================+\n";
    cout << "| [PREMIUM LUXURY CLASS]                               |\n";
    cout << "+======================================================+\n";
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Capacity      :  " << left << setw(28) << getCapacity() << " Person(s) |" << "\n";
    cout << "| Hourly Rate   :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Features      :  " << left << setw(36) << luxuryFeatures << "|\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? "AVAILABLE" : "RENTED") << "|\n";
    cout << "+======================================================+\n";
}
