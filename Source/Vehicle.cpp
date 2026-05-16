#include "Vehicle.h"
#include "Constants.h"

/**
 * @brief Constructor for the Vehicle base class.
 * Initializes core attributes common to all vehicles.
 */
Vehicle::Vehicle(string id, string model, int year, int capacity, float rate) 
    : vehicleID(id), model(model), year(year), capacity(capacity), rentalRate(rate), status(VehicleStatus::Available) {}

/**
 * @brief Virtual destructor.
 * Defined as empty; primary purpose is to allow proper cleanup of derived classes.
 */
Vehicle::~Vehicle() {}

// --- Getters ---

string Vehicle::getID() const {
    return vehicleID;
}

string Vehicle::getModel() const {
    return model;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::getCapacity() const {
    return capacity;
}

float Vehicle::getRentalRate() const {
    return rentalRate;
}

VehicleStatus Vehicle::getStatus() const {
    return status;
}

bool Vehicle::getAvailable() const {
    return status == VehicleStatus::Available;
}

// --- Setters ---

void Vehicle::setStatus(VehicleStatus newStatus) {
    status = newStatus;
}

/**
 * @brief Updates the availability status of the vehicle.
 * @param status true if available for rent, false if currently rented/sold.
 */
void Vehicle::setAvailable(bool available) {
    if (status == VehicleStatus::Sold) return; // SOLD is a terminal state for rentals
    status = available ? VehicleStatus::Available : VehicleStatus::Rented;
}

/**
 * @brief Determines the discount percentage based on days.
 */
float Vehicle::getDiscountPercentage(int days) const {
    if (days >= Pricing::TIER_2_DAYS) return Pricing::TIER_2_DISCOUNT; 
    if (days >= Pricing::TIER_1_DAYS) return Pricing::TIER_1_DISCOUNT;
    return 0.0f;
}

/**
 * @brief Calculates the total cost after applying tiered discounts.
 */
float Vehicle::calculateDiscountedCost(int days) {
    float baseTotal = calculateCost(days); // This already applies multipliers in derived classes
    float discount = baseTotal * getDiscountPercentage(days);
    return baseTotal - discount;
}

