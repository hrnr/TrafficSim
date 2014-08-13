#include "trafficsim.h"

void Simulation::TrafficSimulation::show_visualisation()
{
	// generates graph visualisation
	std::string dot_temp = city_map.regenerate_dot();
	// show it to user
	system((std::string(DOT_VIEWER) + " " + dot_temp + "> /dev/null 2>&1 &").c_str());
}
