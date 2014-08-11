#include "graph.h"

// default constructor
Graph::CityGraph::CityGraph() {}

void Graph::CityGraph::import()
{
	// property mapping, gv file -> graph_t
	// node name
	boost::property_map<graph_t, boost::vertex_name_t>::type name =
		get(boost::vertex_name, city_graph);
	dprop.property("node_id", name);

	boost::property_map<graph_t, boost::vertex_color_t>::type mass =
		get(boost::vertex_color, city_graph);
	dprop.property("mass", mass);

	boost::property_map<graph_t, boost::edge_weight_t>::type weight =
		get(boost::edge_weight, city_graph);
	dprop.property("weight", weight);

	// Sample graph as an std::istream;
	std::istringstream gvgraph("digraph G \n\
		{\n\
		\n\
		v21->v11;\n\
		v21->v12;\n\
		v21->v13;\n\
		\n\
		v11->v21;\n\
		v21->v11;\n\
		v11->v22;\n\
		v11->v23;\n\
		\n\
		v21->v22;\n\
		v22->v23;\n\
		v23->v21;\n\
		\n\
		v21->v31;\n\
		v21->v32;\n\
		v21->v33;\n\
		\n\
		v32->v41;\n\
		v32->v42;\n\
		v33->v43;\n\
		}");

	bool status = boost::read_graphviz(gvgraph, city_graph, dprop);
}

void Graph::CityGraph::print()
{
	std::cout << "Printing current graph state..." << std::endl;
	std::cout << "Number of edges: " << boost::num_edges(city_graph)
			  << std::endl;
	std::cout << "Number of vertices: " << boost::num_vertices(city_graph)
			  << std::endl;
}