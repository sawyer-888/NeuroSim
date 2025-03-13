#include "network.h"
#include "neuron.h"
#include "synapse.h"

Network::Network(int size) {
    for (int i = 0; i < size; i++) {
        neurons.push_back(new Neuron(i));
    }
    // Correctly create synapses
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j) {
                neurons[i]->addSynapse(new Synapse(neurons[i], neurons[j], 0.5));  
            }
        }
    }
}
