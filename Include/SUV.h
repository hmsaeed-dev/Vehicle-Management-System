#ifndef SUV_H
#define SUV_H

#include "Vehicle.h"

/**
 * @class SUV
 * @brief Concrete class for sports utility vehicles.
 */
class SUV : public Vehicle {
public:
    // Constructor
    SUV(string id, string model, int capacity, float rate);

    // Polymorphic overrides
    string getCategory() const override;
    float calculateCost(int hours) override;

protected:
    // UI Hooks
    string getHeaderTitle() const override { return "[SUV CATEGORY]"; }
    string getCategoryDisplay() const override;
    string getCapacityUnit() const override { return "Seats"; }
    void displayExtraInfo() const override;
};


#endif // SUV_H
