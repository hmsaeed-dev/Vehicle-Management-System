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
    SUV(string id, string model, int year, int capacity, float rate);

    // Polymorphic overrides
    string getCategory() const override;
    float calculateCost(int hours) override;
    void displayInfo() override;
    void displayRow() const override;
};

#endif // SUV_H
