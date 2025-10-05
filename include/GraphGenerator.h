#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "PetriNet.h"

class GraphGenerator {
public:
    // Generates a random Petri net with a given number of places and transitions.
    static PetriNet generateRandomPetriNet(int num_places, int num_transitions);

    // Prunes a Petri net to reduce its complexity.
    static PetriNet prunePetriNet(const PetriNet& net);

    // Adds tokens randomly to the places of a Petri net.
    static PetriNet addTokensRandomly(const PetriNet& net);
};

#endif // GRAPH_GENERATOR_H