#ifndef TRIP_PLANNER_H
#define TRIP_PLANNER_H

#include <string>
#include <vector>
#include "Vehicle.h"

using namespace std;

/**
 * @class TripPlanner
 * @brief Helps customers plan trips and choose suitable vehicles.
 */
class TripPlanner
{
    public:

    void planTrip(string source, string destination, float distance, float budget, int passengers, const vector<Vehicle*>& fleet);
};

#endif // TRIP_PLANNER_H
