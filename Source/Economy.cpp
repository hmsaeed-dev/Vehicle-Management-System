#include "Economy.h"
#include "Colors.h"
#include <iostream>
#include <iomanip>

using namespace std;

Economy::Economy(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

/**
 * @brief Simple billing for economy cars.
 * No extra multipliers applied.
 */

float Economy::calculateCost(int days)
{
    return getRentalRate() * days;
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
    cout << "| Daily Rate    :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [PROMO] 4-7 Days: 10% OFF | 8+ Days: 20% OFF         |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? Color::GREEN + "AVAILABLE" + Color::RESET : Color::RED + "RENTED" + Color::RESET) << "|\n";
    cout << "+------------------------------------------------------+\n";
}

void Economy::displayRow() const
{
    string coloredStatus = getAvailable() ? Color::GREEN + "Available " + Color::RESET : Color::RED + "Rented    " + Color::RESET;
    
    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| $" << left << setw(7) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << coloredStatus
         << " | " << left << setw(10) << "Economy" << " |" << endl;
}
