#include "neuron.h"
#include "synapse.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> // For std::min

Neuron::Neuron(int id) : id(id), activation(0.0) {
    synapses.reserve(10); 
}

void Neuron::receiveSignal(double signal) {
    activation += signal;
    activation = std::min(activation, 2.0); 
}

void Neuron::update() {
    if (activation <= 1.0) return; 
#ifdef DEBUG
    std::cout << "Neuron " << id << " fired!\n";
#endif

    activation = 0.0;  

    for (auto& synapse : synapses) {
        synapse->propagate();
    }
}

void Neuron::addSynapse(std::unique_ptr<Synapse> synapse) {
    synapses.push_back(std::move(synapse));
}

double Neuron::getActivation() const {
    return activation;
}

void Neuron::optimizeMemory() {
    synapses.shrink_to_fit();  
}
