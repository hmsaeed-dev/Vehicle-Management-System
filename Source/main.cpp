#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

#include "FileHandler.h"
#include "MenuHandler.h"
#include "Vehicle.h"
#include "User.h"
#include "Colors.h"

using namespace std;

/**
 * @brief Entry point of the Vehicle Management System.
 * Orchestrates the application lifecycle.
 */
int main()
{
#ifdef _WIN32
    // Enable ANSI colors for Windows CMD
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif

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
