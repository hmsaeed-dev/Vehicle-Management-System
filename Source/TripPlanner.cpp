#include "TripPlanner.h"
#include "Vehicle.h"
#include "Colors.h"
#include "Constants.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

/**
 * @brief Plans a trip and recommends best vehicles based on budget and capacity.
 */


void TripPlanner::planTrip(string source, string destination, float distance, float budget, int passengers, const vector<Vehicle*>& fleet)
{
    cout << Color::BOLD << Color::YELLOW;
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                TRIP PLANNER RECOMMENDATIONS              |\n";
    cout << "+----------------------------------------------------------+\n"<< Color::RESET;

    // Summary of User Input
    cout << "  > Route        : " << source << " to " << destination << "\n";
    cout << "  > Distance     : " << distance << " km\n";
    cout << "  > Requirements : Budget " << Pricing::CURRENCY << budget << " | " << passengers << " Pax\n";
    cout << Color::BOLD << Color::YELLOW;
    cout << "+----------------------------------------------------------+\n" << Color::RESET;

    // 1. Filter and Collect Matching Vehicles
    vector<Vehicle*> matches;
    for (Vehicle* v : fleet)
    {
        // Filter: Available AND Capacity >= Passengers AND (Cost estimate for 1 day <= Budget)
        if (v->getStatus() == VehicleStatus::Available && v->getCapacity() >= passengers && v->getRentalRate() <= budget)
        {
            matches.push_back(v);
        }
    }

    // 2. Sort Matches by Rental Rate (Ascending)
    sort
    (
        matches.begin(), matches.end(), [](Vehicle* a, Vehicle* b)
        {
            return a->getRentalRate() < b->getRentalRate();
        }
    );

    // 3. Display Sorted Results
    if (matches.empty())
    {
        cout << Color::ERR << "  [!] No vehicles match your criteria." << Color::RESET << "\n";
        cout << "  Tip: Try increasing your budget or reducing passenger count.\n";
    }
    else
    {
        cout << "  " << Color::CYAN << left << setw(20) << "VEHICLE MODEL" << setw(12) << "ID" << "DAILY RATE" << Color::RESET << "\n";
        cout << Color::BOLD << Color::YELLOW;
        cout << "+----------------------------------------------------------+\n" << Color::RESET;

        for (Vehicle* v : matches)
        {
            cout << "  "
                << left << setw(20) << v->getModel()
                << " [" << setw(6) << v->getID() << "]"
                << "  " << Pricing::CURRENCY << setw(8) << fixed << setprecision(2) << v->getRentalRate() << "\n";
        }
        cout << "\n  " << Color::SUCCESS << "[SYSTEM] Found " << matches.size() << " suitable options [Sorted by Price]." << Color::RESET << "\n";
    }
    cout << Color::BOLD << Color::YELLOW;
    cout << "+----------------------------------------------------------+\n" << Color::RESET;
}
