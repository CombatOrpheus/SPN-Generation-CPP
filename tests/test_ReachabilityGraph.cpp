#include "gtest/gtest.h"
#include "PetriNet.h"
#include "ReachabilityGraph.h"

TEST(ReachabilityGraphTest, GenerateBoundedGraph) {
    // A simple Petri Net: P0 -> T0 -> P1
    // Initial marking: [1, 0]
    Eigen::MatrixXi matrix(2, 5);
    matrix << 1, 0, 0, 1, 1,
              0, 1, 1, 0, 0;
    PetriNet net(matrix);

    ReachabilityGraph graph = ReachabilityGraph::generate(net);

    ASSERT_TRUE(graph.isBounded());
    ASSERT_EQ(graph.getVertices().size(), 2);
    ASSERT_EQ(graph.getEdges().size(), 2);

    // Vertices (Markings)
    Eigen::VectorXi marking0(2);
    marking0 << 1, 0;
    Eigen::VectorXi marking1(2);
    marking1 << 0, 1;
    ASSERT_EQ(graph.getVertices()[0], marking0);
    ASSERT_EQ(graph.getVertices()[1], marking1);

    // Edges
    const auto& edges = graph.getEdges();
    // Edge 0: M0 -> M1 via T0
    ASSERT_EQ(edges[0].from_vertex_idx, 0);
    ASSERT_EQ(edges[0].to_vertex_idx, 1);
    ASSERT_EQ(edges[0].transition_idx, 0);
    // Edge 1: M1 -> M0 via T1
    ASSERT_EQ(edges[1].from_vertex_idx, 1);
    ASSERT_EQ(edges[1].to_vertex_idx, 0);
    ASSERT_EQ(edges[1].transition_idx, 1);
}

TEST(ReachabilityGraphTest, GenerateUnboundedGraph) {
    // An unbounded Petri Net: T0 -> P0
    // Initial marking: [1]
    Eigen::MatrixXi matrix(1, 3);
    matrix << 0, 1, 1;
    PetriNet net(matrix);

    ReachabilityGraph graph = ReachabilityGraph::generate(net, 5, 10); // place_upper_limit=5

    ASSERT_FALSE(graph.isBounded());
}