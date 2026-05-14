#include "Transaction.h"

/**
 * @brief Constructor for the Transaction base class.
 * Uses composition to link a vehicle and a customer to a record.
 */
Transaction::Transaction(string id, Vehicle* v, Customer* c, string date) 
    : transactionID(id), vehicle(v), customer(c), date(date) {}

/**
 * @brief Virtual destructor.
 */
Transaction::~Transaction() {}

string Transaction::getTransactionID() const {
    return transactionID;
}

string Transaction::getDate() const {
    return date;
}
