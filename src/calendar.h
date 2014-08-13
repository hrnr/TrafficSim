#ifndef CALENDAR_H
#define CALENDAR_H

#include <map>
#include <list>
#include "simulation.h"
#include "vehicle.h"

namespace Simulation
{
	class Calendar
	{
	public:
		Calendar();
		~Calendar();
		void add_event(sim_time_t time, Vehicle vehicle);
		/**
		 * @brief remove all events scheduled for time
		 * @details [long description]
		 * 
		 * @param time artificial simulation time
		 */
		void release_time (sim_time_t time);
	private:
		std::map<sim_time_t, std::list<Vehicle>> calendar_map;
	};
}

#endif