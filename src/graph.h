#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <string.h>
#include <cstdlib>

#define DOT_VIEWER "xdot"

namespace Graph
{
class CityGraph
{
	// Graph type definition
	// vertices in graph
	struct Node
	{
		// requied properties
		std::string name;

		// design properties
		std::string label;
	};
	// edges in graph
	struct Edge
	{
		// requied properties
		std::string name;
		const uint64_t capacity = 0;
		const uint64_t length = 0;
		uint64_t traffic;
		// weight used for route planning
		uint64_t weight = 1;

		// design properties
		std::string color;
		std::string label;
	};
	// adjacency_list-based graph
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
								  Node, Edge> city_graph_t;

  public:
	CityGraph();
	~CityGraph();
	void import(std::string dot_file);
	void print();
	/**
	 * @brief Generates temporary dot file
	 * @details [long description]
	 * @return path to temporary dot file
	 */
	std::string regenerate_dot();
	city_graph_t::vertex_descriptor find_node(std::string name);
	std::list<city_graph_t::edge_descriptor> get_route(city_graph_t::vertex_descriptor from, city_graph_t::vertex_descriptor to);

  private:
	// main graph
	city_graph_t city_graph;
	// graph dynamic properties used for mapping
	boost::dynamic_properties dprop;
	// visualization tempfile (dot file)
	std::string dot_temp;

	// init dynamic property mapping used for graphviz read/write
	void init_dynamic_property();
};
}

#endif /* GRAPH_H */