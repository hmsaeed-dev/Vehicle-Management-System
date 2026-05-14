#include "Economy.h"
#include <iostream>
#include <iomanip>

using namespace std;

Economy::Economy(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

/**
 * @brief Simple billing for economy cars.
 * No extra multipliers applied.
 */

float Economy::calculateCost(int hours)
{
    return getRentalRate() * hours;
}

/**
 * @brief Displays economy-specific info.
 */

void Economy::displayInfo()
{
    cout << "\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [ECONOMY CLASS]                                      |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Capacity      :  " << left << setw(28) << getCapacity() << " Person(s) |" << "\n";
    cout << "| Hourly Rate   :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? "AVAILABLE" : "RENTED") << "|\n";
    cout << "+------------------------------------------------------+\n";
}
