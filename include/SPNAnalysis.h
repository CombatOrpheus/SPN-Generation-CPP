#ifndef SPN_ANALYSIS_H
#define SPN_ANALYSIS_H

#include "ReachabilityGraph.h"
#include "SPNAnalysisResult.h"
#include <Eigen/Sparse>

class SPNAnalysis {
public:
    // Constructor that takes the reachability graph to be analyzed
    explicit SPNAnalysis(const ReachabilityGraph& graph);

    // Run the steady-state analysis with given firing rates
    SPNAnalysisResult analyze(const Eigen::VectorXd& firing_rates);

private:
    const ReachabilityGraph& graph_;

    // Helper function to build the state transition matrix
    Eigen::SparseMatrix<double> buildStateTransitionMatrix(const Eigen::VectorXd& firing_rates);

    // Helper function to solve for the steady-state probabilities
    Eigen::VectorXd solveForSteadyState(const Eigen::SparseMatrix<double>& matrix);

    // Helper function to compute average markings
    Eigen::VectorXd computeAverageMarkings(const Eigen::VectorXd& steady_state_probs);

    // Helper function to compute marking density
    Eigen::MatrixXd computeMarkingDensity(const Eigen::VectorXd& steady_state_probs);
};

#endif // SPN_ANALYSIS_H