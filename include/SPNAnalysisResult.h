#ifndef SPN_ANALYSIS_RESULT_H
#define SPN_ANALYSIS_RESULT_H

#include <Eigen/Dense>

struct SPNAnalysisResult {
    // Steady-state probabilities for each marking
    Eigen::VectorXd steady_state_probabilities;

    // Average number of tokens in each place
    Eigen::VectorXd average_markings;

    // Marking density matrix
    Eigen::MatrixXd marking_density;

    // Firing rates of the transitions
    Eigen::VectorXd firing_rates;

    // Total average number of tokens in the net
    double total_average_markings;

    // Flag indicating if the analysis was successful
    bool success;
};

#endif // SPN_ANALYSIS_RESULT_H