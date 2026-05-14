#ifndef RENTAL_TRANSACTION_H
#define RENTAL_TRANSACTION_H

#include "Transaction.h"

/**
 * @class RentalTransaction
 * @brief Concrete class for vehicle rentals.
 */
class RentalTransaction : public Transaction {
private:
    string startTime;
    string endTime;
    int daysRented;
    float totalBill;

public:
    // Constructor
    RentalTransaction(string id, Vehicle* v, Customer* c, string date, string start);

    // Polymorphic override
    void finalise() override;

    // Additional methods
    void setEndTime(string end, int days);
    float calculateBill();
};

#endif // RENTAL_TRANSACTION_H
