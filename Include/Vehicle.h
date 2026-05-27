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
    string vehicleID;    // Unique Numeric ID (e.g., 1001, 2005)
    string model;        // Car model name
    int capacity;        // Seating capacity
    float rentalRate;    // Base price per hour/day
    VehicleStatus status; // Current status

public:
    // Constructor
    Vehicle(string id, string model, int capacity, float rate);

    // Virtual destructor is mandatory for polymorphic cleanup
    virtual ~Vehicle();

    // Getters
    string getID() const;
    string getModel() const;
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
    
    // UI Methods (Template Methods)
    virtual void displayInfo();
    virtual void displayRow() const; // Tabular view with status
    virtual void displayRowSimple() const; // Tabular view without status column

    // Discount Logic
    float calculateDiscountedCost(int days);
    float getDiscountPercentage(int days) const;

protected:
    // Hooks for Template Method Pattern (UI)
    virtual string getHeaderTitle() const = 0;
    virtual string getCategoryDisplay() const = 0;
    virtual string getCapacityUnit() const { return "Person(s)"; }
    virtual void displayExtraInfo() const {}

    // Helper for status string formatting
    string getStatusString() const;
};

#endif // VEHICLE_H
