// Header Guard
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

#include <vector>
#include <string>

// Forward Declaration
class Vehicle;
class FileHandler;

// Doxygen Documentation Comment
/**
* @class Admin
* @brief Concrete class for administrative users.
*/

// Admin Class
class Admin : public User {
public:
    // Constructor
    Admin(std::string id, std::string username, std::string name, std::string phone, std::string password);

    // Polymorphic override for Admin menu
    void showMenu() override;

    // Administrative capabilities
    void showDashboard(const std::vector<Vehicle*>& fleet);
    void addVehicle(std::vector<Vehicle*>& fleet);

    void removeVehicle(std::vector<Vehicle*>& fleet);
    void salePurchaseModule(std::vector<Vehicle*>& fleet, std::vector<User*>& users, FileHandler& fh);
    void viewAllRecords(const std::vector<Vehicle*>& fleet, const std::vector<User*>& users);
};

#endif // ADMIN_H
