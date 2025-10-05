#include "GraphGenerator.hpp"
#include <vector>
#include <map>
#include <queue>

namespace GraphGenerator {

std::vector<int> get_initial_marking(const PetriNet& net) {
    std::vector<int> initial_marking;
    const auto& matrix = net.get_matrix();
    int num_places = net.get_places();
    int marking_col = 2 * net.get_transitions();
    for (int i = 0; i < num_places; ++i) {
        initial_marking.push_back(matrix[i][marking_col]);
    }
    return initial_marking;
}

std::vector<int> get_enabled_transitions(const PetriNet& net, const std::vector<int>& marking) {
    std::vector<int> enabled;
    const auto& matrix = net.get_matrix();
    int num_transitions = net.get_transitions();
    int num_places = net.get_places();

    for (int t = 0; t < num_transitions; ++t) {
        bool is_enabled = true;
        for (int p = 0; p < num_places; ++p) {
            if (marking[p] < matrix[p][t]) {
                is_enabled = false;
                break;
            }
        }
        if (is_enabled) {
            enabled.push_back(t);
        }
    }
    return enabled;
}

std::vector<int> fire_transition(const PetriNet& net, const std::vector<int>& marking, int transition) {
    std::vector<int> new_marking = marking;
    const auto& matrix = net.get_matrix();
    int num_places = net.get_places();
    int num_transitions = net.get_transitions();

    for (int p = 0; p < num_places; ++p) {
        new_marking[p] -= matrix[p][transition];
        new_marking[p] += matrix[p][num_transitions + transition];
    }
    return new_marking;
}

ReachabilityGraph generate_reachability_graph(
    const PetriNet& net,
    int place_upper_bound,
    int max_markings_to_explore) {

    ReachabilityGraph graph;
    std::vector<int> initial_marking = get_initial_marking(net);

    std::map<std::vector<int>, int> visited_markings;
    std::queue<std::vector<int>> q;

    graph.add_vertex(initial_marking);
    visited_markings[initial_marking] = 0;
    q.push(initial_marking);

    int markings_explored = 1;

    while (!q.empty() && markings_explored < max_markings_to_explore) {
        std::vector<int> current_marking = q.front();
        q.pop();
        int current_marking_index = visited_markings[current_marking];

        std::vector<int> enabled_transitions = get_enabled_transitions(net, current_marking);

        for (int t : enabled_transitions) {
            std::vector<int> new_marking = fire_transition(net, current_marking, t);

            bool bounded = true;
            for(int tokens : new_marking) {
                if (tokens > place_upper_bound) {
                    bounded = false;
                    break;
                }
            }
            if (!bounded) continue;

            if (visited_markings.find(new_marking) == visited_markings.end()) {
                int new_marking_index = graph.get_vertices().size();
                graph.add_vertex(new_marking);
                visited_markings[new_marking] = new_marking_index;
                q.push(new_marking);
                graph.add_edge(current_marking_index, new_marking_index, t);
                markings_explored++;
            } else {
                int existing_marking_index = visited_markings[new_marking];
                graph.add_edge(current_marking_index, existing_marking_index, t);
            }
        }
    }

    return graph;
}

} // namespace GraphGenerator