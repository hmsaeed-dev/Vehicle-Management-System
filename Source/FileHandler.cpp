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
 */
vector<Vehicle*> FileHandler::loadVehicles()
{
    vector<Vehicle*> fleet;
    ifstream file(Config::VEHICLE_FILE);
    string line;

    if (!file.is_open())
    {
        cerr << "[ERROR] Could not open " << Config::VEHICLE_FILE << " for reading." << endl;
        return fleet;
    }

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');

        if (data.size() < 6)
        {
            cerr << "[WARNING] Skipping malformed vehicle data: " << line << endl;
            continue;
        }

        try {
            // Format: Type|ID|Model|Capacity|Rate|Status
            char type = data[0][0];
            string id = data[1];
            string model = data[2];
            int capacity = stoi(data[3]);
            float rate = stof(data[4]);
            int statusInt = stoi(data[5]);

            VehicleStatus status = static_cast<VehicleStatus>(statusInt);

            Vehicle* v = nullptr;
            if      (type == '3') v = new Economy(id, model, capacity, rate);
            else if (type == '4') v = new Luxury(id, model, capacity, rate, "Standard Luxury Pack");
            else if (type == '5') v = new SUV(id, model, capacity, rate);
            else if (type == '6') v = new Van(id, model, capacity, rate);

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
        string cat = v->getCategory();
        char typeCode = '0';
        if      (cat == "Economy") typeCode = '3';
        else if (cat == "Luxury")  typeCode = '4';
        else if (cat == "SUV")     typeCode = '5';
        else if (cat == "Van/Bus")     typeCode = '6';

        // Format: Type|ID|Model|Capacity|Rate|Status
        file << typeCode << "|" << v->getID() << "|" << v->getModel() << "|" << v->getCapacity() << "|" << v->getRentalRate() << "|" << static_cast<int>(v->getStatus()) << endl;
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

        // Format: ROLE|ID|USERNAME|NAME|CNIC|PASSWORD (6 fields)
        if (data.size() < 6) continue;

        string roleRaw = data[0];
        string id = data[1];
        string username = data[2];
        string name = data[3];
        string cnic = data[4];
        string password = data[5];

        if (roleRaw == "ADMIN") users.push_back(new Admin(id, username, name, cnic, password));
        else if (roleRaw == "CUSTOMER") users.push_back(new Customer(id, username, name, cnic, password));
    }

    file.close();
    return users;
}



void FileHandler::saveUsers(const vector<User*>& users)
{
    ofstream file(Config::USERS_FILE);
    for (User* u : users)
    {
        // Format: ROLE|ID|USERNAME|NAME|CNIC|PASSWORD
        file << u->getRole() << "|" << u->getID() << "|" << u->getUsername() << "|" << u->getName() << "|" << u->getCNIC() << "|" << u->getPassword() << endl;
    }
    file.close();
}

string FileHandler::generateNextUserID(const vector<User*>& users)
{
    int maxID = 1000;
    for (User* u : users) {
        try {
            int id = stoi(u->getID());
            if (id > maxID) maxID = id;
        } catch (...) {}
    }
    return to_string(maxID + 1);
}

string FileHandler::generateNextVehicleID(const vector<Vehicle*>& fleet)
{
    int maxID = 0;
    for (Vehicle* v : fleet) {
        try {
            int id = stoi(v->getID());
            if (id > maxID) maxID = id;
        } catch (...) {}
    }
    return to_string(maxID + 1);
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
            if (u->getID() == cID)
            {
                Customer* customer = dynamic_cast<Customer*>(u);
                if (customer) {
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
    }
    file.close();
}

string FileHandler::getRentalStartDate(const string& vID, const string& cID)
{
    ifstream file(Config::TRANSACTIONS_FILE);
    string line;
    string startDate = "";

    if (!file.is_open()) return "";

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');
        if (data.size() < 5) continue;

        // Type|vID|cID|Amount|Date
        if (data[0] == "RENT_START" && data[1] == vID && data[2] == cID)
        {
            startDate = data[4]; // Keep track of the latest start date
        }
    }
    file.close();
    return startDate;
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

