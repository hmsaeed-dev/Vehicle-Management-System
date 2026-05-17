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
    string getCategory() const override;
    float calculateCost(int hours) override;

protected:
    // UI Hooks
    string getHeaderTitle() const override { return "[ECONOMY CLASS]"; }
    string getCategoryDisplay() const override;
    void displayExtraInfo() const override;
};


#endif // ECONOMY_H
