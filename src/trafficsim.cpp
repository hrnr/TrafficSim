#include "trafficsim.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include "nonstd.h"

namespace Simulation
{
TrafficSimulation::TrafficSimulation(std::string graph_in,
									 std::string vehicles_in)
{
	// import graph
	city_map.import(graph_in);

	// import vehicles
	import_vehicles(vehicles_in);
}

void TrafficSimulation::run(const bool show_visualisation)
{
	// show visualisation
	if (show_visualisation) {
		TrafficSimulation::show_visualisation();
	}

	sim_time_t current_time = 0;
	// event loop
	while (!sim_calendar.empty()) {
		// get vehicles for current time
		auto events = sim_calendar.get_events(current_time);

		// update all planned vehicles
		for (Vehicle &v : events) {
			v.update_status(current_time);
		}

		// update visualisation
		city_map.regenerate_dot();

		// update time
		++current_time;
	}
}

void TrafficSimulation::import_vehicles(std::string vehicles_file)
{
	// load input file
	std::ifstream infile(vehicles_file);

	// create regex for line matching
	std::regex r(
		"(.*)\\w*:\\w*(.*):\\w*(.*)\\w*->\\w*(.*)\\w*[?(?:(.*)=(.*);)*]?",
		std::regex::ECMAScript);
	std::cmatch regex_result;

	// read and match lines
	std::string str;

	for (uint_fast32_t line_num = 1; getline(infile, str); ++line_num) {
		// if nothing was matched -> bad syntax
		if (!std::regex_match(str.c_str(), regex_result, r)) {
			std::cerr << "E: Line " << line_num << " of input file \""
					  << vehicles_file << "\" is not valid. See documentation "
										  "for correct syntax. Skipping..."
					  << std::endl;
			continue;
		}

		// create vehicle; parse starttime, name, from and to
		Vehicle veh(*this, regex_result[2], regex_result[3],
					stoull(regex_result[0]), regex_result[1]);

		// parse optional properties
		for (int i = 4; i < regex_result.size(); i += 2) {
			switch (nonstd::hash(regex_result[i].str().c_str())) {
			case nonstd::hash("traffic_increase_caused"):
				veh.traffic_increase_caused = stof(regex_result[i + 1]);
				break;
			case nonstd::hash("max_speed"):
				veh.max_speed = stoul(regex_result[i + 1]);
				break;
			}
		}

		// add vehicle to simulation
		vehicles.push_back(veh);

		std::cout << "I: Vehicle " << veh.name << " loaded for simulation";
	}

	infile.close();
}

void TrafficSimulation::show_visualisation()
{
	// generates graph visualisation
	std::string dot_temp = city_map.regenerate_dot();
	// show it to user
	system((std::string(DOT_VIEWER) + " " + dot_temp + "> /dev/null 2>&1 &")
			   .c_str());
}
}