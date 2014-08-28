#include "vehicle.h"
#include <algorithm>
#include <iostream>

namespace Simulation
{
TrafficSimulation::Vehicle::Vehicle(TrafficSimulation &simulation,
									const std::string &from,
									const std::string &to,
									const sim_time_t &start_time,
									const std::string &name)
	: name(name), sim(simulation)
{
	// plan a route
	route_remaining = sim.city_map.get_route(sim.city_map.find_node(from),
											 sim.city_map.find_node(to));

	// plan vehicle to start time
	next_position_at = start_time;
	sim.sim_calendar.add_event(start_time, *this);

	// init position to nothing
	status = Status::READY;
}
void TrafficSimulation::Vehicle::update_status(const sim_time_t &current_time)
{
	// this must be called only on proper times
	if (current_time != next_position_at) {
		throw "E: Simulation time mismatch";
	}

	// decrease traffic on edge we are leaving
	// set as no longer waiting
	if (status == Status::ONROUTE) {
		sim.city_map[current_position].traffic -= traffic_increase_caused;
	}

	// are we finished?
	if (route_remaining.empty()) {
		status = Status::FINISHED;
		std::cout << "S [" << current_time << "]: Vehicle " << name
				  << " finished" << std::endl;
		return;
	}

	// set vehicle to next edge
	status = Status::ONROUTE;
	current_position = route_remaining.front();
	route_remaining.pop_front();
	std::cout << "S [" << current_time << "]: Vehicle " << name << " is now on "
			  << sim.city_map[current_position].name << std::endl;

	// increase traffic on next edge
	sim.city_map[current_position].traffic += traffic_increase_caused;

	// compute time on next edge
	next_position_at = current_time + get_travelling_time(current_position);

	// plan next update
	sim.sim_calendar.add_event(next_position_at, *this);
}
sim_time_t TrafficSimulation::Vehicle::get_travelling_time(
	const Graph::CityGraph::edge_descriptor &edge)
{
	double length = sim.city_map[edge].length;
	double ratio = std::max(1.0, (double)sim.city_map[edge].traffic /
									 (sim.city_map[edge].capacity + 1));
	double speed = std::min(max_speed, sim.city_map[edge].max_speed);

	return (length / speed) * ratio;
}
}