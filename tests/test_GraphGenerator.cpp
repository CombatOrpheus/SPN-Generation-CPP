#include "gtest/gtest.h"
#include "GraphGenerator.hpp"
#include "PetriNet.hpp"
#include "ReachabilityGraph.hpp"

TEST(GraphGeneratorTest, SimpleGraph) {
    PetriNet net(2, 1);
    net.set_marking(0, 1); // Initial marking: [1, 0]
    net.set_pre(0, 0, 1);   // Transition 0: P0 -> T0
    net.set_post(1, 0, 1);  // Transition 0: T0 -> P1

    ReachabilityGraph graph = GraphGenerator::generate_reachability_graph(net);

    const auto& vertices = graph.get_vertices();
    const auto& edges = graph.get_edges();

    ASSERT_EQ(vertices.size(), 2);
    EXPECT_EQ(vertices[0], std::vector<int>({1, 0}));
    EXPECT_EQ(vertices[1], std::vector<int>({0, 1}));

    ASSERT_EQ(edges.size(), 1);
    EXPECT_EQ(edges[0], std::make_pair(0, 1));
}

TEST(GraphGeneratorTest, Loop) {
    PetriNet net(2, 2);
    net.set_marking(0, 1); // Initial marking: [1, 0]
    net.set_pre(0, 0, 1);
    net.set_post(1, 0, 1);
    net.set_pre(1, 1, 1);
    net.set_post(0, 1, 1);

    ReachabilityGraph graph = GraphGenerator::generate_reachability_graph(net);

    const auto& vertices = graph.get_vertices();
    const auto& edges = graph.get_edges();
    const auto& arc_transitions = graph.get_arc_transitions();

    ASSERT_EQ(vertices.size(), 2);
    EXPECT_EQ(vertices[0], std::vector<int>({1, 0}));
    EXPECT_EQ(vertices[1], std::vector<int>({0, 1}));

    ASSERT_EQ(edges.size(), 2);
    EXPECT_EQ(edges[0], std::make_pair(0, 1));
    EXPECT_EQ(arc_transitions[0], 0);
    EXPECT_EQ(edges[1], std::make_pair(1, 0));
    EXPECT_EQ(arc_transitions[1], 1);
}