#ifndef SPN_ANALYSIS_HPP
#define SPN_ANALYSIS_HPP

#include <vector>
#include "ReachabilityGraph.hpp"
#include <Eigen/Dense>

struct SPNAnalysisResult {
    Eigen::VectorXd steady_state_probabilities;
    Eigen::VectorXd average_markings;
};

class SPNAnalysis {
public:
    SPNAnalysis(const ReachabilityGraph& graph, int num_transitions);

    SPNAnalysisResult analyze(const std::vector<double>& firing_rates);

private:
    const ReachabilityGraph& graph_;
    int num_transitions_;
};

#endif // SPN_ANALYSIS_HPP