#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"

/**
 * @class Van
 * @brief Concrete class for large passenger vehicles (Vans, Minivans, Buses).
 */
class Van : public Vehicle {
public:
    Van(string id, string model, int year, int capacity, float rate);
    string getCategory() const override;
    float calculateCost(int days) override;
    void displayInfo() override;
    void displayRow() const override;
};

#endif // VAN_H
