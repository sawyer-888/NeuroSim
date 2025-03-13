#include "neuron.h"
#include "synapse.h"
#include <iostream>
#include <vector>
#include <algorithm>  // For std::min, std::for_each
#include <utility>    // For std::exchange
#include <execution>  // For parallel execution (future)

Neuron::Neuron(int id) : id(id), activation(0.0) {
    synapses.reserve(10);
}

void Neuron::receiveSignal(double signal) {
    activation = std::min(activation + signal, 2.0); 
}

void Neuron::update() {
    if (activation <= 1.0) return; 

#ifdef DEBUG
    std::cout << "Neuron " << id << " fired!\n";
#endif

    activation = std::exchange(activation, 0.0);

    std::for_each(std::execution::par_unseq, synapses.begin(), synapses.end(), 
                  [](Synapse* synapse) { synapse->propagate(); });
}

void Neuron::addSynapse(Synapse* synapse) {
    synapses.push_back(synapse);  
}

double Neuron::getActivation() const {
    return activation;
}

void Neuron::optimizeMemory() {
    synapses.clear();       
    synapses.shrink_to_fit(); 
}
