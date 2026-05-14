#include "SUV.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

SUV::SUV(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

/**
 * @brief Mid-range billing for SUVs.
 */
float SUV::calculateCost(int days)
{
    return (getRentalRate() * Pricing::SUV_MULTIPLIER) * days;
}

/**
 * @brief Displays SUV-specific info including seating capacity.
 */

void SUV::displayInfo()
{
    cout << "\n";
    cout << Color::BOLD << Color::YELLOW;
    cout << "+------------------------------------------------------+\n";
    cout << "| [SUV CATEGORY]                                       |\n";
    cout << "+------------------------------------------------------+\n" << Color::RESET;
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Seating       :  " << left << setw(29) << getCapacity() << " Seats |" << "\n";
    cout << "| Daily Rate    :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [PROMO] 4-7 Days: 10% OFF | 8+ Days: 20% OFF         |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? Color::GREEN + "AVAILABLE" + Color::RESET : Color::RED + "RENTED" + Color::RESET) << "|\n";
    cout << "+------------------------------------------------------+\n";
}

void SUV::displayRow() const
{
    string coloredStatus = getAvailable() ? Color::GREEN + "Available " + Color::RESET : Color::RED + "Rented    " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| $" << left << setw(7) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << coloredStatus
         << " | " << left << Color::YELLOW << setw(10) << "SUV" << Color::RESET << " |" << endl;
}
