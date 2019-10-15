#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.h"

typedef struct {
    int depth;              // Number of layers
    int *stack;             // Number of neurons per layer
    int numInputs;
    double **inWeights;     // Input weights
    double ***weights;      // Inter-layer 3d weights
    // double *weights;      // Inter-layer 1d weights
    double **bias;          // Neuron bias values
    Neuron **neurons;  // Neurons
} Network;


int initNetwork(Network *p_net, NeuronType **types, int depth, int *stack, int numInputs, double **inWeights, double ***weights, double **bias);

void loadNetwork(const char *fileName);

#endif