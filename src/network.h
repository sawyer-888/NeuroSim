#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "neuron.h"

class Network {
public:
    Network(int size);
    void stimulateNeuron(int neuron_id, double strength);
    void update();
    
    std::vector<Neuron*>& getNeurons() { return neurons; }
private:
    std::vector<Neuron*> neurons;
};

#endif
