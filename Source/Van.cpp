#include "Van.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

Van::Van(string id, string model, int capacity, float rate)
    : Vehicle(id, model, capacity, rate) {}

string Van::getCategory() const {
    return "Van/Bus";
}

float Van::calculateCost(int days) {
    return (getRentalRate() * Pricing::VAN_MULTIPLIER) * days;
}


string Van::getCategoryDisplay() const {
    return Color::CATEGORY_VAN + "Van/Bus   " + Color::RESET;
}

void Van::displayExtraInfo() const {
    cout << "| [PROMO] " << Pricing::TIER_1_DAYS << "-" << (Pricing::TIER_2_DAYS-1) << " Days: " << (int)(Pricing::TIER_1_DISCOUNT*100) << "% OFF | " << Pricing::TIER_2_DAYS << "+ Days: " << (int)(Pricing::TIER_2_DISCOUNT*100) << "% OFF |\n";
    cout << "+------------------------------------------------------+\n";
}


