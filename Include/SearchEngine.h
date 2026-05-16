#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include "Vehicle.h"

using namespace std;

/**
 * @class SearchEngine
 * @brief Provides advanced filtering capabilities for the vehicle fleet.
 * Demonstrates Function Overloading.
 */
class SearchEngine {
private:
    vector<Vehicle*>& fleet; // Reference to the main vehicle list

public:
    // Constructor
    SearchEngine(vector<Vehicle*>& f);

    // Overloaded search methods
    vector<Vehicle*> searchByPriceRange(float min, float max);
    vector<Vehicle*> searchByCategory(char type);
    vector<Vehicle*> searchByAvailability();
    vector<Vehicle*> searchByYearRange(int minYear, int maxYear);
    
    // Multi-criteria search
    vector<Vehicle*> smartSearch(char type, float maxPrice, bool onlyAvailable);
};

#endif // SEARCH_ENGINE_H
