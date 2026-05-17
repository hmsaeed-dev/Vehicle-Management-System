#ifndef LUXURY_H
#define LUXURY_H

#include "Vehicle.h"

/**
 * @class Luxury
 * @brief Concrete class for high-end vehicles with extra features.
 */
class Luxury : public Vehicle
{
    private:
    string luxuryFeatures; // Special features (e.g., Sunroof, Leather Seats)

    public:
    // Constructor
    Luxury(string id, string model, int year, int capacity, float rate, string features);

    // Getter
    string getLuxuryFeatures() const;

    // Polymorphic overrides
    string getCategory() const override;
    float calculateCost(int hours) override;

protected:
    // UI Hooks
    string getHeaderTitle() const override { return "[PREMIUM LUXURY CLASS]"; }
    string getCategoryDisplay() const override;
    void displayExtraInfo() const override;
};


#endif // LUXURY_H
