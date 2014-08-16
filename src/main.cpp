//
//  main.cpp
//  TrafficSim
//
//  Created by Jiri Horner on 11.08.14.
//  Licensed under MIT licence
//

#include "trafficsim.h"

int main(int argc, char const *argv[])
{
	// Graph::CityGraph graph;
	// graph.import("../pokus.dot");
	// graph.print();
	// graph.regenerate_dot();
	// graph.get_route(graph.find_node("v21"), graph.find_node("v23"));
	Simulation::TrafficSimulation simulation ("../pokus.dot", "../vehicles.in");
	simulation.run(true);
	return 0;
}