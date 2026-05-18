#include "Luxury.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

Luxury::Luxury(string id, string model, int year, int capacity, float rate, string features) : Vehicle(id, model, year, capacity, rate), luxuryFeatures(features) {}

string Luxury::getCategory() const {
    return "Luxury";
}

string Luxury::getLuxuryFeatures() const {
    return luxuryFeatures;
}

/**
 * @brief Premium billing for luxury cars.
 */
float Luxury::calculateCost(int days)
{
    float baseTotal = (getRentalRate() * Pricing::LUXURY_MULTIPLIER) * days;
    float discount = 0.0f;

    if (days >= Pricing::TIER_2_DAYS)
    {
        discount = Pricing::TIER_2_DISCOUNT;
    }

    else if (days >= Pricing::TIER_1_DAYS)
    {
        discount = Pricing::TIER_1_DISCOUNT;
    }

    return baseTotal * (1.0f - discount);
}

/**
 * @brief Displays luxury-specific info including premium features.
 */

string Luxury::getCategoryDisplay() const
{
    return Color::CATEGORY_LUXURY + "Luxury    " + Color::RESET;
}

void Luxury::displayExtraInfo() const {
    cout << "| Features      :  " << left << setw(36) << luxuryFeatures << "|\n";
    cout << "+------------------------------------------------------+\n";
}


