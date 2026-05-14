#include "RentalTransaction.h"
#include <iostream>

using namespace std;

// Constructor
RentalTransaction::RentalTransaction(string id, Vehicle* v, Customer* c, string date, string start)
    : Transaction(id, v, c, date), startTime(start), endTime("N/A"), daysRented(0), totalBill(0.0f) {}

/**
 * @brief Finalizes the rental deal.
 * Marks the vehicle as rented and calculates the initial expectation.
 */

void RentalTransaction::finalise()
{
    if (vehicle) {
        vehicle->setAvailable(false); // Vehicle is now on the road
        cout << "[RENTAL] Transaction " << getTransactionID() << " finalized." << endl;
        cout << "[RENTAL] Vehicle " << vehicle->getID() << " marked as RENTED." << endl;
    }
}

/**
 * @brief Records the return of the vehicle.
 */
void RentalTransaction::setEndTime(string end, int days) {
    endTime = end;
    daysRented = days;
    totalBill = calculateBill();

    if (vehicle) {
        vehicle->setAvailable(true); // Vehicle is back in the garage
    }
}

/**
 * @brief Calculates the bill using polymorphism.
 * Calls the vehicle's specific calculateCost method.
 */
float RentalTransaction::calculateBill()
{
    if (vehicle)
    {
        return vehicle->calculateCost(daysRented);
    }
    return 0.0f;
}
