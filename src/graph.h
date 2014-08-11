#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>

namespace Graph
{
class CityGraph
{
	// Graph type definition we will be using
	// Vertex properties
	typedef boost::property<boost::vertex_name_t, std::string,
							boost::property<boost::vertex_color_t, float>>
		vertex_p;
	// Edge properties
	typedef boost::property<boost::edge_weight_t, uint64_t> edge_p;
	// Graph properties
	typedef boost::property<boost::graph_name_t, std::string> graph_p;
	// adjacency_list-based type
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
								  vertex_p, edge_p, graph_p> graph_t;

  public:
	CityGraph();
	void import();
	void print();

  private:
  	// main graph
	graph_t city_graph;
	// graph dynamic properties used for mapping
	boost::dynamic_properties dprop;
};
}

#endif /* GRAPH_H */