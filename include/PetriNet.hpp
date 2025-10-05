#ifndef PETRI_NET_HPP
#define PETRI_NET_HPP

#include <vector>
#include <iostream>

class PetriNet {
public:
    PetriNet(int places, int transitions);

    int get_places() const;
    int get_transitions() const;
    const std::vector<std::vector<int>>& get_matrix() const;

    void set_marking(int place, int tokens);
    void set_pre(int place, int transition, int weight);
    void set_post(int place, int transition, int weight);

    void print() const;

private:
    int places_;
    int transitions_;
    std::vector<std::vector<int>> matrix_;
};

#endif // PETRI_NET_HPP