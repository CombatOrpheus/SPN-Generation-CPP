#include "PetriNet.h"
#include "ReachabilityGraph.h"
#include "GraphGenerator.h"
#include "SPNAnalysis.h"
#include <iostream>

void printVector(const Eigen::VectorXd& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec(i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1. Generate a random Petri Net
    std::cout << "--- 1. Generating Random Petri Net ---" << std::endl;
    PetriNet randomNet = GraphGenerator::generateRandomPetriNet(3, 3); // 3 places, 3 transitions
    std::cout << "Generated Petri Net Matrix:" << std::endl;
    std::cout << randomNet.getMatrix() << std::endl << std::endl;

    // 2. Generate the Reachability Graph
    std::cout << "--- 2. Generating Reachability Graph ---" << std::endl;
    ReachabilityGraph graph = ReachabilityGraph::generate(randomNet, 10, 100);

    if (!graph.isBounded()) {
        std::cout << "The generated Petri Net is unbounded. Analysis cannot proceed." << std::endl;
        return 1;
    }
    std::cout << "Reachability Graph Generated:" << std::endl;
    std::cout << "  - Vertices: " << graph.getVertices().size() << std::endl;
    std::cout << "  - Edges: " << graph.getEdges().size() << std::endl << std::endl;

    // 3. Perform SPN Analysis
    std::cout << "--- 3. Performing SPN Analysis ---" << std::endl;
    SPNAnalysis analysis(graph);

    // Generate random firing rates for the transitions
    Eigen::VectorXd firing_rates = Eigen::VectorXd::Random(randomNet.getNumTransitions());
    firing_rates = (firing_rates.array() + 1.0) * 5.0; // Make them positive and in a reasonable range

    std::cout << "Using Firing Rates: ";
    printVector(firing_rates);
    std::cout << std::endl;

    SPNAnalysisResult result = analysis.analyze(firing_rates);

    if (result.success) {
        std::cout << "Analysis Successful!" << std::endl;
        std::cout << "Steady-State Probabilities:" << std::endl;
        printVector(result.steady_state_probabilities);
        std::cout << "\nAverage Markings:" << std::endl;
        printVector(result.average_markings);
    } else {
        std::cout << "SPN Analysis failed." << std::endl;
    }

    return 0;
}