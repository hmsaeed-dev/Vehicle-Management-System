#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

#include "FileHandler.h"
#include "SearchEngine.h"
#include "TripPlanner.h"
#include "RentalTransaction.h"
#include "Admin.h"
#include "Customer.h"

using namespace std;


// --- Helper Functions ---

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForUser()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


// --- Sub-Menu Handlers ---

void handleSearch(SearchEngine& engine)
{
    int choice;
    do
    {
        cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                   SEARCH VEHICLE FLEET                   |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                                                          |\n";
    cout << "|   [1]   By Model Name                                    |\n";
    cout << "|   [2]   By Price Range                                   |\n";
    cout << "|   [3]   By Category                                      |\n";
    cout << "|   [4]   By Availability                                  |\n";
    cout << "|   [5]   By Year                                          |\n";
    cout << "|   [6]   Back to Dashboard                                |\n";
    cout << "|                                                          |\n";
    cout << "+----------------------------------------------------------+\n\n";
    cout << "Selection: ";

        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        vector<Vehicle*> results;
        if (choice == 1)
        {
            string name;
            cout << "Enter model name: "; cin >> name;
            results = engine.searchByName(name);
        }

        else if (choice == 2)
        {
            float minP, maxP;
            cout << "Enter Min Price: "; cin >> minP;
            cout << "Enter Max Price: "; cin >> maxP;
            results = engine.searchByPriceRange(minP, maxP);
        }

        else if (choice == 3)
        {
            char type;
            cout << "Enter Category \nE: Economy\nL: Luxury\nS: SUV\n"; cin >> type;
            results = engine.searchByCategory(type);
        }

        else if (choice == 4)
        {
            results = engine.searchByAvailability();
        }

        else if (choice == 5)
        {
            int minY, maxY;
            cout << "Enter Start Year: "; cin >> minY;
            cout << "Enter End Year: "; cin >> maxY;
            results = engine.searchByYearRange(minY, maxY);
        }

        if (choice >= 1 && choice <= 5)
        {
            if (results.empty()) {
                cout << "\n[SYSTEM] No matching vehicles found." << endl;
            } else {
                cout << "\n[SYSTEM] Found " << results.size() << " vehicles matching your criteria:\n";
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
    string src, dest;
    float dist, budget;
    int pax;

    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                    TRIP PLANNER MODULE                   |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "  Please provide your travel details:\n\n";
    cout << "  > Starting Point   : "; cin >> src;
    cout << "  > Destination      : "; cin >> dest;
    cout << "  > Distance (km)    : "; cin >> dist;
    cout << "  > Your Budget ($)  : "; cin >> budget;
    cout << "  > Passenger Count  : "; cin >> pax;

    cout << "\n+----------------------------------------------------------+\n";

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
        cout << "+==========================================================+\n";
        cout << "|                                                          |\n";
        cout << "|          CAR RENTAL & RESERVATION SYSTEM                 |\n";
        cout << "|                                                          |\n";
        cout << "+==========================================================+\n";
        cout << "|                                                          |\n";
        cout << "|   [1]   Register New Account                             |\n";
        cout << "|   [2]   Login to System                                  |\n";
        cout << "|   [3]   Exit System                                      |\n";
        cout << "|                                                          |\n";
        cout << "+----------------------------------------------------------+\n\n";
        cout << "Selection: ";

        if (!(cin >> mainChoice))
        {
            clearInput();
            continue;
        }

        if (mainChoice == 3) break;

        if (mainChoice == 1)
        {
            string name, id, username, phone, password;
            cout << "\n";
            cout << "+----------------------------------------------------------+\n";
            cout << "|                 ACCOUNT REGISTRATION                     |\n";
            cout << "+----------------------------------------------------------+\n";
            cout << "  Please enter your details to create an account:\n\n";
            cout << "  > Full Name        : "; cin.ignore(); getline(cin, name);
            cout << "  > Username         : "; cin >> username;

            // Check if username is taken
            bool taken = false;
            for (User* u : users) {
                if (u->getUsername() == username) {
                    taken = true;
                    break;
                }
            }

            if (taken) {
                cout << "[ERROR] Username already taken. Please try another." << endl;
                waitForUser();
                continue;
            }

            cout << "  > Customer ID      : "; cin >> id;
            cout << "  > Phone Number     : "; cin >> phone;
            cout << "  > Secure Password  : "; cin >> password;

            cout << "\n+----------------------------------------------------------+\n";

            // Simple check: Customers start with C
            if (id[0] != 'C') {
                cout << "[ERROR] Only customer registration is allowed via this menu." << endl;
            } else {
                users.push_back(new Customer(id, username, name, phone, password));
                cout << "[SUCCESS] Account created! Please login." << endl;
            }
            continue;
        }

        if (mainChoice == 2)
        {
            string username, pass;
            cout << "\n";
            cout << "+----------------------------------------------------------+\n";
            cout << "|                    SYSTEM LOGIN                          |\n";
            cout << "+----------------------------------------------------------+\n";
            cout << "  Please verify your identity to continue:\n";
            cout << "  > Username         : "; cin >> username;
            cout << "  > Password         : "; cin >> pass;
            cout << "+----------------------------------------------------------+\n";

            // Checking if User Exists
            User* currentUser = nullptr;
            for (User* u : users) {
                if (u->getUsername() == username && u->authenticate(pass)) {
                    currentUser = u;
                    break;
                }
            }

            if (!currentUser) {
                cout << "[ERROR] Invalid Username or Password." << endl;
                waitForUser();
                continue;
            }

            SearchEngine engine(fleet);
            TripPlanner planner;
            int choice;
            bool logout = false;

            do {
                currentUser->showMenu();
                if (!(cin >> choice)) {
                    cout << "Invalid choice." << endl;
                    clearInput();
                    continue;
                }

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
                        default: cout << "Invalid selection. Please choose 1-5." << endl;
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
                        default: cout << "Invalid selection. Please choose 1-6." << endl;
                    }
                }

                if (!logout && !((currentUser->getID()[0] == 'C' && choice == 1) || (currentUser->getID()[0] == 'C' && choice == 4)))
                {
                    waitForUser();
                }
            } while (!logout);
        }
    }

    cout << "\n[SYSTEM] Saving changes and shutting down..." << endl;
    fh.saveVehicles(fleet);
    fh.saveUsers(users); // Now saving users too
    for (Vehicle* v : fleet) delete v;
    for (User* u : users) delete u;

    return 0;
}
