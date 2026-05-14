#ifndef INSPECTION_REPORT_H
#define INSPECTION_REPORT_H

#include <string>
#include <fstream>

using namespace std;

// Forward Declarations
class Vehicle;
class Customer;

/**
 * @class InspectionReport
 * @brief Records the condition of a vehicle upon return.
 * Uses Composition: References Vehicle and Customer.
 */
class InspectionReport {
private:
    Vehicle* inspectedVehicle;  // HAS A Vehicle
    Customer* inspector;        // HAS A Customer (the one returning)
    string fuelLevel;
    string damageNotes;
    float mileage;
    string condition;           // Good, Fair, Poor
    string evaluationRemarks;
    string date;

public:
    // Constructor
    InspectionReport(Vehicle* v, Customer* c);

    // Methods
    void fillReport();              // Interactive console input
    void displayReport() const;     // Show report details
    void saveToFile(ofstream& out) const; // Write to Inspections.txt
    float getDamageFee() const;
};

#endif // INSPECTION_REPORT_H
