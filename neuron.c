#include <stdlib.h>
#include <math.h>

#include "neuron.h"

// Activation functions

void sigmoidFunction(Neuron *p_neuron, double input) {
    p_neuron->value = 1 / (1 + exp(-input));
}

void hyperTanFunction(Neuron *p_neuron, double input) {
    p_neuron->value = (exp(input) + exp(-input)) / (exp(input) + exp(-input));
}

// Define default function!
void (*defaultFunction)(Neuron *p_neuron, double input) = sigmoidFunction;


int initNeuron(Neuron *p_neuron, NeuronType type) {
    if (NULL == p_neuron) {
        return -1;  // Neuron is not initialized so fail.
    }

    p_neuron->type = type;
    p_neuron->value = 0;

    switch (type) {
        case NEURON_HYPERTAN:
            p_neuron->activate = hyperTanFunction;   // Set to sigmoid function
            break;

        case NEURON_SIGMOID:
            p_neuron->activate = sigmoidFunction;   // Set to sigmoid function
            break;

        case NEURON_DEFAULT:
        default:
            p_neuron->activate = defaultFunction;   // Set to default in case of default type or undefined type value
            break;
    }

    return 0;   // Ran successfully.
}

int freeNeuron(Neuron *p_neuron) {
    if (NULL == p_neuron) {
        return -1;  // Neuron is not initialized so fail.
    }

    free(p_neuron);

    return 0;   // Ran successfully.
}