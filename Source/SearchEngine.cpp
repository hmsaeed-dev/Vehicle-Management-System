#include "SearchEngine.h"
#include <algorithm>
#include <iostream>

/**
 * @brief Constructor taking a reference to the main fleet.
 */

SearchEngine::SearchEngine(vector<Vehicle*>& f) : fleet(f) {}


vector<Vehicle*> SearchEngine::searchByPriceRange(float min, float max)
{
    vector<Vehicle*> results;
    for (Vehicle* v : fleet)
    {
        if (v->getStatus() != VehicleStatus::Sold && v->getRentalRate() >= min && v->getRentalRate() <= max)
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
        if (v->getStatus() != VehicleStatus::Sold && v->getID()[0] == type) {
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
        if (v->getStatus() != VehicleStatus::Sold && v->getYear() >= minYear && v->getYear() <= maxYear)
        {
            results.push_back(v);
        }
    }
    return results;
}

vector<Vehicle*> SearchEngine::smartSearch(char type, float maxPrice, bool onlyAvailable)
{
    vector<Vehicle*> results;
    type = toupper(type);

    for (Vehicle* v : fleet)
    {
        if (v->getStatus() == VehicleStatus::Sold) continue;

        bool matchesType = (type == 'A' || v->getID()[0] == type);
        bool matchesPrice = (v->getRentalRate() <= maxPrice);
        bool matchesAvail = (!onlyAvailable || v->getStatus() == VehicleStatus::Available);

        if (matchesType && matchesPrice && matchesAvail)
        {
            results.push_back(v);
        }
    }
    return results;
}

