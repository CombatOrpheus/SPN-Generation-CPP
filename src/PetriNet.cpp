#include "PetriNet.hpp"

PetriNet::PetriNet(int places, int transitions)
    : places_(places), transitions_(transitions) {
    matrix_.resize(places, std::vector<int>(2 * transitions + 1, 0));
}

int PetriNet::get_places() const {
    return places_;
}

int PetriNet::get_transitions() const {
    return transitions_;
}

const std::vector<std::vector<int>>& PetriNet::get_matrix() const {
    return matrix_;
}

void PetriNet::set_marking(int place, int tokens) {
    if (place >= 0 && place < places_) {
        matrix_[place][2 * transitions_] = tokens;
    }
}

void PetriNet::set_pre(int place, int transition, int weight) {
    if (place >= 0 && place < places_ && transition >= 0 && transition < transitions_) {
        matrix_[place][transition] = weight;
    }
}

void PetriNet::set_post(int place, int transition, int weight) {
    if (place >= 0 && place < places_ && transition >= 0 && transition < transitions_) {
        matrix_[place][transitions_ + transition] = weight;
    }
}

void PetriNet::print() const {
    for (const auto& row : matrix_) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}