#include "PetriNet.h"

PetriNet::PetriNet(const Eigen::MatrixXi& matrix) : petri_matrix_(matrix) {}

const Eigen::MatrixXi& PetriNet::getMatrix() const {
    return petri_matrix_;
}

Eigen::MatrixXi PetriNet::getPreConditionMatrix() const {
    return petri_matrix_.leftCols(getNumTransitions());
}

Eigen::MatrixXi PetriNet::getPostConditionMatrix() const {
    return petri_matrix_.block(0, getNumTransitions(), getNumPlaces(), getNumTransitions());
}

Eigen::MatrixXi PetriNet::getChangeMatrix() const {
    return getPostConditionMatrix() - getPreConditionMatrix();
}

Eigen::VectorXi PetriNet::getInitialMarking() const {
    return petri_matrix_.rightCols(1);
}

int PetriNet::getNumPlaces() const {
    return petri_matrix_.rows();
}

int PetriNet::getNumTransitions() const {
    return (petri_matrix_.cols() - 1) / 2;
}