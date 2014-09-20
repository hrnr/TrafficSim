//
//  main.cpp
//  TrafficSim
//
//  Created by Jiri Horner on 11.08.14.
//  Licensed under MIT licence
//

#include "trafficsim.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

/**
 Determines if a file exists.
 @param path Path of the file.
 @return true if the file at @c path exists and is readable.
 */
bool fexists(std::string path)
{
	// use the input stream to check for existence
	std::ifstream ifs(path);
	return ifs.good();
}

int main(int argc, char *const argv[])
{
	/* parse arguments */

	// defaults
	bool visualize = false;
	int simulation_speed = 1;
	std::string map_file;
	std::string vehicles_file;
	std::string dot_visualiser = "xdot -f neato";

	// optarg vars
	int c;
	bool errflg = false;
	extern char *optarg;
	extern int optind, optopt;

	// parse options
	while ((c = getopt(argc, argv, ":st:v:")) != -1) {
		switch (c) {
		case 's': // enable visualisation and search for xdot
			std::cout << "I: Graphical visualisation is ON" << std::endl;
			visualize = true;
			break;
		case 'v': // set dot visualiser
			dot_visualiser = optarg;
			std::cout << "I: Using '" << dot_visualiser
					  << "' as DOT visualiser (default 'xdot -f neato')" << std::endl;
			break;
		case 't':
			try {
				simulation_speed = std::stoi(optarg);
			} catch (const std::invalid_argument &) {
				std::cerr << "E: Argument for -t must be number" << std::endl;
				errflg = true;
			}
			break;
		case ':': // missing operand
			std::cerr << "E: Option -" << (char)optopt << " requires an operand"
					  << std::endl;
			errflg = true;
			break;
		case '?':
			std::cerr << "E: Unrecognized option: -" << (char)optopt
					  << std::endl;
			errflg = true;
		}
	}

	// parse input files arguments
	if (optind + 1 < argc) {
		if (fexists(argv[optind])) {
			map_file = argv[optind];
		} else {
			std::cerr << "E: '" << argv[optind] << "' is not readable"
					  << std::endl;
			errflg = true;
		}

		++optind;
		if (fexists(argv[optind])) {
			vehicles_file = argv[optind];
		} else {
			std::cerr << "E: '" << argv[optind] << "' is not readable"
					  << std::endl;
			errflg = true;
		}
	} else {
		std::cerr << "E: Input files not specified" << std::endl;
		errflg = true;
	}

	// print usage
	if (errflg) {
		std::cerr << "usage: TrafficSim [-s] [-t time_delay] [-v dot_visualiser] <map> <vehicles>"
				  << std::endl;
		return 2;
	}

	// run simulation
	Simulation::TrafficSimulation simulation(map_file, vehicles_file);
	simulation.run(visualize, simulation_speed, dot_visualiser);

	// Graph::CityGraph graph;
	// graph.import("../pokus.dot");
	// graph.print();
	// graph.regenerate_dot();
	// graph.get_route(graph.find_node("v21"), graph.find_node("v23"));
	return 0;
}