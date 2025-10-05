#include "gtest/gtest.h"
#include "PetriNet.h"
#include "ReachabilityGraph.h"
#include "SPNAnalysis.h"
#include "GraphGenerator.h"

TEST(IntegrationTest, FullWorkflow) {
    // 1. Generate a random Petri Net
    PetriNet net = GraphGenerator::generateRandomPetriNet(4, 4); // 4 places, 4 transitions

    // 2. Generate the Reachability Graph
    // Use a high limit for markings to increase the chance of boundedness for the test
    ReachabilityGraph graph = ReachabilityGraph::generate(net, 20, 200);

    // If the graph is unbounded, the test will still pass, as this is a valid outcome.
    // The main goal is to ensure the components work together without crashing.
    if (!graph.isBounded()) {
        SUCCEED() << "Generated an unbounded graph, which is a valid scenario.";
        return;
    }

    // 3. Perform SPN Analysis
    SPNAnalysis analysis(graph);
    Eigen::VectorXd firing_rates = Eigen::VectorXd::Ones(net.getNumTransitions()); // Simple firing rates

    SPNAnalysisResult result = analysis.analyze(firing_rates);

    // We expect the analysis to succeed for a valid, bounded graph.
    ASSERT_TRUE(result.success);

    // Basic sanity checks on the results
    ASSERT_GT(result.steady_state_probabilities.size(), 0);
    ASSERT_GT(result.average_markings.size(), 0);
    EXPECT_NEAR(result.steady_state_probabilities.sum(), 1.0, 1e-6);
}