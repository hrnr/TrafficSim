#include "trafficsim.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <thread>
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

void TrafficSimulation::run(const bool show_visualisation,
							const int simulation_speed,
							const std::string dot_visualiser)
{
	// show visualisation
	if (show_visualisation) {
		TrafficSimulation::show_visualisation(dot_visualiser);
	}

	sim_time_t current_time = 0;

	// event loop
	while (!sim_calendar.empty()) {

#ifndef NDEBUG
		std::cerr << "I: time is now: " << current_time << std::endl;
#endif

		// get vehicles for current time
		auto events = sim_calendar.get_events(current_time);

		// update all planned vehicles
		for (Vehicle &v : events) {
			v.update_status(current_time);
		}

		// remove prcessed events from calendar
		sim_calendar.release_events(current_time);

		// update visualisation
		city_map.regenerate_dot();

		// update time
		++current_time;

		// update calendar time
		sim_calendar.update_time(1);

		// adjust simulation speed if visualizing
		if (show_visualisation) {
			std::this_thread::sleep_for(std::chrono::seconds(simulation_speed));
		}
	}

	// finished
	std::cout << "S [" << current_time - 1 << "]: Simulation finished"
			  << std::endl;
}

void TrafficSimulation::import_vehicles(std::string vehicles_file)
{
	// load input file
	std::ifstream infile;
	infile.exceptions(std::ifstream::badbit);
	try {
		infile.open(vehicles_file);

		// read and match lines
		std::string line;

		for (uint_fast32_t line_num = 1; std::getline(infile, line);
			 ++line_num) {
			// split by fields
			std::vector<std::string> fields = nonstd::split(line, ':');

			// 4 fields are required (time, name, from, to)
			if (fields.size() < 4) {
				std::cerr << "E: Line " << line_num << " of input file \""
						  << vehicles_file
						  << "\" is not valid. See documentation "
							 "for correct syntax. Skipping..." << std::endl;
				continue;
			}

#ifndef NDEBUG
			std::cout << "Fields:" << std::endl;
			for (auto &f : fields) {
				std::cout << f << std::endl;
			}
			std::cout << "Matched vehicle on line " << line_num << std::endl
					  << "name: " << fields[1] << std::endl
					  << "from: " << fields[2] << std::endl
					  << "to: " << fields[3] << std::endl
					  << "starttime: " << fields[0] << std::endl;
#endif

			// create vehicle; parse starttime, name, from and to
			try {
				Vehicle veh(*this, fields[2], fields[3], stoull(fields[0]),
							fields[1]);

				// parse optional properties
				for (int i = 4; i < fields.size(); ++i) {
					// split property field by =
					std::vector<std::string> property =
						nonstd::split(fields[i], '=');

					// assign property
					switch (nonstd::hash(property[0].c_str())) {
					case nonstd::hash("traffic_increase_caused"):
						veh.traffic_increase_caused = stof(property[1]);
						break;
					case nonstd::hash("max_speed"):
						veh.max_speed = stoul(property[1]);
						break;
					}
				}

				// add vehicle to simulation
				vehicles.push_back(veh);

				std::cout << "I: Vehicle " << veh.name
						  << " loaded for simulation" << std::endl;
			}
			// vehicle construction errors
			catch (const std::runtime_error &e) {
				std::cerr << "E: " << vehicles_file << ":" << line_num
						  << " Vehicle on line " << line_num
						  << "could'n be loaded for simulation. " << e.what()
						  << std::endl;
			}
		}
	}
	// input file errors
	catch (const std::ifstream::failure &e) {
		std::cerr << "E: Couldn't read file '" << vehicles_file << " "
				  << e.what() << std::endl;
	}
}

void TrafficSimulation::show_visualisation(std::string dot_visualiser)
{
	// generates graph visualisation
	std::string dot_temp = city_map.regenerate_dot();
	// show it to user
	system((dot_visualiser + " " + dot_temp + "> /dev/null 2>&1 &").c_str());
}
}