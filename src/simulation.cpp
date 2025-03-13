#include <cstdlib>  
#include "simulation.h"

Simulation::Simulation(int num_neurons) : network(num_neurons) {}

void Simulation::run(int steps) {
    for (int i = 0; i < steps; i++) {
        if (i % 10 == 0) {
            network.stimulateNeuron(rand() % 100, 1.0); 
        }
        network.update();
    }
}
