#include "SearchEngine.h"
#include <algorithm>
#include <iostream>

/**
 * @brief Constructor taking a reference to the main fleet.
 */

SearchEngine::SearchEngine(vector<Vehicle*>& f) : fleet(f) {}

// Helper for case-insensitive comparison
bool equalsIgnoreCase(string a, string b)
{
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    transform(b.begin(), b.end(), b.begin(), ::tolower);
    // Changed to find for partial matches
    return a.find(b) != string::npos;
}

vector<Vehicle*> SearchEngine::searchByName(string name)
{
    vector<Vehicle*> results;
    for (Vehicle* v : fleet)
    {
        if (equalsIgnoreCase(v->getModel(), name))
        {
            results.push_back(v);
        }
    }
    return results;
}


vector<Vehicle*> SearchEngine::searchByPriceRange(float min, float max)
{
    vector<Vehicle*> results;
    for (Vehicle* v : fleet)
    {
        if (v->getRentalRate() >= min && v->getRentalRate() <= max)
        {
            results.push_back(v);
        }
    }
    return results;
}


vector<Vehicle*> SearchEngine::searchByCategory(char type) {
    vector<Vehicle*> results;
    type = toupper(type);
    for (Vehicle* v : fleet) {
        if (v->getID()[0] == type) {
            results.push_back(v);
        }
    }
    return results;
}

vector<Vehicle*> SearchEngine::searchByAvailability() {
    vector<Vehicle*> results;
    for (Vehicle* v : fleet) {
        if (v->getStatus() == VehicleStatus::Available) {
            results.push_back(v);
        }
    }
    return results;
}

vector<Vehicle*> SearchEngine::searchByYearRange(int minYear, int maxYear)
{
    vector<Vehicle*> results;
    for (Vehicle* v : fleet)
    {
        if (v->getYear() >= minYear && v->getYear() <= maxYear)
        {
            results.push_back(v);
        }
    }
    return results;
}
