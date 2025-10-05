#include "gtest/gtest.h"
#include "PetriNet.h"

class PetriNetTest : public ::testing::Test {
protected:
    void SetUp() override {
        // A simple Petri Net with 2 places and 2 transitions
        // Pre-condition matrix: [[1, 0], [0, 1]]
        // Post-condition matrix: [[0, 1], [1, 0]]
        // Initial marking: [1, 0]
        Eigen::MatrixXi matrix(2, 5);
        matrix << 1, 0, 0, 1, 1,
                  0, 1, 1, 0, 0;

        petriNet = new PetriNet(matrix);
    }

    void TearDown() override {
        delete petriNet;
    }

    PetriNet* petriNet;
};

TEST_F(PetriNetTest, Getters) {
    ASSERT_EQ(petriNet->getNumPlaces(), 2);
    ASSERT_EQ(petriNet->getNumTransitions(), 2);
}

TEST_F(PetriNetTest, PreConditionMatrix) {
    Eigen::MatrixXi expected(2, 2);
    expected << 1, 0,
                0, 1;
    ASSERT_EQ(petriNet->getPreConditionMatrix(), expected);
}

TEST_F(PetriNetTest, PostConditionMatrix) {
    Eigen::MatrixXi expected(2, 2);
    expected << 0, 1,
                1, 0;
    ASSERT_EQ(petriNet->getPostConditionMatrix(), expected);
}

TEST_F(PetriNetTest, ChangeMatrix) {
    Eigen::MatrixXi expected(2, 2);
    expected << -1, 1,
                 1, -1;
    ASSERT_EQ(petriNet->getChangeMatrix(), expected);
}

TEST_F(PetriNetTest, InitialMarking) {
    Eigen::VectorXi expected(2);
    expected << 1, 0;
    ASSERT_EQ(petriNet->getInitialMarking(), expected);
}

TEST_F(PetriNetTest, FullMatrix) {
    Eigen::MatrixXi expected(2, 5);
    expected << 1, 0, 0, 1, 1,
                0, 1, 1, 0, 0;
    ASSERT_EQ(petriNet->getMatrix(), expected);
}