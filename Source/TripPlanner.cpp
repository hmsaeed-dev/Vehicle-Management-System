#include "TripPlanner.h"
#include "Vehicle.h"

#include <iostream>
#include <iomanip>

/**
 * @brief Plans a trip and recommends best vehicles based on budget and capacity.
 */


void TripPlanner::planTrip(string source, string destination, float distance, float budget, int passengers, const vector<Vehicle*>& fleet)
{
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                TRIP PLANNER RECOMMENDATIONS              |\n";
    cout << "+----------------------------------------------------------+\n";

    // Summary of User Input
    cout << "  > Route        : " << source << " to " << destination << "\n";
    cout << "  > Distance     : " << distance << " km\n";
    cout << "  > Requirements : Budget $" << budget << " | " << passengers << " Pax\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "  MATCHING VEHICLES FOUND:\n\n";

    int count = 0;

    for (Vehicle* v : fleet)
    {
        // Filter: Available AND Capacity >= Passengers AND (Cost estimate for 1 day <= Budget)
        if (v->getStatus() == VehicleStatus::Available && v->getCapacity() >= passengers && v->getRentalRate() <= budget)
        {
            cout << "  [" << count + 1 << "] "
                << left << setw(18) << v->getModel()
                << " (ID: " << setw(6) << v->getID() << ")"
                << " Rate: $" << setw(5) << v->getRentalRate() << "/Day\n";
            count++;
        }
    }

    if (count == 0)
    {
        cout << "  [!] No vehicles match your budget/capacity criteria.\n";
    }
    else
    {
        cout << "\n  [SYSTEM] Found " << count << " suitable option(s).\n";
    }

    cout << "+----------------------------------------------------------+\n";
}
