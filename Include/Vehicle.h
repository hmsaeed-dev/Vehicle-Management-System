#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @class Vehicle
 * @brief Abstract base class representing the core vehicle entity.
 * Follows Option C: Separated .h and .cpp structure.
 */
enum class VehicleStatus { Available, Rented, Sold };

class Vehicle
{
private:
    string vehicleID;    // Unique ID (e.g., E001, L005)
    string model;        // Car model name
    int year;            // Manufacturing year
    int capacity;        // Seating capacity
    float rentalRate;    // Base price per hour/day
    VehicleStatus status; // Current status

public:
    // Constructor
    Vehicle(string id, string model, int year, int capacity, float rate);

    // Virtual destructor is mandatory for polymorphic cleanup
    virtual ~Vehicle();

    // Getters
    string getID() const;
    string getModel() const;
    int getYear() const;
    int getCapacity() const;
    float getRentalRate() const;
    VehicleStatus getStatus() const;
    bool getAvailable() const; // Helper for legacy code

    // Setters
    void setStatus(VehicleStatus newStatus);
    void setAvailable(bool available); // Helper for legacy code

    // Pure Virtual Functions
    virtual string getCategory() const = 0;
    virtual float calculateCost(int days) = 0;
    virtual void displayInfo() = 0;
    virtual void displayRow() const = 0; // New method for tabular view

    // Discount Logic
    float calculateDiscountedCost(int days);
    float getDiscountPercentage(int days) const;
};

#endif // VEHICLE_H
