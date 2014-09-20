#ifndef TRAFFICSIM_H
#define TRAFFICSIM_H

#include "graph.h"
#include "calendar.h"
#include <vector>

namespace Simulation
{
class TrafficSimulation
{
  public:
	TrafficSimulation(std::string graph_in, std::string vehicles_in);
	void run(bool show_visualisation, int simulation_speed,
			 std::string dot_visualiser);

  private:
	class Vehicle; // defined in vehicle.h

	void import_vehicles(std::string vehicles_file);
	void show_visualisation(std::string dot_visualiser);

	// city graph stored for simulation
	Graph::CityGraph city_map;
	// calendar stored for simulation
	Calendar<Vehicle> sim_calendar;
	// vehicles in simulation
	std::vector<Vehicle> vehicles;
};
}

#include "vehicle.h"

#endif
