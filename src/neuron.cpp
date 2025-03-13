#include "neuron.h"
#include "synapse.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>  // For std::clamp, std::for_each
#include <execution>  // For parallel execution
#include <utility>    // For std::exchange

constexpr int MAX_SYNAPSES = 16;

Neuron::Neuron(int id) : id(id), activation(0.0) {
    synapses.reserve(MAX_SYNAPSES);  
}

void Neuron::receiveSignal(double signal) {
    activation = std::clamp(activation + signal, 0.0, 2.0);  
}

void Neuron::update() {
    if (activation <= 1.0) return;  

#ifdef DEBUG
    std::cout << "Neuron " << id << " fired!\n";
#endif

    activation = std::exchange(activation, 0.0);  

    
    #pragma omp simd
    for (size_t i = 0; i < synapses.size(); ++i) {
        synapses[i]->propagate();
    }
}

void Neuron::addSynapse(Synapse* synapse) {
    if (synapses.size() < MAX_SYNAPSES) { 
        synapses.push_back(synapse);
    }
}

double Neuron::getActivation() const {
    return activation;
}

void Neuron::optimizeMemory() {
    synapses.clear();        
    synapses.shrink_to_fit(); 
}
