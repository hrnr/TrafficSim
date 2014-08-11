//
//  main.cpp
//  TrafficSim
//
//  Created by Jiri Horner on 11.08.14.
//  Licensed under MIT licence
//

#include "graph.h"

int main(int argc, char const *argv[])
{
	Graph::CityGraph graph;
	graph.import();
	graph.print();
	return 0;
}