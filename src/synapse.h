#ifndef SYNAPSE_H
#define SYNAPSE_H

class Neuron; 

class Synapse {
public:
    Synapse(Neuron* from, Neuron* to, double weight);
    void propagate();
    
    Neuron* getTo() const { return to; }  

private:
    Neuron* from;
    Neuron* to;
    double weight;
};

#endif
