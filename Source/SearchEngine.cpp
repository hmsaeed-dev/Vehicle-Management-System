#include "SearchEngine.h"
#include <algorithm>
#include <iostream>


SearchEngine::SearchEngine(vector<Vehicle*> &f) : fleet(f) {}

vector<Vehicle*> SearchEngine::searchByCategory(char type) {
    vector<Vehicle*> results;
    string targetCat;
    if (type == 'E') targetCat = "Economy";
    else if (type == 'L') targetCat = "Luxury";
    else if (type == 'S') targetCat = "SUV";
    else if (type == 'V') targetCat = "Van/Bus";

    for (Vehicle* v : fleet) {
        if (v->getStatus() != VehicleStatus::Sold && v->getCategory() == targetCat) {
            results.push_back(v);
        }
    }
    return results;
}
