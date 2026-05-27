#include "MenuHandler.h"
#include "Vehicle.h"
#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "FileHandler.h"
#include "SearchEngine.h"
#include "TripPlanner.h"
#include "InputHandler.h"
#include "Colors.h"
#include "Constants.h"
#include "Validator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

MenuHandler::MenuHandler(vector<Vehicle*>& fleet, vector<User*>& users, FileHandler& fh)
    : fleet(fleet), users(users), fh(fh) {}

void MenuHandler::runMainMenu()
{
    while (true)
    {
        cout << "\n";
        cout << Color::HEADER;
        cout << "+==========================================================+\n";
        cout << "|                                                          |\n";
        cout << "|               VEHICLE MANAGEMENT SYSTEM                  |\n";
        cout << "|                                                          |\n";
        cout << "+==========================================================+\n" << Color::RESET;
        cout << "|                                                          |\n";
        cout << "|   [1]   Register New Account                             |\n";
        cout << "|   [2]   Login to System                                  |\n";
        cout << "|   [Z]   Exit System                                      |\n";
        cout << "|                                                          |\n";
        cout << Color::HEADER << "+----------------------------------------------------------+\n\n" << Color::RESET;

        int mainChoice = InputHandler::getInt("Selection", 1, 2, true);

        if (mainChoice == InputHandler::CANCEL_INT) break;

        if (mainChoice == 1) handleRegistration();
        else if (mainChoice == 2) handleLogin();
    }
}

void MenuHandler::handleRegistration()
{
    string name, id, username, cnic, password;
    cout << "\n";
    cout << Color::HEADER;
    cout << "+==========================================================+\n";
    cout << "|                 ACCOUNT REGISTRATION                     |\n";
    cout << "+==========================================================+\n" << Color::RESET;
    cout << "  Please enter your details to create an account (or 'Z' to go back):\n\n";

    while (true) {
        name = InputHandler::getString("  > Full Name (Min 3 characters)", true, true);
        if (name == InputHandler::CANCEL_STR) return;
        
        // Strictly enforcing 3+ characters for Pakistan-style full names
        if (name.length() >= 3 && Validator::isAlphaOnly(name)) break;
        
        cout << Color::ERR << "[ERROR] Name must be at least 3 characters and contain only letters." << Color::RESET << endl;
    }

    username = InputHandler::getString("  > Login Username", false, true);
    if (username == InputHandler::CANCEL_STR) return;

    // Check if username is taken
    bool taken = false;
    for (User* u : users) {
        if (u->getUsername() == username) {
            taken = true;
            break;
        }
    }

    if (taken) {
        cout << Color::ERR << "[ERROR] Username already taken. Please try another." << Color::RESET << endl;
        InputHandler::waitForEnter();
        return;
    }

    // --- AUTOMATED ID GENERATION ---
    id = FileHandler::generateNextUserID(users);

    while (true) {
        cnic = InputHandler::getString("  > CNIC (XXXXX-XXXXXXX-X)", false, true);
        if (cnic == InputHandler::CANCEL_STR) return;
        if (Validator::isValidCNIC(cnic)) break;
        cout << Color::ERR << "[ERROR] Invalid CNIC format. Expected: 12345-1234567-1" << Color::RESET << endl;
    }

    password = InputHandler::getString("  > Secure Password", false, true);
    if (password == InputHandler::CANCEL_STR) return;

    cout << "\n" << Color::HEADER << "+----------------------------------------------------------+\n" << Color::RESET;

    users.push_back(new Customer(id, username, name, cnic, password));
    cout << Color::SUCCESS << "[SUCCESS] Registration complete!" << Color::RESET << endl;
    cout << "  Your assigned Account ID is: " << Color::HIGHLIGHT << id << Color::RESET << endl;
    cout << "  Please use your Username (" << Color::HIGHLIGHT << username << Color::RESET << ") for future logins." << endl;
    InputHandler::waitForEnter();
}

void MenuHandler::handleLogin()
{
    cout << "\n";
    cout << Color::HEADER;
    cout << "+----------------------------------------------------------+\n";
    cout << "|                    SYSTEM LOGIN                          |\n";
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
    cout << "  Please verify your identity to continue (or 'Z' to go back):\n";

    string username = InputHandler::getString("  > Username", false, true);
    if (username == InputHandler::CANCEL_STR) return;

    string pass = InputHandler::getString("  > Password", false, true);
    if (pass == InputHandler::CANCEL_STR) return;

    cout << Color::HEADER << "+----------------------------------------------------------+\n" << Color::RESET;

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
        cout << Color::ERR << "[ERROR] Invalid Username or Password." << Color::RESET << endl;
        InputHandler::waitForEnter();
        return;
    }

    if (currentUser->getRole() == "ADMIN") adminSession(currentUser);
    else customerSession(currentUser);
}

void MenuHandler::adminSession(User* currentUser)
{
    Admin* admin = static_cast<Admin*>(currentUser);
    bool logout = false;
    do {
        admin->showDashboard(fleet);
        admin->showMenu();
        int choice = InputHandler::getInt("Selection", 1, 8, true);

        if (choice == InputHandler::CANCEL_INT) { logout = true; break; }

        switch (choice) {
            case 1: admin->addVehicle(fleet); break;
            case 2: admin->removeVehicle(fleet); break;
            case 3: admin->removeUser(users, fh); break;
            case 4: admin->salePurchaseModule(fleet, users, fh); break;
            case 5: admin->viewAllRecords(fleet, users); break;
            case 6: admin->viewTransactionHistory(); break;
            case 7: admin->viewCustomerReport(users); break;
            case 8: admin->processReturn(fleet, users, fh); break;
            default: cout << Color::ERR << "Invalid selection." << Color::RESET << endl;
        }
        if (!logout) InputHandler::waitForEnter();
    } while (!logout);
}


void MenuHandler::customerSession(User* currentUser)
{
    Customer* customer = static_cast<Customer*>(currentUser);
    SearchEngine engine(fleet);
    TripPlanner planner;
    bool logout = false;
    do {
        customer->showMenu();
        int choice = InputHandler::getInt("Selection", 1, 5, true);

        if (choice == InputHandler::CANCEL_INT) { logout = true; break; }

        switch (choice)
        {
            case 1: handleSearch(engine, fleet, customer, &fh); break;
            case 2: customer->rentVehicle(fleet, fh); break;
            case 3: customer->returnVehicle(fleet, fh); break;
            case 4: handleTripPlanning(planner, fleet, customer, &fh); break;
            case 5: customer->viewRentalHistory(); break;
            default: cout << Color::ERR << "Invalid selection !!!" << Color::RESET << endl;
        }
        if (!logout && choice != 1 && choice != 4) InputHandler::waitForEnter();
    } while (!logout);
}

void MenuHandler::handleSearch(SearchEngine& engine, vector<Vehicle*>& fleet, Customer* customer, FileHandler* fh)
{
    int choice;
    do
    {
        cout << "\n";
        cout << Color::SUBHEADER;
        cout << "+----------------------------------------------------------+\n";
        cout << "|                   SEARCH VEHICLE FLEET                   |\n";
        cout << "+----------------------------------------------------------+\n" << Color::RESET;
        cout << "|                                                          |\n";
        cout << "|   [1]   Browse All Vehicles                              |\n";
        cout << "|   [2]   Filter by Category                               |\n";
        cout << "|   [Z]   Back to Dashboard                                |\n";
        cout << "|                                                          |\n";
        cout << Color::TABLE_HEADER << "+----------------------------------------------------------+\n\n" << Color::RESET;

        choice = InputHandler::getInt("Selection", 1, 4, true);

        vector<Vehicle*> results;
        bool onlyAvailFilter = false;
        if (choice == InputHandler::CANCEL_INT) break;

        if (choice == 1) {
            for (Vehicle* v : fleet) {
                if (v->getStatus() != VehicleStatus::Sold) results.push_back(v);
            }
        }
        else if (choice == 2)
        {
            cout << "\n" << Color::SUBHEADER << "Select a Category to Explore:" << Color::RESET << "\n";
            cout << "1. Economy  - Budget-friendly\n";
            cout << "2. Luxury   - Premium experience\n";
            cout << "3. SUV      - Spacious, off-road capable\n";
            cout << "4. Van / Bus  - Large groups, maximum capacity\n";
            int catChoice = InputHandler::getInt("Choice", 1, 4);
            char type = 'E';
            if (catChoice == 2) type = 'L';
            else if (catChoice == 3) type = 'S';
            else if (catChoice == 4) type = 'V';
            results = engine.searchByCategory(type);
        }
        if (choice >= 1 && choice <= 4)
        {
            if (results.empty()) {
                cout << "\n" << Color::WARNING << "[SYSTEM] No matching vehicles found." << Color::RESET << endl;
                InputHandler::waitForEnter();
            } else {
                cout << "\n" << Color::INFO << "[SYSTEM] Found " << results.size() << " vehicles matching your criteria:" << Color::RESET << "\n";

                if (onlyAvailFilter) {
                    cout << "+-------+-------------------+-------+------------+------------+\n";
                    cout << "| ID    | Model             | Cap.  | Rate       | Category   |\n";
                    cout << "+-------+-------------------+-------+------------+------------+\n";
                    for (Vehicle* v : results) v->displayRowSimple();
                    cout << "+-------+-------------------+-------+------------+------------+\n";
                } else {
                    cout << "+-------+-------------------+-------+------------+------------+------------+\n";
                    cout << "| ID    | Model             | Cap.  | Rate       | Status     | Category   |\n";
                    cout << "+-------+-------------------+-------+------------+------------+------------+\n";
                    for (Vehicle* v : results) v->displayRow();
                    cout << "+-------+-------------------+-------+------------+------------+------------+\n";
                }

                if (customer && fh) {
                    string rentID = InputHandler::getString("\nEnter Vehicle ID to RENT (or press Enter to continue)", true, false, true);
                    if (!rentID.empty()) {
                        bool found = false;
                        for (Vehicle* v : results) if (v->getID() == rentID) { found = true; break; }
                        if (found) { customer->processRental(rentID, fleet, *fh); InputHandler::waitForEnter(); }
                        else { cout << Color::ERR << "[ERROR] That ID was not in the search results." << Color::RESET << endl; InputHandler::waitForEnter(); }
                    }
                } else {
                    InputHandler::waitForEnter();
                }
            }
        }
    } while (choice != InputHandler::CANCEL_INT);
}

void MenuHandler::handleTripPlanning(TripPlanner& planner, vector<Vehicle*>& fleet, Customer* customer, FileHandler* fh)
{
    cout << "\n";
    cout << Color::HEADER;
    cout << "+==========================================================+\n";
    cout << "|                    TRIP PLANNER MODULE                   |\n";
    cout << "+==========================================================+\n" << Color::RESET;
    cout << "  Please provide your travel details:\n\n";

    string src = InputHandler::getAlphaString("  > Starting Point");
    string dest = InputHandler::getAlphaString("  > Destination");
    float dist = InputHandler::getFloat("  > Distance (km)", 1.0f, 20000.0f);
    float budget = InputHandler::getFloat("  > Your Budget (" + Pricing::CURRENCY + ")", 100.0f, 1000000.0f);
    int pax = InputHandler::getInt("  > Passenger Count", 1, 20);

    cout << "\n" << Color::HEADER << "+----------------------------------------------------------+\n" << Color::RESET;
    planner.planTrip(src, dest, dist, budget, pax, fleet);

    if (customer && fh)
    {
        string rentID = InputHandler::getString("\nWould you like to RENT one of these? Enter ID (or press Enter to skip)", true, false, true);
        if (!rentID.empty())
        {
            customer->processRental(rentID, fleet, *fh);
            InputHandler::waitForEnter();
        }

        else InputHandler::waitForEnter();
    }
    else InputHandler::waitForEnter();
}
