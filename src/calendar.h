#ifndef CALENDAR_H
#define CALENDAR_H

#include <map>
#include <list>
#include "simulation.h"

namespace Simulation
{
template <typename SimulationEvent> class Calendar
{
  public:
	/**
	 * @brief Add new event to calendar
	 * @details Add new event, only future events (according to internally
	 *stored time) will be accepted.
	 *
	 * @param time artificial simualtion time
	 * @param event event to add
	 */
	void add_event(sim_time_t time, SimulationEvent event);

	/**
	 * @brief remove all events scheduled for time
	 * @details Removes all events from specified time.
	 *
	 * @param time artificial simulation time
	 */
	void release_events(sim_time_t time);
	std::list<SimulationEvent> get_events(sim_time_t time);
	bool empty();

	/**
	 * @brief Update calendar's time
	 * @details Updates time, before new events won't be accepted.
	 *
	 * @param increment time increment
	 */
	void update_time(uint_fast32_t increment = 1);

  private:
	sim_time_t current_time = 0;
	std::map<sim_time_t, std::list<SimulationEvent>> calendar_map;
};
}

// implementation
#include "calendar.cpp"

#endif