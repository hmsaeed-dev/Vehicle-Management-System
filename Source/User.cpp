#include "User.h"

/**
 * @brief Constructor for the User base class.
 */
User::User(string id, string username, string name, string phone, string password) 
    : userID(id), username(username), name(name), phone(phone), password(password) {}

/**
 * @brief Virtual destructor for polymorphic cleanup.
 */
User::~User() {}

// --- Getters ---

string User::getID() const {
    return userID;
}

string User::getUsername() const {
    return username;
}

string User::getName() const {
    return name;
}

string User::getPhone() const {
    return phone;
}

string User::getPassword() const {
    return password;
}

/**
 * @brief Checks if the provided password matches the stored one.
 */
bool User::authenticate(string inputPassword) const {
    return password == inputPassword;
}
