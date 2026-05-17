#include "Economy.h"
#include "Colors.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>


using namespace std;

Economy::Economy(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

string Economy::getCategory() const {
    return "Economy";
}

/**
 * @brief Simple billing for economy cars.
 * No extra multipliers applied.
 */

float Economy::calculateCost(int days)
{
    float baseTotal = (getRentalRate() * Pricing::ECONOMY_MULTIPLIER) * days;
    float discount = 0.0f;

    if (days >= Pricing::TIER_2_DAYS) {
        discount = Pricing::TIER_2_DISCOUNT;
    } else if (days >= Pricing::TIER_1_DAYS) {
        discount = Pricing::TIER_1_DISCOUNT;
    }

    return baseTotal * (1.0f - discount);
}


/**
 * @brief Displays economy-specific info.
 */

void Economy::displayInfo()
{
    string statusStr;
    if (getStatus() == VehicleStatus::Available) statusStr = Color::STATUS_AVAILABLE + "AVAILABLE" + Color::RESET;
    else if (getStatus() == VehicleStatus::Rented) statusStr = Color::STATUS_RENTED + "RENTED" + Color::RESET;
    else statusStr = Color::STATUS_SOLD + "SOLD" + Color::RESET;

    cout << "\n";
    cout << Color::SUBHEADER;
    cout << "+------------------------------------------------------+\n";
    cout << "| [ECONOMY CLASS]                                      |\n";
    cout << "+------------------------------------------------------+\n" << Color::RESET;
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Capacity      :  " << left << setw(28) << getCapacity() << " Person(s) |" << "\n";
    cout << "| Daily Rate    :  " << left << Pricing::CURRENCY << setw(35-Pricing::CURRENCY.length()) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [PROMO] " << Pricing::TIER_1_DAYS << "-" << (Pricing::TIER_2_DAYS-1) << " Days: " << (int)(Pricing::TIER_1_DISCOUNT*100) << "% OFF | " << Pricing::TIER_2_DAYS << "+ Days: " << (int)(Pricing::TIER_2_DISCOUNT*100) << "% OFF |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(45) << statusStr << "|\n";
    cout << "+------------------------------------------------------+\n";
}

void Economy::displayRow() const
{
    string statusStr;
    if (getStatus() == VehicleStatus::Available) statusStr = Color::STATUS_AVAILABLE + "Available " + Color::RESET;
    else if (getStatus() == VehicleStatus::Rented) statusStr = Color::STATUS_RENTED + "Rented    " + Color::RESET;
    else statusStr = Color::STATUS_SOLD + "Sold      " + Color::RESET;

    string category = Color::CATEGORY_ECONOMY + "Economy   " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << statusStr
         << "| " << left << category
         << " |" << endl;
}

void Economy::displayRowSimple() const
{
    string category = Color::CATEGORY_ECONOMY + "Economy   " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << category
         << " |" << endl;
}


