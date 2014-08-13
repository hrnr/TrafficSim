#ifndef VEHICLE_H
#define VEHICLE_H

#include "simulation.h"
#include "graph.h"

namespace Simulation
{
	class Vehicle
	{
	public:
		Vehicle(std::string from, std::string to, sim_time_t start_time, std::string name = "unnamed_vehicle");
		~Vehicle();
		void update_status(sim_time_t current_time);
	};
}

#endif