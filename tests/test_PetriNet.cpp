#include "gtest/gtest.h"
#include "PetriNet.hpp"

TEST(PetriNetTest, Constructor) {
    PetriNet net(3, 2);
    EXPECT_EQ(net.get_places(), 3);
    EXPECT_EQ(net.get_transitions(), 2);
    const auto& matrix = net.get_matrix();
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix[0].size(), 5);
}

TEST(PetriNetTest, Setters) {
    PetriNet net(2, 1);
    net.set_marking(0, 1);
    net.set_pre(0, 0, 1);
    net.set_post(1, 0, 1);

    const auto& matrix = net.get_matrix();
    EXPECT_EQ(matrix[0][2], 1); // marking
    EXPECT_EQ(matrix[0][0], 1); // pre
    EXPECT_EQ(matrix[1][1], 1); // post
}

TEST(PetriNetTest, SettersOutOfBounds) {
    PetriNet net(2, 1);
    net.set_marking(2, 1);
    net.set_pre(2, 0, 1);
    net.set_post(1, 1, 1);

    const auto& matrix = net.get_matrix();
    EXPECT_EQ(matrix[0][2], 0);
    EXPECT_EQ(matrix[1][2], 0);
    EXPECT_EQ(matrix[0][0], 0);
    EXPECT_EQ(matrix[1][0], 0);
    EXPECT_EQ(matrix[0][1], 0);
    EXPECT_EQ(matrix[1][1], 0);
}