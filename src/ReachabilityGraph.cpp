#include "ReachabilityGraph.h"
#include <deque>
#include <map>
#include <vector>

// Helper function to find all enabled transitions and the resulting new markings
static std::pair<std::vector<ReachabilityGraph::Vertex>, std::vector<int>>
getEnabledTransitions(const Eigen::MatrixXi& pre_matrix, const Eigen::MatrixXi& change_matrix, const ReachabilityGraph::Vertex& current_marking) {
    std::vector<ReachabilityGraph::Vertex> new_markings;
    std::vector<int> enabled_transitions_indices;
    int num_transitions = pre_matrix.cols();

    for (int t = 0; t < num_transitions; ++t) {
        bool enabled = true;
        for (int p = 0; p < pre_matrix.rows(); ++p) {
            if (current_marking(p) < pre_matrix(p, t)) {
                enabled = false;
                break;
            }
        }

        if (enabled) {
            enabled_transitions_indices.push_back(t);
            new_markings.push_back(current_marking + change_matrix.col(t));
        }
    }
    return {new_markings, enabled_transitions_indices};
}


ReachabilityGraph ReachabilityGraph::generate(const PetriNet& net, int place_upper_limit, int max_markings_to_explore) {
    ReachabilityGraph graph;
    graph.num_transitions_ = net.getNumTransitions();

    Eigen::MatrixXi pre_matrix = net.getPreConditionMatrix();
    Eigen::MatrixXi change_matrix = net.getChangeMatrix();
    Vertex initial_marking = net.getInitialMarking();

    std::deque<int> processing_queue;
    std::map<std::vector<int>, int> explored_markings_dict;

    // Initial state
    graph.vertices_.push_back(initial_marking);
    std::vector<int> initial_marking_vec(initial_marking.data(), initial_marking.data() + initial_marking.size());
    explored_markings_dict[initial_marking_vec] = 0;
    processing_queue.push_back(0);

    while (!processing_queue.empty()) {
        int current_marking_idx = processing_queue.front();
        processing_queue.pop_front();

        if (graph.vertices_.size() >= max_markings_to_explore) {
            graph.is_bounded_ = false;
            break;
        }

        Vertex current_marking = graph.vertices_[current_marking_idx];

        auto [new_markings, enabled_transitions] = getEnabledTransitions(pre_matrix, change_matrix, current_marking);

        for (size_t i = 0; i < new_markings.size(); ++i) {
            const auto& new_marking = new_markings[i];
            int transition_idx = enabled_transitions[i];

            if ((new_marking.array() > place_upper_limit).any()) {
                graph.is_bounded_ = false;
                break;
            }

            std::vector<int> new_marking_vec(new_marking.data(), new_marking.data() + new_marking.size());
            auto it = explored_markings_dict.find(new_marking_vec);

            int new_marking_idx;
            if (it == explored_markings_dict.end()) {
                new_marking_idx = graph.vertices_.size();
                graph.vertices_.push_back(new_marking);
                explored_markings_dict[new_marking_vec] = new_marking_idx;
                processing_queue.push_back(new_marking_idx);
            } else {
                new_marking_idx = it->second;
            }
            graph.edges_.push_back({current_marking_idx, new_marking_idx, transition_idx});
        }
        if (!graph.is_bounded_) {
            break;
        }
    }

    return graph;
}