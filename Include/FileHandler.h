#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <vector>
#include <string>

using namespace std;

// Forward Declarations
class Vehicle;
class User;
class Transaction;
class InspectionReport;

/**
 * @class FileHandler
 * @brief Centralized class for all file I/O operations.
 * Sole owner of persistence logic.
 */
class FileHandler {
public:
    // Vehicle operations
    vector<Vehicle*> loadVehicles();
    void saveVehicles(const vector<Vehicle*>& fleet);

    // User operations
    vector<User*> loadUsers();
    void saveUsers(const vector<User*>& users);

    // Transaction operations
    vector<Transaction*> loadTransactions();
    void saveTransactions(const vector<Transaction*>& txns);
    void appendTransaction(const string& type, const string& vID, const string& cID, float amount, const string& date);
    void loadTransactionsIntoHistory(vector<User*>& users);

    // Inspection operations
    void saveInspection(const InspectionReport& report);
};

#endif // FILE_HANDLER_H
