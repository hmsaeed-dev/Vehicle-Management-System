//! File System Manager (FileHandler)
// bridge between your program's temporary memory (RAM) and the permanent storage (txt files)

#include "FileHandler.h"
#include "Economy.h"
#include "Luxury.h"
#include "SUV.h"
#include "Van.h"
#include "Admin.h"
#include "Customer.h"
#include "RentalTransaction.h"
#include "SaleTransaction.h"
#include "InspectionReport.h"
#include "Constants.h"

#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>




/**
 * @brief Helper to split a string by a delimiter and trim whitespace.
 */
vector<string> split(const string& s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter))
    {
        // Trim leading and trailing whitespace from the token
        size_t first = token.find_first_not_of(" \t\r\n");
        if (string::npos != first)
        {
            size_t last = token.find_last_not_of(" \t\r\n");
            tokens.push_back(token.substr(first, (last - first + 1)));
        }
        else
        {
            tokens.push_back(""); // Add empty string for consecutive delimiters or whitespace-only tokens
        }
    }
    return tokens;
}


/**
 * @brief Loads vehicles from Config::VEHICLE_FILE.
 * Uses factory-style logic to instantiate derived classes.
 */
vector<Vehicle*> FileHandler::loadVehicles()
{
    vector<Vehicle*> fleet;
    ifstream file(Config::VEHICLE_FILE);
    string line;

    if (!file.is_open()) {
        cerr << "[ERROR] Could not open " << Config::VEHICLE_FILE << " for reading." << endl;
        return fleet;
    }

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');

        if (data.size() < 7) {
            cerr << "[WARNING] Skipping malformed vehicle data: " << line << endl;
            continue;
        }

        try {
            // Format: Type|ID|Model|Year|Capacity|Rate|Status
            char type = data[0][0];
            string id = data[1];
            string model = data[2];
            int year = stoi(data[3]);
            int capacity = stoi(data[4]);
            float rate = stof(data[5]);
            int statusInt = stoi(data[6]);

            VehicleStatus status = static_cast<VehicleStatus>(statusInt);

            Vehicle* v = nullptr;
            if      (type == 'E') v = new Economy(id, model, year, capacity, rate);
            else if (type == 'L') v = new Luxury(id, model, year, capacity, rate, "Standard Luxury Pack");
            else if (type == 'S') v = new SUV(id, model, year, capacity, rate);
            else if (type == 'V') v = new Van(id, model, year, capacity, rate);

            if (v)
            {
                v->setStatus(status);
                fleet.push_back(v);
            }
        } catch (...) {
            cerr << "[ERROR] Exception parsing vehicle data: " << line << endl;
        }
    }
    file.close();
    return fleet;
}





/**
    * @brief Saves current fleet to Config::VEHICLE_FILE
 */


void FileHandler::saveVehicles(const vector<Vehicle*>& fleet)
{
    ofstream file(Config::VEHICLE_FILE);

    for (Vehicle* v : fleet)
    {
        char type = v->getID()[0];

        file << type << "|" << v->getID() << "|" << v->getModel() << "|" << v->getYear() << "|" << v->getCapacity() << "|" << v->getRentalRate() << "|" << static_cast<int>(v->getStatus()) << endl;
    }
    file.close();
}




/**
    * @brief Loads users from Config::USERS_FILE
 */

vector<User*> FileHandler::loadUsers()
{
    vector<User*> users;
    ifstream file(Config::USERS_FILE);
    string line;

    if (!file.is_open()) {
        cerr << "[ERROR] Could not open " << Config::USERS_FILE << " for reading." << endl;
        return users;
    }

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');

        if (data.size() < 4) {
            cerr << "[WARNING] Skipping malformed user data: " << line << endl;
            continue;
        }

        char type = data[0][0];
        string id = data[1];
        string username, name, phone, password;

        if (data.size() >= 6 && data[3].find('-') == string::npos) {
            username = data[2];
            name = data[3];
            phone = data[4];
            password = data[5];
        } else {
            username = id;
            name = data[2];
            phone = data[3];
            password = (data.size() > 4) ? data[4] : "1111";
        }

        if (username == "Admin" && name.find('-') != string::npos) {
             username = "admin";
             name = "Admin User";
        }

        if (type == 'A') users.push_back(new Admin(id, username, name, phone, password));
        else if (type == 'C') users.push_back(new Customer(id, username, name, phone, password));
    }

    file.close();
    return users;
}



void FileHandler::saveUsers(const vector<User*>& users)
{
    ofstream file(Config::USERS_FILE);
    for (User* u : users)
    {
        char type = u->getID()[0];

        // A for Admin, C for Customer
        file << type << "|" << u->getID() << "|" << u->getUsername() << "|" << u->getName() << "|" << u->getPhone() << "|" << u->getPassword() << endl;
    }
    file.close();
}

vector<Transaction*> FileHandler::loadTransactions()
{
    return vector<Transaction*>(); // Placeholder for now
}

void FileHandler::saveTransactions(const vector<Transaction*>& txns)
{
    // Implementation for full save if needed in future
}

void FileHandler::appendTransaction(const string& type, const string& vID, const string& cID, float amount, const string& date)
{
    ofstream file(Config::TRANSACTIONS_FILE, ios::app);
    if (file.is_open())
    {
        file << type << "|" << vID << "|" << cID << "|" << amount << "|" << date << endl;
        file.close();
    }
}

void FileHandler::loadTransactionsIntoHistory(vector<User*>& users)
{
    ifstream file(Config::TRANSACTIONS_FILE);
    string line;
    if (!file.is_open()) return;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');
        if (data.size() < 5) continue;

        string type = data[0];
        string vID = data[1];
        string cID = data[2];
        string amount = data[3];
        string date = data[4];

        for (User* u : users)
        {
            if (u->getID() == cID && u->getID()[0] == 'C')
            {
                Customer* customer = static_cast<Customer*>(u);
                string record;
                if (type == "SALE") record = "Purchased Vehicle " + vID + " for " + Pricing::CURRENCY + amount + " on " + date;
                else if (type == "RENT_START") record = "Started Rental of " + vID + " on " + date;
                else if (type == "RENT_RETURN") record = "Returned " + vID + " (Bill: " + Pricing::CURRENCY + amount + ") on " + date;

                if (!record.empty()) {
                    customer->addToHistory(record);
                }
            }
        }
    }
    file.close();
}




/**
 * @brief Appends an inspection report to Config::INSPECTIONS_FILE.
 */
void FileHandler::saveInspection(const InspectionReport& report)
{
    ofstream file(Config::INSPECTIONS_FILE, ios::app);
    if (file.is_open())
    {
        report.saveToFile(file);
        file.close();
    }
}

