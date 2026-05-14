#include "SUV.h"

#include <iostream>
#include <iomanip>

using namespace std;

SUV::SUV(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

/**
 * @brief Mid-range billing for SUVs.
 * Applies a 1.2x multiplier for extra space/capacity.
 */
float SUV::calculateCost(int hours)
{
    return (getRentalRate() * 1.2f) * hours;
}

/**
 * @brief Displays SUV-specific info including seating capacity.
 */

void SUV::displayInfo()
{
    cout << "\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [SUV CATEGORY]                                       |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Seating       :  " << left << setw(29) << getCapacity() << " Seats |" << "\n";
    cout << "| Hourly Rate   :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? "AVAILABLE" : "RENTED") << "|\n";
    cout << "+------------------------------------------------------+\n";
}
