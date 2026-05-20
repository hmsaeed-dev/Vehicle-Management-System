#include "Economy.h"
#include "Colors.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>


using namespace std;

Economy::Economy(string id, string model, int capacity, float rate)
    : Vehicle(id, model, capacity, rate) {}

string Economy::getCategory() const {
    return "Economy";
}

/**
 * @brief Simple billing for economy cars.
 * No extra multipliers applied.
 */

float Economy::calculateCost(int days)
{
    return (getRentalRate() * Pricing::ECONOMY_MULTIPLIER) * days;
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


