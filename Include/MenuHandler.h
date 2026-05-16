#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <vector>
#include <string>

class Vehicle;
class User;
class FileHandler;
class SearchEngine;
class TripPlanner;
class Customer;

/**
 * @class MenuHandler
 * @brief Manages the various menus and UI flows of the application.
 * Decouples main logic from specific menu implementations.
 */
class MenuHandler
{
private:
    std::vector<Vehicle*>& fleet;
    std::vector<User*>& users;
    FileHandler& fh;

public:
    MenuHandler(std::vector<Vehicle*>& fleet, std::vector<User*>& users, FileHandler& fh);

    // Main Menus
    void runMainMenu();
    void handleRegistration();
    void handleLogin();

    // Sub-Menus
    static void handleSearch(SearchEngine& engine, std::vector<Vehicle*>& fleet, Customer* customer = nullptr, FileHandler* fh = nullptr);
    static void handleTripPlanning(TripPlanner& planner, std::vector<Vehicle*>& fleet, Customer* customer = nullptr, FileHandler* fh = nullptr);

private:
    void adminSession(User* currentUser);
    void customerSession(User* currentUser);
};

#endif // MENU_HANDLER_H
