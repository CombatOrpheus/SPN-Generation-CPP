#include "PetriNet.hpp"
#include "ReachabilityGraph.hpp"
#include "GraphGenerator.hpp"
#include "SPNAnalysis.hpp"
#include <iostream>
#include <vector>

int main() {
    // 1. Create a Petri Net
    std::cout << "--- 1. Creating Petri Net ---" << std::endl;
    PetriNet net(2, 2);
    net.set_marking(0, 1); // Initial marking: [1, 0]

    // Transition 0: P0 -> T0 -> P1
    net.set_pre(0, 0, 1);
    net.set_post(1, 0, 1);

    // Transition 1: P1 -> T1 -> P0
    net.set_pre(1, 1, 1);
    net.set_post(0, 1, 1);

    std::cout << "Petri Net Matrix:" << std::endl;
    net.print();
    std::cout << std::endl;

    // 2. Generate the Reachability Graph
    std::cout << "--- 2. Generating Reachability Graph ---" << std::endl;
    ReachabilityGraph graph = GraphGenerator::generate_reachability_graph(net);
    graph.print();
    std::cout << std::endl;

    // 3. Perform SPN Analysis
    std::cout << "--- 3. Performing SPN Analysis ---" << std::endl;
    SPNAnalysis analysis(graph, net.get_transitions());
    std::vector<double> firing_rates = {1.0, 2.0}; // Firing rates for T0 and T1

    std::cout << "Firing rates: ";
    for(double rate : firing_rates) {
        std::cout << rate << " ";
    }
    std::cout << std::endl;

    SPNAnalysisResult result = analysis.analyze(firing_rates);

    std::cout << "\nSteady-State Probabilities:" << std::endl;
    std::cout << result.steady_state_probabilities << std::endl;

    std::cout << "\nAverage Markings:" << std::endl;
    std::cout << result.average_markings << std::endl;

    return 0;
}