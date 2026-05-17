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

string Economy::getCategoryDisplay() const {
    return Color::CATEGORY_ECONOMY + "Economy   " + Color::RESET;
}

void Economy::displayExtraInfo() const {
    cout << "| [PROMO] " << Pricing::TIER_1_DAYS << "-" << (Pricing::TIER_2_DAYS-1) << " Days: " << (int)(Pricing::TIER_1_DISCOUNT*100) << "% OFF | " << Pricing::TIER_2_DAYS << "+ Days: " << (int)(Pricing::TIER_2_DISCOUNT*100) << "% OFF |\n";
    cout << "+------------------------------------------------------+\n";
}


