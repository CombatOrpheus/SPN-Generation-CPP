#include "gtest/gtest.h"
#include "ReachabilityGraph.hpp"

TEST(ReachabilityGraphTest, Constructor) {
    ReachabilityGraph graph;
    EXPECT_EQ(graph.get_vertices().size(), 0);
    EXPECT_EQ(graph.get_edges().size(), 0);
    EXPECT_EQ(graph.get_arc_transitions().size(), 0);
}

TEST(ReachabilityGraphTest, AddVertex) {
    ReachabilityGraph graph;
    graph.add_vertex({1, 0, 0});
    graph.add_vertex({0, 1, 0});

    const auto& vertices = graph.get_vertices();
    ASSERT_EQ(vertices.size(), 2);
    EXPECT_EQ(vertices[0], std::vector<int>({1, 0, 0}));
    EXPECT_EQ(vertices[1], std::vector<int>({0, 1, 0}));
}

TEST(ReachabilityGraphTest, AddEdge) {
    ReachabilityGraph graph;
    graph.add_edge(0, 1, 0);
    graph.add_edge(1, 2, 1);

    const auto& edges = graph.get_edges();
    const auto& transitions = graph.get_arc_transitions();

    ASSERT_EQ(edges.size(), 2);
    EXPECT_EQ(edges[0], std::make_pair(0, 1));
    EXPECT_EQ(edges[1], std::make_pair(1, 2));

    ASSERT_EQ(transitions.size(), 2);
    EXPECT_EQ(transitions[0], 0);
    EXPECT_EQ(transitions[1], 1);
}