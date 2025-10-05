#include "gtest/gtest.h"
#include "SPNAnalysis.hpp"
#include "ReachabilityGraph.hpp"

TEST(SPNAnalysisTest, SimpleAnalysis) {
    ReachabilityGraph graph;
    graph.add_vertex({1, 0});
    graph.add_vertex({0, 1});
    graph.add_edge(0, 1, 0);

    SPNAnalysis analysis(graph, 1);
    std::vector<double> firing_rates = {1.0};
    SPNAnalysisResult result = analysis.analyze(firing_rates);

    // For a simple two-state system with one transition, the steady state
    // is not well-defined in this formulation, but we can check the dimensions.
    EXPECT_EQ(result.steady_state_probabilities.size(), 2);
    EXPECT_EQ(result.average_markings.size(), 2);
}

TEST(SPNAnalysisTest, ReversibleSystem) {
    ReachabilityGraph graph;
    graph.add_vertex({1, 0}); // State 0
    graph.add_vertex({0, 1}); // State 1
    graph.add_edge(0, 1, 0); // T0: State 0 -> State 1
    graph.add_edge(1, 0, 1); // T1: State 1 -> State 0

    SPNAnalysis analysis(graph, 2);
    std::vector<double> firing_rates = {1.0, 1.0}; // rates for T0 and T1
    SPNAnalysisResult result = analysis.analyze(firing_rates);

    ASSERT_EQ(result.steady_state_probabilities.size(), 2);
    EXPECT_NEAR(result.steady_state_probabilities[0], 0.5, 1e-9);
    EXPECT_NEAR(result.steady_state_probabilities[1], 0.5, 1e-9);

    ASSERT_EQ(result.average_markings.size(), 2);
    EXPECT_NEAR(result.average_markings[0], 0.5, 1e-9);
    EXPECT_NEAR(result.average_markings[1], 0.5, 1e-9);
}