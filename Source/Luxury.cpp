#include "Luxury.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

using namespace std;

Luxury::Luxury(string id, string model, int capacity, float rate, string features) 
    : Vehicle(id, model, capacity, rate), luxuryFeatures(features) {}

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
    return (getRentalRate() * Pricing::LUXURY_MULTIPLIER) * days;
}

/**
 * @brief Displays luxury-specific info including premium features.
 */

string Luxury::getCategoryDisplay() const
{
    return Color::CATEGORY_LUXURY + "Luxury    " + Color::RESET;
}


