#include "Luxury.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

Luxury::Luxury(string id, string model, int year, int capacity, float rate, string features)
    : Vehicle(id, model, year, capacity, rate), luxuryFeatures(features) {}

string Luxury::getCategory() const {
    return "Luxury";
}

string Luxury::getLuxuryFeatures() const {
    return luxuryFeatures;
}

/**
 * @brief Premium billing for luxury cars.
 */
float Luxury::calculateCost(int days) {
    float baseTotal = (getRentalRate() * Pricing::LUXURY_MULTIPLIER) * days;
    float discount = 0.0f;

    if (days >= Pricing::TIER_2_DAYS) {
        discount = Pricing::TIER_2_DISCOUNT;
    } else if (days >= Pricing::TIER_1_DAYS) {
        discount = Pricing::TIER_1_DISCOUNT;
    }

    return baseTotal * (1.0f - discount);
}

/**
 * @brief Displays luxury-specific info including premium features.
 */

void Luxury::displayInfo()
{
    string statusStr;
    if (getStatus() == VehicleStatus::Available) statusStr = Color::STATUS_AVAILABLE + "AVAILABLE" + Color::RESET;
    else if (getStatus() == VehicleStatus::Rented) statusStr = Color::STATUS_RENTED + "RENTED" + Color::RESET;
    else statusStr = Color::STATUS_SOLD + "SOLD" + Color::RESET;

    cout << "\n";
    cout << Color::SUBHEADER;
    cout << "+======================================================+\n";
    cout << "| [PREMIUM LUXURY CLASS]                               |\n";
    cout << "+======================================================+\n" << Color::RESET;
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Capacity      :  " << left << setw(28) << getCapacity() << " Person(s) |" << "\n";
    cout << "| Daily Rate    :  " << left << Pricing::CURRENCY << setw(35-Pricing::CURRENCY.length()) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Features      :  " << left << setw(36) << luxuryFeatures << "|\n";
    cout << "| Status        :  " << left << setw(45) << statusStr << "|\n";
    cout << "+======================================================+\n";
}

void Luxury::displayRow() const
{
    string statusStr;
    if (getStatus() == VehicleStatus::Available) statusStr = Color::STATUS_AVAILABLE + "Available " + Color::RESET;
    else if (getStatus() == VehicleStatus::Rented) statusStr = Color::STATUS_RENTED + "Rented    " + Color::RESET;
    else statusStr = Color::STATUS_SOLD + "Sold      " + Color::RESET;

    string category = Color::CATEGORY_LUXURY + "Luxury    " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << statusStr
         << "| " << left << category
         << " |" << endl;
}

void Luxury::displayRowSimple() const
{
    string category = Color::CATEGORY_LUXURY + "Luxury    " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getYear()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << fixed << setprecision(2) << getRentalRate()
         << "| " << left << category
         << " |" << endl;
}


