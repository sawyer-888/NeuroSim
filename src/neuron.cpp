#include "neuron.h"
#include "synapse.h"
#include <iostream>
#include <vector>

Neuron::Neuron(int id) : id(id), activation(0.0), isFiring(false) {
    synapses.reserve(10); 
}

void Neuron::receiveSignal(double signal) {
    activation += signal;
    if (activation > 1.0) {  
        isFiring = true;
    }
}

void Neuron::update() {
    if (!isFiring) return;  

    
#ifdef DEBUG
    std::cout << "Neuron " << id << " fired!\n";
#endif

    activation = 0.0;
    isFiring = false; 

    for (Synapse* synapse : synapses) {
        synapse->propagate();
    }
}

void Neuron::addSynapse(Synapse* synapse) {
    synapses.push_back(synapse);
}

double Neuron::getActivation() const {
    return activation;
}
