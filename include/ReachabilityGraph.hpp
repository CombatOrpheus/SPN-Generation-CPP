#ifndef REACHABILITY_GRAPH_HPP
#define REACHABILITY_GRAPH_HPP

#include <vector>
#include <iostream>
#include <utility> // For std::pair

class ReachabilityGraph {
public:
    ReachabilityGraph() = default;

    void add_vertex(const std::vector<int>& marking);
    void add_edge(int from, int to, int transition_index);

    const std::vector<std::vector<int>>& get_vertices() const;
    const std::vector<std::pair<int, int>>& get_edges() const;
    const std::vector<int>& get_arc_transitions() const;

    void print() const;

private:
    std::vector<std::vector<int>> vertices_;
    std::vector<std::pair<int, int>> edges_;
    std::vector<int> arc_transitions_;
};

#endif // REACHABILITY_GRAPH_HPP