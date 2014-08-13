#ifndef TRAFFICSIM_H
#define TRAFFICSIM_H

#include "graph.h"
#include "calendar.h"
#include "vehicle.h"

namespace Simulation
{
class TrafficSimulation
{
	friend class Vehicle;

  public:
	TrafficSimulation(std::string graph_in, std::string vehicles_in);
	~TrafficSimulation();
	void run();
	void show_visualisation();

  private:
	void load_vehicles(std::string vehicles_file);

	// city graph stored for simulation
	Graph::CityGraph city_map;
	// calendar stored for simulation
	Calendar sim_calendar;
};
}

#endif
