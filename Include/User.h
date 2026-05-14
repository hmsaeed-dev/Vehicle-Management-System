#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

/**
* @class User
* @brief Abstract base class for all system users.
*/

class User {
private:
    string userID;   // Unique User ID
    string username; // Login Username
    string name;     // Full name
    string phone;    // Contact number
    string password; // Login password

public:
    // Constructor
    User(string id, string username, string name, string phone, string password);

    // Virtual destructor for safe cleanup
    virtual ~User();

    // Getters
    string getID() const;
    string getUsername() const;
    string getName() const;
    string getPhone() const;
    string getPassword() const;

    // Authentication
    bool authenticate(string inputPassword) const;

    // Pure Virtual Function (Polymorphism - role-based menus)
    virtual void showMenu() = 0;
};

#endif // USER_H
