#include "SPNAnalysis.h"
#include <Eigen/IterativeLinearSolvers>
#include <iostream>

SPNAnalysis::SPNAnalysis(const ReachabilityGraph& graph) : graph_(graph) {}

SPNAnalysisResult SPNAnalysis::analyze(const Eigen::VectorXd& firing_rates) {
    SPNAnalysisResult result;
    result.success = false;

    if (!graph_.isBounded() || graph_.getVertices().empty()) {
        return result;
    }

    Eigen::SparseMatrix<double> state_matrix = buildStateTransitionMatrix(firing_rates);
    Eigen::VectorXd steady_state_probs = solveForSteadyState(state_matrix);

    if (steady_state_probs.size() == 0) {
        return result;
    }

    result.steady_state_probabilities = steady_state_probs;
    result.average_markings = computeAverageMarkings(steady_state_probs);
    result.marking_density = computeMarkingDensity(steady_state_probs);
    result.total_average_markings = result.average_markings.sum();
    result.firing_rates = firing_rates;
    result.success = true;

    return result;
}

Eigen::SparseMatrix<double> SPNAnalysis::buildStateTransitionMatrix(const Eigen::VectorXd& firing_rates) {
    int num_vertices = graph_.getVertices().size();
    Eigen::SparseMatrix<double> state_matrix(num_vertices, num_vertices);
    std::vector<Eigen::Triplet<double>> triplets;

    Eigen::VectorXd diagonal_coeffs(num_vertices);
    diagonal_coeffs.setZero();

    for (const auto& edge : graph_.getEdges()) {
        double rate = firing_rates(edge.transition_idx);
        if (edge.from_vertex_idx != edge.to_vertex_idx) {
            triplets.emplace_back(edge.to_vertex_idx, edge.from_vertex_idx, rate);
            diagonal_coeffs(edge.from_vertex_idx) -= rate;
        }
    }

    for (int i = 0; i < num_vertices; ++i) {
        triplets.emplace_back(i, i, diagonal_coeffs(i));
    }

    // The last row is for the normalization constraint (sum of probabilities = 1)
    Eigen::SparseMatrix<double> final_matrix(num_vertices + 1, num_vertices);
    final_matrix.setFromTriplets(triplets.begin(), triplets.end());

    for (int i = 0; i < num_vertices; ++i) {
        final_matrix.insert(num_vertices, i) = 1.0;
    }

    return final_matrix;
}

Eigen::VectorXd SPNAnalysis::solveForSteadyState(const Eigen::SparseMatrix<double>& matrix) {
    int num_vertices = matrix.cols();
    Eigen::VectorXd b = Eigen::VectorXd::Zero(num_vertices + 1);
    b(num_vertices) = 1.0;

    // Use a least-squares solver for the rectangular system
    Eigen::LeastSquaresConjugateGradient<Eigen::SparseMatrix<double>> solver;
    solver.compute(matrix);
    Eigen::VectorXd x = solver.solve(b);

    if (solver.info() != Eigen::Success) {
        return Eigen::VectorXd(); // Return empty vector on failure
    }

    // Normalize probabilities to ensure they sum to 1 and are non-negative
    x = x.cwiseMax(0);
    double sum = x.sum();
    if (sum > 1e-9) {
        x /= sum;
    }

    return x;
}

Eigen::VectorXd SPNAnalysis::computeAverageMarkings(const Eigen::VectorXd& steady_state_probs) {
    int num_places = graph_.getVertices()[0].size();
    Eigen::VectorXd avg_markings = Eigen::VectorXd::Zero(num_places);

    for (size_t i = 0; i < graph_.getVertices().size(); ++i) {
        avg_markings += graph_.getVertices()[i].cast<double>() * steady_state_probs(i);
    }
    return avg_markings;
}

Eigen::MatrixXd SPNAnalysis::computeMarkingDensity(const Eigen::VectorXd& steady_state_probs) {
    // This is a more complex calculation that depends on the range of token values.
    // For now, we return an empty matrix as a placeholder.
    // A full implementation would require finding the max token count across all places
    // and then building the density matrix.
    return Eigen::MatrixXd();
}