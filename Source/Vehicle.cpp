#include "Vehicle.h"
#include "Constants.h"
#include "Colors.h"

#include <iostream>
#include <iomanip>

/**
 * @brief Constructor for the Vehicle base class.
 * Initializes core attributes common to all vehicles.
 */
Vehicle::Vehicle(string id, string model, int capacity, float rate)
    : vehicleID(id), model(model), capacity(capacity), rentalRate(rate), status(VehicleStatus::Available) {}
    
Vehicle::~Vehicle() {}

// --- Getters ---

string Vehicle::getID() const {
    return vehicleID;
}

string Vehicle::getModel() const {
    return model;
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


float Vehicle::calculateDiscountedCost(int days) {
    float baseTotal = calculateCost(days); // This already applies multipliers in derived classes
    float discount = baseTotal * getDiscountPercentage(days);
    return baseTotal - discount;
}

// --- UI Methods (Template Methods) ---

string Vehicle::getStatusString() const {
    switch (status) {
        case VehicleStatus::Available: return Color::STATUS_AVAILABLE + "AVAILABLE" + Color::RESET;
        case VehicleStatus::Rented:    return Color::STATUS_RENTED + "RENTED" + Color::RESET;
        case VehicleStatus::Sold:      return Color::STATUS_SOLD + "SOLD" + Color::RESET;
        default:                       return "UNKNOWN";
    }
}

void Vehicle::displayInfo() {
    cout << "\n";
    cout << Color::SUBHEADER;
    cout << "+------------------------------------------------------+\n";
    cout << "| " << left << setw(53) << getHeaderTitle() << "|\n";
    cout << "+------------------------------------------------------+\n" << Color::RESET;
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Capacity      :  " << left << setw(27) << getCapacity() << " " << setw(10) << getCapacityUnit() << "|\n";
    cout << "| Daily Rate    :  " << left << Pricing::CURRENCY << setw(35-Pricing::CURRENCY.length()) << (int)getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";

    // Call hook for category-specific info (Promos or Features)
    displayExtraInfo();

    cout << "| Status        :  " << left << setw(45) << getStatusString() << "|\n";
    cout << "+------------------------------------------------------+\n";
}

void Vehicle::displayRow() const
{
    string statusStr;
    if (status == VehicleStatus::Available) statusStr = Color::STATUS_AVAILABLE + "Available " + Color::RESET;
    else if (status == VehicleStatus::Rented) statusStr = Color::STATUS_RENTED + "Rented    " + Color::RESET;
    else statusStr = Color::STATUS_SOLD + "Sold      " + Color::RESET;

    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << (int)getRentalRate()
         << "| " << left << statusStr
         << "| " << left << getCategoryDisplay()
         << " |" << endl;
}

void Vehicle::displayRowSimple() const
{
    cout << "| " << left << setw(6) << getID()
         << "| " << left << setw(18) << getModel()
         << "| " << left << setw(6) << getCapacity()
         << "| " << Pricing::CURRENCY << left << setw(10-Pricing::CURRENCY.length()) << (int)getRentalRate()
         << "| " << left << getCategoryDisplay()
         << " |" << endl;
}

