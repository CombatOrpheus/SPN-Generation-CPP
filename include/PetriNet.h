#ifndef PETRI_NET_H
#define PETRI_NET_H

#include <Eigen/Dense>

class PetriNet {
public:
    // Constructor that takes an existing Eigen::MatrixXi
    explicit PetriNet(const Eigen::MatrixXi& matrix);

    // Get the full Petri net matrix
    const Eigen::MatrixXi& getMatrix() const;

    // Get the pre-condition matrix (slice of the full matrix)
    Eigen::MatrixXi getPreConditionMatrix() const;

    // Get the post-condition matrix (slice of the full matrix)
    Eigen::MatrixXi getPostConditionMatrix() const;

    // Get the change matrix (Post - Pre)
    Eigen::MatrixXi getChangeMatrix() const;

    // Get the initial marking vector (last column of the full matrix)
    Eigen::VectorXi getInitialMarking() const;

    // Get the number of places
    int getNumPlaces() const;

    // Get the number of transitions
    int getNumTransitions() const;

private:
    Eigen::MatrixXi petri_matrix_;
};

#endif // PETRI_NET_H