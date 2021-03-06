cmake_minimum_required (VERSION 2.6)

# set default build (current Debug), user can override
# must be before project
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif()

project (TrafficSim)

# c++11 support required
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# we are using boost::graph with graphviz import/export functions
find_package(Boost 1.40 COMPONENTS graph REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(TrafficSim src/main.cpp src/graph.cpp src/vehicle.cpp src/trafficsim.cpp)
target_link_libraries(TrafficSim ${Boost_LIBRARIES})