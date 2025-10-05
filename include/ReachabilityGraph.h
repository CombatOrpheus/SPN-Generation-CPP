#ifndef REACHABILITY_GRAPH_H
#define REACHABILITY_GRAPH_H

#include "PetriNet.h"
#include <vector>
#include <Eigen/Dense>

class ReachabilityGraph {
public:
    // A vertex is a marking, represented as a vector of tokens
    using Vertex = Eigen::VectorXi;

    // An edge represents a transition between two markings (vertices)
    struct Edge {
        int from_vertex_idx;
        int to_vertex_idx;
        int transition_idx;
    };

    // --- Static Factory Method ---
    // Generates the reachability graph from a given Petri net.
    static ReachabilityGraph generate(const PetriNet& net, int place_upper_limit = 10, int max_markings_to_explore = 500);

    // --- Getters ---
    const std::vector<Vertex>& getVertices() const { return vertices_; }
    const std::vector<Edge>& getEdges() const { return edges_; }
    int getNumTransitions() const { return num_transitions_; }
    bool isBounded() const { return is_bounded_; }

    // --- Public Members ---
    // These are populated by the `generate` method.
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
    int num_transitions_;
    bool is_bounded_;

    // --- Constructor ---
    ReachabilityGraph() : num_transitions_(0), is_bounded_(true) {}
};

#endif // REACHABILITY_GRAPH_H