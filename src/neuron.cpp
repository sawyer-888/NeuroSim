#include "neuron.h"
#include "synapse.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> // For std::min

Neuron::Neuron(int id) : id(id), activation(0.0) {
    synapses.reserve(10); // ✅ Preallocate memory (can be adjusted)
}

void Neuron::receiveSignal(double signal) {
    activation += signal;
    activation = std::min(activation, 2.0);  // ✅ Avoids unnecessary "if" check (caps activation)
}

void Neuron::update() {
    if (activation <= 1.0) return;  // ✅ Skip unnecessary processing

#ifdef DEBUG
    std::cout << "Neuron " << id << " fired!\n";
#endif

    activation = 0.0;  // ✅ Reset neuron activation

    for (auto& synapse : synapses) {
        synapse->propagate();
    }
}

void Neuron::addSynapse(std::unique_ptr<Synapse> synapse) {
    synapses.push_back(std::move(synapse));  // ✅ Moves ownership, avoids copy overhead
}

double Neuron::getActivation() const {
    return activation;
}

void Neuron::optimizeMemory() {
    synapses.shrink_to_fit();  // ✅ Reduce memory overhead after all synapses are added
}
