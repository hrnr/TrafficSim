#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <string>
#include <list>

#define DOT_VIEWER "xdot"

namespace Graph
{
class CityGraph
{

  public:
	// vertices in graph
	struct Vertex
	{
		// requied properties
		std::string name;

		// design properties
		std::string label;
	};
	// edges in graph
	struct Edge
	{
		// required properties
		std::string name;
		// how many vehicles can be there for fluent traffic
		uint64_t capacity = 30;
		// should be lenght in meters in real world
		uint64_t length = 500;
		// how many norm vehicles in there
		uint64_t traffic = 0;
		// max speed in meters/second
		uint64_t max_speed = 180;
		// weight used for route planning
		double weight = 1;
		

		// design properties
		std::string color;
		std::string label;
	};

  private:
	// private graph type definition
	// adjacency_list-based graph
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
								  Vertex, Edge> city_graph_t;

  public:
	// public exposed types
	typedef city_graph_t::vertex_descriptor vertex_descriptor;
	typedef city_graph_t::edge_descriptor edge_descriptor;

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
	vertex_descriptor find_node(std::string name);
	std::list<edge_descriptor> get_route(vertex_descriptor from,
										 vertex_descriptor to);
	Vertex& operator[](vertex_descriptor vertex);
	Edge& operator[](edge_descriptor edge);

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