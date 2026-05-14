#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

#include "FileHandler.h"
#include "SearchEngine.h"
#include "TripPlanner.h"
#include "RentalTransaction.h"
#include "Admin.h"
#include "Colors.h"
#include "Customer.h"
#include "InputHandler.h"

using namespace std;


// --- Helper Functions ---

void waitForUser()
{
    InputHandler::waitForEnter();
}


// --- Sub-Menu Handlers ---

void handleSearch(SearchEngine& engine)
{
    int choice;
    do
    {
        cout << "\n";
    cout << Color::BOLD << Color::CYAN;
    cout << "+----------------------------------------------------------+\n";
    cout << "|                   SEARCH VEHICLE FLEET                   |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "|                                                          |\n";
    cout << "|   [1]   By Model Name                                    |\n";
    cout << "|   [2]   By Price Range                                   |\n";
    cout << "|   [3]   By Category                                      |\n";
    cout << "|   [4]   By Availability                                  |\n";
    cout << "|   [5]   By Year                                          |\n";
    cout << "|   [6]   Back to Dashboard                                |\n";
    cout << "|                                                          |\n";
    cout << Color::CYAN << "+----------------------------------------------------------+\n\n" << Color::RESET;
    
    choice = InputHandler::getInt("Selection: ", 1, 6);

        vector<Vehicle*> results;
        if (choice == 1)
        {
            string name = InputHandler::getString("Enter model name: ");
            results = engine.searchByName(name);
        }

        else if (choice == 2)
        {
            float minP = InputHandler::getFloat("Enter Min Price: ");
            float maxP = InputHandler::getFloat("Enter Max Price: ");
            results = engine.searchByPriceRange(minP, maxP);
        }

        else if (choice == 3)
        {
            char type = InputHandler::getChar("Enter Category (E: Economy, L: Luxury, S: SUV): ", "ELS");
            results = engine.searchByCategory(type);
        }

        else if (choice == 4)
        {
            results = engine.searchByAvailability();
        }

        else if (choice == 5)
        {
            int minY = InputHandler::getInt("Enter Start Year: ");
            int maxY = InputHandler::getInt("Enter End Year: ");
            results = engine.searchByYearRange(minY, maxY);
        }

        if (choice >= 1 && choice <= 5)
        {
            if (results.empty()) {
                cout << "\n" << Color::WARNING << "[SYSTEM] No matching vehicles found." << Color::RESET << endl;
            } else {
                cout << "\n" << Color::INFO << "[SYSTEM] Found " << results.size() << " vehicles matching your criteria:" << Color::RESET << "\n";
                cout << "+-------+-------------------+-------+-------+----------+------------+------------+\n";
                cout << "| ID    | Model             | Year  | Cap.  | Rate     | Status     | Category   |\n";
                cout << "+-------+-------------------+-------+-------+----------+------------+------------+\n";
                for (Vehicle* v : results) v->displayRow();
                cout << "+-------+-------------------+-------+-------+----------+------------+------------+\n";
            }
            waitForUser();
        }
    }
    while (choice != 6);
}

void handleTripPlanning(TripPlanner& planner, vector<Vehicle*>& fleet)
{
    cout << "\n";
    cout << Color::BOLD << Color::YELLOW;
    cout << "+----------------------------------------------------------+\n";
    cout << "|                    TRIP PLANNER MODULE                   |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "  Please provide your travel details:\n\n";
    
    string src = InputHandler::getString("  > Starting Point   : ");
    string dest = InputHandler::getString("  > Destination      : ");
    float dist = InputHandler::getFloat("  > Distance (km)    : ");
    float budget = InputHandler::getFloat("  > Your Budget ($)  : ");
    int pax = InputHandler::getInt("  > Passenger Count  : ");

    cout << "\n" << Color::YELLOW << "+----------------------------------------------------------+\n" << Color::RESET;

    planner.planTrip(src, dest, dist, budget, pax, fleet);
    waitForUser();
}

// ================== Main Logic ==================

int main()
{
    FileHandler fh;
    vector<Vehicle*> fleet = fh.loadVehicles();
    vector<User*> users = fh.loadUsers();
    fh.loadTransactionsIntoHistory(users); // Load history on startup

    int mainChoice;
    while (true)
    {
        cout << "\n";
        cout << Color::BOLD << Color::YELLOW;
        cout << "+==========================================================+\n";
        cout << "|                                                          |\n";
        cout << "|               VEHICLE MANAGEMENT SYSTEM                  |\n";
        cout << "|                                                          |\n";
        cout << "+==========================================================+\n" << Color::RESET;
        cout << "|                                                          |\n";
        cout << "|   [1]   Register New Account                             |\n";
        cout << "|   [2]   Login to System                                  |\n";
        cout << "|   [3]   Exit System                                      |\n";
        cout << "|                                                          |\n";
        cout << Color::YELLOW << "+----------------------------------------------------------+\n\n" << Color::RESET;
        
        mainChoice = InputHandler::getInt("Selection: ", 1, 3);

        if (mainChoice == 3) break;

        if (mainChoice == 1)
        {
            string name, id, username, phone, password;
            cout << "\n";
            cout << Color::BOLD << Color::YELLOW;
            cout << "+----------------------------------------------------------+\n";
            cout << "|                 ACCOUNT REGISTRATION                     |\n";
            cout << "+----------------------------------------------------------+\n" << Color::RESET;
            cout << "  Please enter your details to create an account:\n\n";
            
            name = InputHandler::getString("  > Full Name        : ");
            username = InputHandler::getString("  > Username         : ", false);

            // Check if username is taken
            bool taken = false;
            for (User* u : users) {
                if (u->getUsername() == username) {
                    taken = true;
                    break;
                }
            }

            if (taken) {
                cout << Color::ERROR << "[ERROR] Username already taken. Please try another." << Color::RESET << endl;
                waitForUser();
                continue;
            }

            id = InputHandler::getString("  > Customer ID      : ", false);
            phone = InputHandler::getString("  > Phone Number     : ", false);
            password = InputHandler::getString("  > Secure Password  : ", false);

            cout << "\n" << Color::YELLOW << "+----------------------------------------------------------+\n" << Color::RESET;

            // Simple check: Customers start with C
            if (id[0] != 'C') {
                cout << Color::ERROR << "[ERROR] Only customer registration is allowed via this menu." << Color::RESET << endl;
            } else {
                users.push_back(new Customer(id, username, name, phone, password));
                cout << Color::SUCCESS << "[SUCCESS] Account created! Please login." << Color::RESET << endl;
            }
            waitForUser();
            continue;
        }

        if (mainChoice == 2)
        {
            cout << "\n";
            cout << Color::BOLD << Color::YELLOW;
            cout << "+----------------------------------------------------------+\n";
            cout << "|                    SYSTEM LOGIN                          |\n";
            cout << "+----------------------------------------------------------+\n" << Color::RESET;
            cout << "  Please verify your identity to continue:\n";
            
            string username = InputHandler::getString("  > Username         : ", false);
            string pass = InputHandler::getString("  > Password         : ", false);
            
            cout << Color::YELLOW << "+----------------------------------------------------------+\n" << Color::RESET;

            // Checking if User Exists
            User* currentUser = nullptr;
            for (User* u : users)
            {
                if (u->getUsername() == username && u->authenticate(pass))
                {
                    currentUser = u;
                    break;
                }
            }

            if (!currentUser)
            {
                cout << Color::ERROR << "[ERROR] Invalid Username or Password." << Color::RESET << endl;
                waitForUser();
                continue;
            }

            SearchEngine engine(fleet);
            TripPlanner planner;
            int choice;
            bool logout = false;

            do {
                currentUser->showMenu();
                choice = InputHandler::getInt("Selection: ");

                // Admin logic
                if (currentUser->getID()[0] == 'A')
                {
                    Admin* admin = static_cast<Admin*>(currentUser);
                    switch (choice) {
                        case 1: admin->addVehicle(fleet); break;
                        case 2: admin->removeVehicle(fleet); break;
                        case 3: admin->salePurchaseModule(fleet, users, fh); break;
                        case 4: admin->viewAllRecords(fleet, users); break;
                        case 5: logout = true; break;
                        default: cout << Color::ERROR << "Invalid selection. Please choose 1-5." << Color::RESET << endl;
                    }
                }

                // Customer logic
                else
                {
                    Customer* customer = static_cast<Customer*>(currentUser);
                    switch (choice)
                    {
                        case 1: handleSearch(engine); break;
                        case 2: customer->rentVehicle(fleet, fh); break;
                        case 3: customer->returnVehicle(fleet, fh); break;
                        case 4: handleTripPlanning(planner, fleet); break;
                        case 5: customer->viewRentalHistory(); break;
                        case 6: logout = true; break;
                        default: cout << Color::ERROR << "Invalid selection. Please choose 1-6." << Color::RESET << endl;
                    }
                }

                if (!logout && !((currentUser->getID()[0] == 'C' && choice == 1) || (currentUser->getID()[0] == 'C' && choice == 4)))
                {
                    waitForUser();
                }
            } while (!logout);
        }
    }

    cout << "\n" << Color::INFO << "[SYSTEM] Saving changes and shutting down..." << Color::RESET << endl;
    fh.saveVehicles(fleet);
    fh.saveUsers(users); // Now saving users too
    for (Vehicle* v : fleet) delete v;
    for (User* u : users) delete u;

    return 0;
}
