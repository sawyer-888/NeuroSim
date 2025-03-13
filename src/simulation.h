#ifndef SIMULATION_H
#define SIMULATION_H

#include "network.h"

class Simulation {
public:
    Simulation(int num_neurons);
    void run(int steps);
    Network& getNetwork();  // Added this function

private:
    Network network;
};

#endif
