#include "Van.h"

#include <iostream>
#include <iomanip>

using namespace std;

Van::Van(string id, string model, int year, int capacity, float rate)
    : Vehicle(id, model, year, capacity, rate) {}

float Van::calculateCost(int days)
{
    return (getRentalRate() * 1.3f) * days; // Van multiplier
}

// void Van::displayInfo() {
//     cout << "[VAN/BUS]  ID: " << getID()
//          << " | Model: " << getModel()
//          << " | Year: " << getYear()
//          << " | Capacity: " << getCapacity() << " pax"
//          << " | Rate: $" << getRentalRate() << "/day"
//          << " | Status: " << (getAvailable() ? "Available" : "Rented")
//          << endl;
// }


void Van::displayInfo()
{
    cout << "\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| [VAN / BUS CATEGORY]                                 |\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Vehicle ID    :  " << left << setw(36) << getID() << "|\n";
    cout << "| Model         :  " << left << setw(36) << getModel() << "|\n";
    cout << "| Year          :  " << left << setw(36) << getYear() << "|\n";
    cout << "| Capacity      :  " << left << setw(30) << getCapacity() << " Pax |" << "\n";
    cout << "| Daily Rate    :  $" << left << setw(35) << getRentalRate() << "|\n";
    cout << "+------------------------------------------------------+\n";
    cout << "| Status        :  " << left << setw(36) << (getAvailable() ? "AVAILABLE" : "RENTED") << "|\n";
    cout << "+------------------------------------------------------+\n";
}
