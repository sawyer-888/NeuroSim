#include "neuron.h"
#include "synapse.h"
#include <iostream>

Neuron::Neuron(int id) : id(id), activation(0.0) {}

void Neuron::receiveSignal(double signal) {
    activation += signal;
}

void Neuron::update() {
    if (activation > 1.0) {
        std::cout << "Neuron " << id << " fired!\n";
        activation = 0.0;
        
        for (auto synapse : synapses) {
            synapse->propagate();
        }
    }
}

void Neuron::addSynapse(Synapse* synapse) {
    synapses.push_back(synapse);
}

double Neuron::getActivation() const {
    return activation;
}
