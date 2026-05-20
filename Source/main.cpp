#include <iostream>
#include <vector>

#include "FileHandler.h"
#include "MenuHandler.h"
#include "Vehicle.h"
#include "User.h"
#include "Colors.h"

using namespace std;

/**
 * @brief Entry point of the Vehicle Management System.
 */
int main()
{
    FileHandler fh;

    // 1. Initial Data Loading
    vector<Vehicle*> fleet = fh.loadVehicles();
    vector<User*> users = fh.loadUsers();
    fh.loadTransactionsIntoHistory(users);

    // 2. UI Orchestration
    MenuHandler menu(fleet, users, fh);
    menu.runMainMenu();

    // 3. System Shutdown & Persistence
    cout << "\n" << Color::INFO << "[SYSTEM] Saving changes and shutting down..." << Color::RESET << endl;
    fh.saveVehicles(fleet);
    fh.saveUsers(users);

    // 4. Memory Management
    for (Vehicle* v : fleet) delete v;
    for (User* u : users) delete u;

    return 0;
}
