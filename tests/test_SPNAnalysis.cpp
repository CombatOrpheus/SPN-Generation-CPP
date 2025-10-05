#include "gtest/gtest.h"
#include "PetriNet.h"
#include "ReachabilityGraph.h"
#include "SPNAnalysis.h"

class SPNAnalysisTest : public ::testing::Test {
protected:
    void SetUp() override {
        // A simple Petri Net: P0 <-> P1 via T0 and T1
        // Initial marking: [1, 0]
        Eigen::MatrixXi matrix(2, 5);
        matrix << 1, 0, 0, 1, 1,
                  0, 1, 1, 0, 0;

        PetriNet net(matrix);
        graph = ReachabilityGraph::generate(net);
    }

    ReachabilityGraph graph;
};

TEST_F(SPNAnalysisTest, AnalyzeSimpleSystem) {
    SPNAnalysis analysis(graph);
    Eigen::VectorXd firing_rates(2);
    firing_rates << 1.0, 2.0; // lambda_0 = 1.0, lambda_1 = 2.0

    SPNAnalysisResult result = analysis.analyze(firing_rates);

    ASSERT_TRUE(result.success);

    // Theoretical results:
    // pi_0 = lambda_1 / (lambda_0 + lambda_1) = 2.0 / 3.0
    // pi_1 = lambda_0 / (lambda_0 + lambda_1) = 1.0 / 3.0
    Eigen::VectorXd expected_probs(2);
    expected_probs << 2.0/3.0, 1.0/3.0;

    // Average markings = M0 * pi_0 + M1 * pi_1
    // = [1, 0] * (2/3) + [0, 1] * (1/3) = [2/3, 1/3]
    Eigen::VectorXd expected_avg_markings(2);
    expected_avg_markings << 2.0/3.0, 1.0/3.0;

    // Check steady-state probabilities
    ASSERT_EQ(result.steady_state_probabilities.size(), 2);
    EXPECT_NEAR(result.steady_state_probabilities(0), expected_probs(0), 1e-6);
    EXPECT_NEAR(result.steady_state_probabilities(1), expected_probs(1), 1e-6);

    // Check average markings
    ASSERT_EQ(result.average_markings.size(), 2);
    EXPECT_NEAR(result.average_markings(0), expected_avg_markings(0), 1e-6);
    EXPECT_NEAR(result.average_markings(1), expected_avg_markings(1), 1e-6);

    // Check total average markings
    EXPECT_NEAR(result.total_average_markings, 1.0, 1e-6);
}