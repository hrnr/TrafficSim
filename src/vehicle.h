#ifndef VEHICLE_H
#define VEHICLE_H

#include "simulation.h"
#include "trafficsim.h"
#include "graph.h"
#include <list>

namespace Simulation
{
class TrafficSimulation::Vehicle
{
  public:
	Vehicle(const TrafficSimulation &simulation, const std::string &from,
			const std::string &to, const sim_time_t &start_time,
			const std::string &name = "unnamed_vehicle");
	void update_status(const sim_time_t &current_time);

	// vehicle properties
	std::string name;
	float traffic_increase_caused = 1;
	// max speed in meters per second
	uint_fast32_t max_speed = 22;
  private:
	// simulation to live in
	TrafficSimulation sim;

	// vehicle status
	enum struct Status { READY, WAITING, ONROUTE, FINISHED };
	Status status;
	std::list<Graph::CityGraph::edge_descriptor> route_remaining;
	Graph::CityGraph::edge_descriptor current_position;
	sim_time_t next_position_at;

	sim_time_t
	get_travelling_time(const Graph::CityGraph::edge_descriptor &edge);
};
}

#endif