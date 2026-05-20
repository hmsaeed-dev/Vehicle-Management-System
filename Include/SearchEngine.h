#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include "Vehicle.h"

using namespace std;

/**
 * @class SearchEngine
 * @brief Provides filtering capabilities for the vehicle fleet.
 */
class SearchEngine {
private:
    vector<Vehicle*>& fleet; // Reference to the main vehicle list

public:
    // Constructor
    SearchEngine(vector<Vehicle*>& f);

    // Search methods
    vector<Vehicle*> searchByCategory(char type);
};

#endif // SEARCH_ENGINE_H
