#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Vehicle.h"
#include "Customer.h"

using namespace std;

/**
 * @class Transaction
 * @brief Abstract base class for all deals (Rentals/Sales).
 * Uses Composition: References Vehicle and Customer objects.
 */
class Transaction
{
    protected:
    string transactionID;
    Vehicle* vehicle;    // Composition: HAS A Vehicle
    Customer* customer;  // Composition: HAS A Customer
    string date;

    public:
    // Constructor
    Transaction(string id, Vehicle* v, Customer* c, string date);

    // Virtual destructor
    virtual ~Transaction();

    // Pure Virtual Function
    virtual void finalise() = 0;

    // Getters
    string getTransactionID() const;
    string getDate() const;
};

#endif // TRANSACTION_H
