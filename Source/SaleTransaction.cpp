#include "SaleTransaction.h"
#include <iostream>

using namespace std;

SaleTransaction::SaleTransaction(string id, Vehicle* v, Customer* c, string date, float price)
    : Transaction(id, v, c, date), salePrice(price) {}

/**
 * @brief Finalizes the sale deal.
 * Permanently removes the vehicle from the available fleet.
 */
void SaleTransaction::finalise() {
    if (vehicle) {
        vehicle->setAvailable(false); // Vehicle is sold and no longer available
        cout << "[SALE] Transaction " << getTransactionID() << " finalized." << endl;
        cout << "[SALE] Vehicle " << vehicle->getID() << " SOLD for $" << salePrice << endl;
    }
}
