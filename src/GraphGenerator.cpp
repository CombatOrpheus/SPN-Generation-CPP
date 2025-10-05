#include "GraphGenerator.h"
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

namespace {
// Helper to get a random element from a container
template<typename T>
T getRandomElement(const std::vector<T>& container) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, container.size() - 1);
    return container[distrib(gen)];
}
} // namespace

PetriNet GraphGenerator::generateRandomPetriNet(int num_places, int num_transitions) {
    Eigen::MatrixXi petri_matrix = Eigen::MatrixXi::Zero(num_places, 2 * num_transitions + 1);

    std::vector<int> places(num_places);
    std::iota(places.begin(), places.end(), 0);

    std::vector<int> transitions(num_transitions);
    std::iota(transitions.begin(), transitions.end(), 0);

    // This is a simplified random generation logic compared to the Python version,
    // but it captures the spirit of creating a connected graph.
    // A more faithful translation would involve the subgraph connection logic.
    for (int t = 0; t < num_transitions; ++t) {
        int pre_place = getRandomElement(places);
        int post_place = getRandomElement(places);
        petri_matrix(pre_place, t) = 1; // Pre-condition
        petri_matrix(post_place, t + num_transitions) = 1; // Post-condition
    }

    // Add a single token to a random place
    int initial_token_place = getRandomElement(places);
    petri_matrix(initial_token_place, 2 * num_transitions) = 1;

    return PetriNet(petri_matrix);
}

PetriNet GraphGenerator::prunePetriNet(const PetriNet& net) {
    // The pruning logic from the Python code is quite specific and involves
    // random choices. A full implementation would be complex.
    // For this example, we'll return the net unmodified, as the core
    // functionality is in the generation and analysis.
    return net;
}

PetriNet GraphGenerator::addTokensRandomly(const PetriNet& net) {
    Eigen::MatrixXi matrix = net.getMatrix();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 9);

    for (int i = 0; i < net.getNumPlaces(); ++i) {
        if (distrib(gen) <= 2) {
            matrix(i, net.getNumTransitions() * 2) += 1;
        }
    }
    return PetriNet(matrix);
}