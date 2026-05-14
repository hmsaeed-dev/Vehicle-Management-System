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

#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>




/**
 * @brief Helper to split a string by a delimiter
 */

vector<string> split(const string& s, char delimiter)
{
    vector<string> tokens;          // A container for the split words
    string token;                   // A temporary string for each piece
    istringstream tokenStream(s);   // Treats the input string like a "file" stream

    // Reads the stream until it hits the delimiter (the '|')
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);    // Adds "V001", "Toyota", etc., to the list
    }
    return tokens;
}





/**
 * @brief Loads vehicles from Data/Vehicle.txt.
 * Uses factory-style logic to instantiate derived classes.
 */

vector<Vehicle*> FileHandler::loadVehicles()
{
    vector<Vehicle*> fleet;
    ifstream file("Data/Vehicle.txt");
    string line;

    if (!file.is_open()) return fleet;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');

        // Format: Type|ID|Model|Year|Capacity|Rate|Status
        char type = data[0][0];
        string id = data[1];
        string model = data[2];
        int year = stoi(data[3]);           // stoi : String to Integer
        int capacity = stoi(data[4]);
        float rate = stof(data[5]);         // stof : String to Float
        int statusInt = stoi(data[6]);

        // Converts the number back into the Enum (Available, Rented, Sold)
        VehicleStatus status = static_cast<VehicleStatus>(statusInt);

        Vehicle* v = nullptr;
        // Logic to create the specific child object
        if      (type == 'E') v = new Economy(id, model, year, capacity, rate);
        else if (type == 'L') v = new Luxury(id, model, year, capacity, rate, "Standard Luxury Pack");
        else if (type == 'S') v = new SUV(id, model, year, capacity, rate);
        else if (type == 'V') v = new Van(id, model, year, capacity, rate);
        if (v)
        {
            v->setStatus(status);
            fleet.push_back(v);
        }
    }
    file.close();
    return fleet;
}




/**
    * @brief Saves current fleet to Data/Vehicle.txt
    Saving Vehicles (State Persistence)
    (This writes the current state of your fleet vector back to the text file, overwriting the old data so it stays updated.)
 */


void FileHandler::saveVehicles(const vector<Vehicle*>& fleet)
{
    // Opens and Clear the File
    ofstream file("Data/Vehicle.txt");

    for (Vehicle* v : fleet)
    {
        char type = v->getID()[0];

        file << type << "|" << v->getID() << "|" << v->getModel() << "|" << v->getYear() << "|" << v->getCapacity() << "|" << v->getRentalRate() << "|" << static_cast<int>(v->getStatus()) << endl;
    }
    file.close();
}




/**
    * @brief Loads users from Data/Users.txt
    User Management (Admin vs. Customer)
 */

vector<User*> FileHandler::loadUsers()
{
    vector<User*> users;
    ifstream file("Data/Users.txt");
    string line;

    if (!file.is_open()) return users;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        vector<string> data = split(line, '|');

        char type = data[0][0];
        string id = data[1];
        string username, name, phone, password;

        // Smart Detection:
        // If 6 columns exist AND the 3rd column is lowercase/alphanumeric (like a username)
        // AND the 4th column isn't a phone number... we handle it.
        // For simplicity: If column 4 contains a dash, it's likely a phone number, meaning column 3 is the Name.
        
        if (data.size() >= 6 && data[3].find('-') == string::npos) {
            // Likely New Format: ID|Username|Name|Phone|Password
            username = data[2];
            name = data[3];
            phone = data[4];
            password = data[5];
        } else {
            // Likely Old or Corrupted Format: ID|Name|Phone|Password
            // We use the ID as a fallback username to prevent data shifting
            username = id; 
            name = data[2];
            phone = data[3];
            password = (data.size() > 4) ? data[4] : "1111";
        }

        // Final cleanup: Ensure no one has "Admin" as a username if it was a shift error
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
    ofstream file("Data/Users.txt");
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
    ofstream file("Data/Transactions.txt", ios::app);
    if (file.is_open())
    {
        file << type << "|" << vID << "|" << cID << "|" << amount << "|" << date << endl;
        file.close();
    }
}

void FileHandler::loadTransactionsIntoHistory(vector<User*>& users)
{
    ifstream file("Data/Transactions.txt");
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
                if (type == "SALE") record = "Purchased Vehicle " + vID + " for $" + amount + " on " + date;
                else if (type == "RENT_START") record = "Started Rental of " + vID + " on " + date;
                else if (type == "RENT_RETURN") record = "Returned " + vID + " (Bill: $" + amount + ") on " + date;
                
                if (!record.empty()) {
                    customer->addToHistory(record);
                }
            }
        }
    }
    file.close();
}




/**
 * @brief Appends an inspection report to Data/Inspections.txt.
 */
void FileHandler::saveInspection(const InspectionReport& report)
{
    ofstream file("Data/Inspections.txt", ios::app);
    if (file.is_open())
    {
        report.saveToFile(file);
        file.close();
    }
}
