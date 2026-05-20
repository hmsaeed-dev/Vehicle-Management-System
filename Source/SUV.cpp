#include "SUV.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

SUV::SUV(string id, string model, int capacity, float rate)
    : Vehicle(id, model, capacity, rate) {}

string SUV::getCategory() const {
    return "SUV";
}

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

string SUV::getCategoryDisplay() const {
    return Color::CATEGORY_SUV + "SUV       " + Color::RESET;
}

void SUV::displayExtraInfo() const {
    cout << "| [PROMO] " << Pricing::TIER_1_DAYS << "-" << (Pricing::TIER_2_DAYS-1) << " Days: " << (int)(Pricing::TIER_1_DISCOUNT*100) << "% OFF | " << Pricing::TIER_2_DAYS << "+ Days: " << (int)(Pricing::TIER_2_DISCOUNT*100) << "% OFF |\n";
    cout << "+------------------------------------------------------+\n";
}


