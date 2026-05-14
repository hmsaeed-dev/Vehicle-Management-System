#ifndef SALE_TRANSACTION_H
#define SALE_TRANSACTION_H

#include "Transaction.h"

/**
 * @class SaleTransaction
 * @brief Concrete class for vehicle purchases.
 */
class SaleTransaction : public Transaction {
private:
    float salePrice;

public:
    // Constructor
    SaleTransaction(string id, Vehicle* v, Customer* c, string date, float price);

    // Polymorphic override
    void finalise() override;
};

#endif // SALE_TRANSACTION_H
