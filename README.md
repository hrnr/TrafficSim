#TrafficSim

##About
TrafficSim is simple traffic simulator created as university project. It simulates vehicle movement in network graph. Features:

* importing network graph in DOT format
* visualisation using [Graphviz](http://www.graphviz.org) ([xdot](https://github.com/jrfonseca/xdot.py) recommended)
* non-uniform roads, non-uniform vehicles

##Building
This project is written in standard C++11. It uses POSIX and Boost Graph Library. It should build fine on all POSIX systems, including mac. Windows are not supported (although it should work fine with cygwin - link it with cygwin1.dll). Compilation tested with `boost 1.55` and both `gcc 4.9` and `clang 3.5`. Project uses [cmake](http://www.cmake.org/) as build system.

0. get sources

	```
	git clone https://github.com/hrnr/TrafficSim.git
	```

1. get [boost graph library](http://www.boost.org/doc/libs/1_56_0/libs/graph/doc/), it is in repositories for many linux distros. On debian systems just install `libboost-graph-dev`.

2. compile project with cmake as usual

	```
	cd TrafficSim/
	mkdir build && cd build
	cmake ..
	make
	```

##Invocation
```
usage: TrafficSim [-s] [-t time_delay] [-v dot_visualiser] <map> <vehicles>
```

###Options
* `-s`	enable visualisation [default: disabled]
* `-t` time_delay	set how long 1 artificial simulation time unit lasts in seconds. This enables real-time simulation. This applies only if -s is set. [default: 1]
* `-v` dot_visualiser	set visualiser engine for graphviz DOT files [default: `xdot -f neato`]

###Input files
Simulation is configured mostly by input files.

**`<map>`** is Graphviz ([DOT language](http://www.graphviz.org/doc/info/lang.html)) file, which describes map for simulation. Supported properties for nodes: *shape*, *pos* (position); for edges: *name*, *len* (length, default 500), *max_speed* (default 180), *capacity* (default 30), *color*. See [map example](examples/map.dot).

**`<vehicles>`** is custom /etc/passwd-like config file for vehicles in simulation. It contains one vehicle per line in following format:
```
start_time:vehicle_name:from:to:_property1_=value:_property2_=value ...
```
Fields 1-4 are mandatory, `:` character is forbiden in fields. Supported properties are *traffic_increase_caused* (default: 1) and *max_speed* (default: 22). See [vehicles example](examples/vehicles.in).

For generating this file simple [helper script](vehicles_helper.sh) is provided.

###Visualisation
External viewer for dot files are required for visualisation. [xdot](https://github.com/jrfonseca/xdot.py) is recommended. If xdot is in your `PATH` visualisation should work out of the box, otherwise run TrafficSim with `-v path/to/xdot -f *graphviz_engine*`. You can adjust visualisation speed with `-t` option; eg.
```
TrafficSim -t 2 -sv 'path/to/xdot' /path/to/map /path/to/vehicles_file
```
