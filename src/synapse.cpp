#include "neuron.h"
#include "synapse.h"

Synapse::Synapse(Neuron* from, Neuron* to, double weight)
    : from(from), to(to), weight(weight) {}

void Synapse::propagate() {
    to->receiveSignal(weight);
}
