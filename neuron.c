#include <stdlib.h>
#include <math.h>

#include "neuron.h"
void sigmoidFunction(Neuron *p_neuron, double input);
// Define default function!
void (*defaultFunction)(Neuron *p_neuron, double input) = sigmoidFunction;

// Activation functions

void sigmoidFunction(Neuron *p_neuron, double input) {
    p_neuron->value = 1 / (1 + exp(-input));
}

void hyperTanFunction(Neuron *p_neuron, double input) {
    p_neuron->value = (exp(input) + exp(-input)) / (exp(input) + exp(-input));
}


Neuron initNeuron(NeuronType type) {
    Neuron neuron;
    neuron.type = type;
    neuron.value = 0;

    switch (type) {
        case NEURON_HYPERTAN:
            neuron.activate = hyperTanFunction;   // Set to sigmoid function
            break;
        case NEURON_SIGMOID:
            neuron.activate = sigmoidFunction;   // Set to sigmoid function
            break;
        case NEURON_DEFAULT:
        default:
            neuron.activate = defaultFunction;   // Set to default in case of default type or undefined type value
            break;
    }

    return neuron;
}

int freeNeuron(Neuron *p_neuron) {
    free(p_neuron);
}