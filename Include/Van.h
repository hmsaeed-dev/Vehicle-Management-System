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
    // Polymorphic overrides
    string getCategory() const override;
    float calculateCost(int days) override;

    protected:
    // UI Hooks
    string getHeaderTitle() const override { return "[VAN / BUS CATEGORY]"; }
    string getCategoryDisplay() const override;
    string getCapacityUnit() const override { return "Pax"; }
    void displayExtraInfo() const override;
    };


#endif // VAN_H
