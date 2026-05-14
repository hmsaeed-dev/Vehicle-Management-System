#ifndef ECONOMY_H
#define ECONOMY_H

#include "Vehicle.h"

/**
 * @class Economy
 * @brief Concrete class for budget-friendly vehicles.
 */
class Economy : public Vehicle
{
public:
    // Constructor
    Economy(string id, string model, int year, int capacity, float rate);

    // Polymorphic overrides
    float calculateCost(int hours) override;
    void displayInfo() override;
    void displayRow() const override;
};

#endif // ECONOMY_H
