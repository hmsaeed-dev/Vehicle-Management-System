#include "SUV.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

SUV::SUV(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

string SUV::getCategory() const {
    return "SUV";
}

/**
 * @brief Mid-range billing for SUVs.
 */
float SUV::calculateCost(int days)
{
    float baseTotal = (getRentalRate() * Pricing::SUV_MULTIPLIER) * days;
    float discount = 0.0f;

    if (days >= Pricing::TIER_2_DAYS) {
        discount = Pricing::TIER_2_DISCOUNT;
    } else if (days >= Pricing::TIER_1_DAYS) {
        discount = Pricing::TIER_1_DISCOUNT;
    }

    return baseTotal * (1.0f - discount);
}

/**
 * @brief Displays SUV-specific info including seating capacity.
 */

void SUV::displayInfo()
{
    string statusStr;
    if (getStatus() == VehicleStatus::Available) statusStr = Color::GREEN + "AVAILABLE" + Color::RESET;
    else if (getStatus() == VehicleStatus::Rented) statusStr = Color::RED + "RENTED" + Color::RESET;
    else statusStr = Color::YELLOW + "SOLD" + Color::RESET;

    cout << "\n";
    cout << Color::BOLD << Color::YELLOW;
    cout << "+------------------------------------------------------+\n";
    cout << "| [SUV CATEGORY]                                       |\n";
    cout << "+------------------------------------------------------+\n" << Color::RESET;
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Seating       :  " << left << setw(29) << getCapacity() << " Seats |" << "\n";
    cout << "| Daily Rate    :  " << left << Pricing::CURRENCY << setw(35-Pricing::CURRENCY.length()) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [PROMO] " << Pricing::TIER_1_DAYS << "-" << (Pricing::TIER_2_DAYS-1) << " Days: " << (int)(Pricing::TIER_1_DISCOUNT*100) << "% OFF | " << Pricing::TIER_2_DAYS << "+ Days: " << (int)(Pricing::TIER_2_DISCOUNT*100) << "% OFF |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(45) << statusStr << "|\n";
    cout << "+------------------------------------------------------+\n";
}

void SUV::displayRow() const
{
    string statusStr;
    if (getStatus() == VehicleStatus::Available) statusStr = Color::GREEN + "Available " + Color::RESET;
    else if (getStatus() == VehicleStatus::Rented) statusStr = Color::RED + "Rented    " + Color::RESET;
    else statusStr = Color::YELLOW + "Sold      " + Color::RESET;

    string category = Color::YELLOW + "SUV       " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << statusStr
         << "| " << left << category
         << " |" << endl;
}

