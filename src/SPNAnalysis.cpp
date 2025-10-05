#include "SPNAnalysis.hpp"
#include <iostream>

SPNAnalysis::SPNAnalysis(const ReachabilityGraph& graph, int num_transitions)
    : graph_(graph), num_transitions_(num_transitions) {}

SPNAnalysisResult SPNAnalysis::analyze(const std::vector<double>& firing_rates) {
    const auto& vertices = graph_.get_vertices();
    const auto& edges = graph_.get_edges();
    const auto& arc_transitions = graph_.get_arc_transitions();
    int num_vertices = vertices.size();

    Eigen::MatrixXd state_matrix = Eigen::MatrixXd::Zero(num_vertices, num_vertices);

    for (size_t i = 0; i < edges.size(); ++i) {
        int from = edges[i].first;
        int to = edges[i].second;
        int transition_index = arc_transitions[i];
        double rate = firing_rates[transition_index];

        state_matrix(from, from) -= rate;
        state_matrix(to, from) += rate;
    }

    Eigen::MatrixXd equation_system = state_matrix;
    equation_system.row(num_vertices - 1) = Eigen::VectorXd::Ones(num_vertices);

    Eigen::VectorXd b = Eigen::VectorXd::Zero(num_vertices);
    b(num_vertices - 1) = 1.0;

    Eigen::VectorXd steady_state_probs = equation_system.colPivHouseholderQr().solve(b);

    Eigen::VectorXd avg_markings = Eigen::VectorXd::Zero(vertices[0].size());
    for (int i = 0; i < num_vertices; ++i) {
        for (size_t j = 0; j < vertices[i].size(); ++j) {
            avg_markings(j) += steady_state_probs(i) * vertices[i][j];
        }
    }

    return {steady_state_probs, avg_markings};
}