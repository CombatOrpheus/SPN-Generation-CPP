#include "ReachabilityGraph.hpp"

void ReachabilityGraph::add_vertex(const std::vector<int>& marking) {
    vertices_.push_back(marking);
}

void ReachabilityGraph::add_edge(int from, int to, int transition_index) {
    edges_.emplace_back(from, to);
    arc_transitions_.push_back(transition_index);
}

const std::vector<std::vector<int>>& ReachabilityGraph::get_vertices() const {
    return vertices_;
}

const std::vector<std::pair<int, int>>& ReachabilityGraph::get_edges() const {
    return edges_;
}

const std::vector<int>& ReachabilityGraph::get_arc_transitions() const {
    return arc_transitions_;
}

void ReachabilityGraph::print() const {
    std::cout << "Vertices:" << std::endl;
    for (size_t i = 0; i < vertices_.size(); ++i) {
        std::cout << i << ": [ ";
        for (int token : vertices_[i]) {
            std::cout << token << " ";
        }
        std::cout << "]" << std::endl;
    }

    std::cout << "\nEdges (from -> to, transition):" << std::endl;
    for (size_t i = 0; i < edges_.size(); ++i) {
        std::cout << edges_[i].first << " -> " << edges_[i].second
                  << " (T" << arc_transitions_[i] << ")" << std::endl;
    }
}