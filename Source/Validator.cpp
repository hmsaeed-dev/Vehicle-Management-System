#include "Validator.h"
#include <regex>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

bool Validator::isNonNegative(int value) { return value >= 0; }
bool Validator::isNonNegative(float value) { return value >= 0.0f; }
bool Validator::isPositive(int value) { return value > 0; }
bool Validator::isPositive(float value) { return value > 0.0f; }

bool Validator::inRange(int value, int min, int max) { return value >= min && value <= max; }
bool Validator::inRange(float value, float min, float max) { return value >= min && value <= max; }

bool Validator::isValidID(const string& id)
{
    if (id.empty()) return false;

    // Strictly Numeric Check: All characters must be digits
    for (char c : id) {
        if (!isdigit(c)) return false;
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

bool Validator::isValidCNIC(const string& cnic)
{
    // Format: XXXXX-XXXXXXX-X
    const regex pattern(R"(^\d{5}-\d{7}-\d{1}$)");
    return regex_match(cnic, pattern);
}

bool Validator::isValidName(const string& name)
{
    if (name.length() < 3) return false;
    return isAlphaOnly(name, true);
}

string Validator::getCurrentDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "-"
       << setw(2) << 1 + ltm->tm_mon << "-"
       << 1900 + ltm->tm_year;
    return ss.str();
}

int Validator::calculateDays(const string& start, const string& end)
{
    auto parseDate = [](const string& date) {
        tm t = {};
        stringstream ss(date);
        char dash;
        ss >> t.tm_mday >> dash >> t.tm_mon >> dash >> t.tm_year;
        t.tm_mon -= 1;
        t.tm_year -= 1900;
        return t;
    };

    tm tm1 = parseDate(start);
    tm tm2 = parseDate(end);

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    const int seconds_per_day = 60 * 60 * 24;
    double difference = difftime(time2, time1) / seconds_per_day;

    int days = static_cast<int>(difference);
    return (days < 1) ? 1 : days; // Minimum 1 day billing
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
