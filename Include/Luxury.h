#ifndef LUXURY_H
#define LUXURY_H

#include "Vehicle.h"

/**
 * @class Luxury
 * @brief Concrete class for high-end vehicles with extra features.
 */
class Luxury : public Vehicle
{
    public:
    // Constructor
    Luxury(string id, string model, int capacity, float rate, string features = "");

    // Getter
    string getLuxuryFeatures() const;

    // Polymorphic overrides
    string getCategory() const override;
    float calculateCost(int hours) override;

protected:
    // UI Hooks
    string getHeaderTitle() const override { return "[PREMIUM LUXURY CLASS]"; }
    string getCategoryDisplay() const override;

private:
    string luxuryFeatures;
};


#endif // LUXURY_H
