#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @file Constants.h
 * @brief Centralized configuration for business logic and pricing multipliers.
 */

namespace Pricing
{
    // Category Multipliers (Reflecting Pakistani Market Premiums)
    const float LUXURY_MULTIPLIER = 1.80f; // Luxury cars (Civic) have higher premiums in PK
    const float SUV_MULTIPLIER    = 1.40f; // SUVs (Fortuner/Sportage) are highly valued
    const float VAN_MULTIPLIER    = 1.25f; // Hiace/APV rates
    const float ECONOMY_MULTIPLIER = 1.00f; // Alto/Cultus base rates

    // Currency Label
    const std::string CURRENCY = "Rs. ";

    // Discount Tiers
    const int TIER_1_DAYS = 4;
    const float TIER_1_DISCOUNT = 0.10f; // 10%

    const int TIER_2_DAYS = 8;
    const float TIER_2_DISCOUNT = 0.20f; // 20%

    // Damage Fee Percentages (based on daily rental rate)
    const float DAMAGE_FEE_POOR = 2.0f; // 200% of daily rate
    const float DAMAGE_FEE_FAIR = 0.5f; // 50% of daily rate
    const float DAMAGE_FEE_GOOD = 0.0f; 
}

namespace Config
{
    const std::string VEHICLE_FILE = "Data/Vehicle.txt";
    const std::string USERS_FILE = "Data/Users.txt";
    const std::string TRANSACTIONS_FILE = "Data/Transactions.txt";
    const std::string INSPECTIONS_FILE = "Data/Inspections.txt";
}


#endif // CONSTANTS_H
