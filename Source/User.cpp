#include "User.h"

User::User(string id, string username, string name, string cnic, string password)
    : userID(id), username(username), name(name), cnic(cnic), password(password) {}


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

string User::getCNIC() const {
    return cnic;
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

// We should also check the username along with the password
