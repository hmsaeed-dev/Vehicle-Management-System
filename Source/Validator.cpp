#include "Validator.h"
#include <regex>
#include <algorithm>

using namespace std;

bool Validator::isNonNegative(int value) { return value >= 0; }
bool Validator::isNonNegative(float value) { return value >= 0.0f; }
bool Validator::isPositive(int value) { return value > 0; }
bool Validator::isPositive(float value) { return value > 0.0f; }

bool Validator::inRange(int value, int min, int max) { return value >= min && value <= max; }
bool Validator::inRange(float value, float min, float max) { return value >= min && value <= max; }

bool Validator::isValidID(const string& id, char expectedPrefix)
{
    if (id.empty()) return false;
    if (expectedPrefix != '\0' && id[0] != expectedPrefix) return false;
    
    // Simple ID check: starts with letter, followed by digits
    if (!isalpha(id[0])) return false;
    for (size_t i = 1; i < id.length(); ++i) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

bool Validator::isValidDate(const string& date)
{
    // Format: DD-MM-YYYY
    const regex pattern(R"(^(\d{2})-(\d{2})-(\d{4})$)");
    smatch match;
    if (!regex_match(date, match, pattern)) return false;

    int day = stoi(match[1].str());
    int month = stoi(match[2].str());
    int year = stoi(match[3].str());

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 2000 || year > 2100) return false;

    return true;
}

bool Validator::isValidPhone(const string& phone)
{
    // Format: 03XX-XXXXXXX or +92-XXX-XXXXXXX
    const regex pattern(R"(^(\+92|0)\d{2,3}-?\d{7}$)");
    return regex_match(phone, pattern);
}

bool Validator::isAlphaOnly(const string& str, bool allowSpaces)
{
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalpha(c) && !(allowSpaces && isspace(c))) return false;
    }
    return true;
}

bool Validator::isAlphanumeric(const string& str)
{
    if (str.empty()) return false;
    return all_of(str.begin(), str.end(), [](unsigned char c) { return isalnum(c); });
}
