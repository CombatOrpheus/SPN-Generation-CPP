#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include "PetriNet.hpp"
#include "ReachabilityGraph.hpp"
#include <map>
#include <queue>

namespace GraphGenerator {

ReachabilityGraph generate_reachability_graph(
    const PetriNet& net,
    int place_upper_bound = 10,
    int max_markings_to_explore = 500
);

} // namespace GraphGenerator

#endif // GRAPH_GENERATOR_HPP