#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

/**
 * @class Validator
 * @brief Centralized utility for data validation across the system.
 */
class Validator
{
public:
    // --- Numeric Validations ---
    static bool isNonNegative(int value);
    static bool isNonNegative(float value);
    static bool isPositive(int value);
    static bool isPositive(float value);
    static bool inRange(int value, int min, int max);
    static bool inRange(float value, float min, float max);

    // --- Format Validations ---
    static bool isValidID(const std::string& id, char expectedPrefix = '\0');
    static bool isValidDate(const std::string& date);
    static bool isValidPhone(const std::string& phone);
    static bool isValidCNIC(const std::string& cnic);
    static bool isValidName(const std::string& name);

    // --- Date Utilities ---
    static std::string getCurrentDate();
    static int calculateDays(const std::string& start, const std::string& end);

    // --- String Validations ---
    static bool isAlphaOnly(const std::string& str, bool allowSpaces = true);
    static bool isAlphanumeric(const std::string& str);
};

#endif // VALIDATOR_H
