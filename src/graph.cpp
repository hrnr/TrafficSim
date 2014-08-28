#include "graph.h"
#include <boost/graph/graphviz.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <exception>

Graph::CityGraph::CityGraph()
{
	// initialize property mapping
	init_dynamic_property();

	// create tempfile for visualization
	char *tempname = strdup("/tmp/dotXXXXXX");
	mkstemp(tempname);
	dot_temp = tempname;
}

Graph::CityGraph::~CityGraph()
{
	// remove(viz_temp.c_str());
}

void Graph::CityGraph::init_dynamic_property()
{
	// boost dynamic property mapping, used by graphviz functions
	// node properties
	auto node_name = get(&Vertex::name, city_graph);
	dprop.property("node_id", node_name);

	auto node_label = get(&Vertex::label, city_graph);
	dprop.property("label", node_label);

	// edge properties
	auto edge_name = get(&Edge::name, city_graph);
	dprop.property("name", edge_name);

	auto edge_label = get(&Edge::label, city_graph);
	dprop.property("label", edge_label);
}

void Graph::CityGraph::import(std::string dot_file)
{
	// file to import
	std::ifstream dot_stream;
	dot_stream.exceptions(std::ifstream::badbit);
	try {
		dot_stream.open(dot_file);

		// import graphviz
		bool status = boost::read_graphviz(dot_stream, city_graph, dprop);

		if (!status) {
			throw std::runtime_error("Couldn't parse graphviz file.");
		}
	} catch (const std::exception &e) {
		std::cerr << "E: Unable to load " << dot_file << " " << e.what()
				  << std::endl;
	}
}

void Graph::CityGraph::print()
{
	std::cout << "Printing current graph state..." << std::endl;
	std::cout << "Number of edges: " << boost::num_edges(city_graph)
			  << std::endl;
	std::cout << "Number of vertices: " << boost::num_vertices(city_graph)
			  << std::endl;

	std::cout << "\nList of vertices:" << std::endl;
	city_graph_t::vertex_iterator vertex_it, vertex_it_end;
	std::tie(vertex_it, vertex_it_end) = boost::vertices(city_graph);
	for (; vertex_it != vertex_it_end; ++vertex_it) {
		std::cout << "Vertex [" << *vertex_it
				  << "] name: " << city_graph[*vertex_it].name << std::endl;
	}

	std::cout << "\nList of edges:" << std::endl;
	city_graph_t::edge_iterator edge_it, edge_it_end;
	std::tie(edge_it, edge_it_end) = boost::edges(city_graph);
	for (; edge_it != edge_it_end; ++edge_it) {
		std::cout << "Edge [" << *edge_it
				  << "] name: " << city_graph[*edge_it].name << std::endl;
	}
}

std::string Graph::CityGraph::regenerate_dot()
{
	// @todo: regenerate design traits

	// create/update dot tempfile from city_graph
	std::fstream dot_tempfile_stream(dot_temp);
	boost::write_graphviz_dp(dot_tempfile_stream, city_graph, dprop);

	return dot_temp;
}

Graph::CityGraph::vertex_descriptor
Graph::CityGraph::find_node(std::string name)
{
	city_graph_t::vertex_iterator vertex_it, vertex_it_end;
	std::tie(vertex_it, vertex_it_end) = boost::vertices(city_graph);
	for (; vertex_it != vertex_it_end; ++vertex_it) {
		if (name == city_graph[*vertex_it].name) {
			return *vertex_it;
		}
	}
	throw std::runtime_error("Vertex '" + name + "' doesn't exist!");
}

std::list<Graph::CityGraph::edge_descriptor>
Graph::CityGraph::get_route(vertex_descriptor from, vertex_descriptor to)
{
	// output list
	std::list<city_graph_t::edge_descriptor> path(0);

	// create real storage for Dijkstra output
	std::vector<city_graph_t::vertex_descriptor> predecessors(
		boost::num_vertices(city_graph)); // to store route precessors
	std::vector<uint64_t> distances(
		boost::num_vertices(city_graph)); // to store distances

	// named parameters for dijkstra
	auto indexMap = boost::get(boost::vertex_index, city_graph);
	auto weightMap = boost::get(&Edge::weight, city_graph);
	auto predecessorMap =
		boost::make_iterator_property_map(predecessors.begin(), indexMap);
	auto distanceMap =
		boost::make_iterator_property_map(distances.begin(), indexMap);

	// run dijkstra
	boost::dijkstra_shortest_paths(city_graph, from,
								   boost::vertex_index_map(indexMap)
									   .weight_map(weightMap)
									   .predecessor_map(predecessorMap)
									   .distance_map(distanceMap));

	// walk back on predecessor map and get shortest path
	// u (predecessor) -> v
	// if predecessorMap[v] = v then v is source (see docs)
	city_graph_t::vertex_descriptor u = predecessorMap[to];
	city_graph_t::vertex_descriptor v = to;
	for (; v != u; v = u, u = predecessorMap[u]) {
		path.push_front(boost::edge(u, v, city_graph).first);
	}

#ifndef NDEBUG
	// print path found
	std::cout << "Path found: from " << city_graph[from].name << " to "
			  << city_graph[to].name << std::endl;
	std::cout << "	";
	for (auto &edge_p : path) {
		std::cout << " -> " << city_graph[edge_p].name;
	}
	std::cout << std::endl;
#endif

	return path;
}

Graph::CityGraph::Vertex &Graph::CityGraph::
operator[](Graph::CityGraph::vertex_descriptor vertex)
{
	return city_graph[vertex];
}

Graph::CityGraph::Edge &Graph::CityGraph::
operator[](Graph::CityGraph::edge_descriptor edge)
{
	return city_graph[edge];
}