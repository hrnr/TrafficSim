/*
* this file implements templates and is only valid when included in calendar.h
*/
#ifdef CALENDAR_H

#ifndef NDEBUG
#include <iostream>
#endif

namespace Simulation
{
template <typename SimulationEvent>
void Calendar<SimulationEvent>::add_event(sim_time_t time,
										  SimulationEvent event)
{
	if (time >= current_time) {
		calendar_map[time].push_back(event);

#ifndef NDEBUG
		std::cout << "I: Added event on time: " << time << std::endl;
#endif
	}
}

template <typename SimulationEvent>
void Calendar<SimulationEvent>::release_events(sim_time_t time)
{
	calendar_map.erase(time);
}

template <typename SimulationEvent>
std::list<SimulationEvent>
Calendar<SimulationEvent>::get_events(sim_time_t time)
{
	auto it = calendar_map.find(time);
	if (it == calendar_map.end()) {
		return std::list<SimulationEvent>();
	} else {
		return it->second;
	}
}

template <typename SimulationEvent> bool Calendar<SimulationEvent>::empty()
{
	return calendar_map.empty();
}

template <typename SimulationEvent>
void Calendar<SimulationEvent>::update_time(uint_fast32_t increment)
{
	current_time += increment;
}
}

#endif