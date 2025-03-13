#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "synapse.h" 

class Neuron {
public:
    Neuron(int id);
    void receiveSignal(double signal);
    void update();
    
    void addSynapse(Synapse* synapse);
    double getActivation() const;

    int getId() const { return id; }  
    std::vector<Synapse*>& getSynapses() { return synapses; }  

private:
    int id;
    double activation;
    std::vector<Synapse*> synapses;
};

#endif
