#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <vector>
#include "Vehicle.h"

// Forward Declaration to break circular dependency
class FileHandler;

/**
 * @class Customer
 * @brief Concrete class for customers who rent/buy vehicles.
 */
class Customer : public User {
private:
    vector<string> rentalHistory; // List of vehicle IDs rented in the past

public:
    // Constructor
    Customer(string id, string username, string name, string phone, string password);

    // Polymorphic override for Customer menu
    void showMenu() override;

    // Customer capabilities
    void viewRentalHistory();
    void addToHistory(const string& record);
    void rentVehicle(vector<Vehicle*>& fleet, FileHandler& fh);
    void returnVehicle(vector<Vehicle*>& fleet, FileHandler& fh);
};

#endif // CUSTOMER_H
