#include <stdlib.h>

#include "train.h"
#include "network.h"

void stepNetwork(Network *p_network, double *inputs, double *expectedOut) {
    double **error;

    error = (double **) malloc(p_network->depth * sizeof(double *));
	for (int layer = 0; layer < p_network->depth; layer++) {
		error[layer] = (double *) malloc(p_network->stack[layer] * sizeof(double));
	}
    
    runNetwork(p_network, inputs);

    // Last layer error
    for (int neuron = 0; neuron < p_network->stack[p_network->depth - 1]; neuron++) {
        error[p_network->depth - 1][neuron] = expectedOut[neuron] - p_network->neurons[p_network->depth - 1][neuron].value;
    }

/*
    for (int layer = p_network->depth - 2; layer > 0; layer--) {
        for (int neuron = 0; neuron < p_network->stack[layer]; neuron++) {
            double neuronError = 0;

            for (int frontNeuron = 0; frontNeuron < p_network->stack[layer + 1]; frontNeuron++) {
                double sumOfWeights = 0;
                for (int currNeuron = 0; currNeuron < p_network->stack[layer]; currNeuron++) {
                    sumOfWeights+= p_network->weights[layer][frontNeuron][currNeuron];
                }
                neuronError += p_network->weights[layer][frontNeuron][neuron] * error[layer + 1][frontNeuron] / sumOfWeights;
            }

            error[layer][neuron] = neuronError;
        }
    }
*/
    // Middle layer error
    for (int layer = p_network->depth - 2; layer > 0; layer--) {
        for (int neuron = 0; neuron < p_network->stack[layer]; neuron++) {
            double neuronError = 0;

            for (int frontNeuron = 0; frontNeuron < p_network->stack[layer + 1]; frontNeuron++) {
                neuronError += p_network->weights[layer][frontNeuron][neuron] * error[layer + 1][frontNeuron];
            }

            error[layer][neuron] = neuronError;
        }
    }

    // Input layer error
    for (int neuron = 0; neuron < p_network->stack[0]; neuron++) {
        for (int frontNeuron = 0; frontNeuron < p_network->stack[1]; frontNeuron++) {
            double neuronError = 0;

            for (int frontNeuron = 0; frontNeuron < p_network->stack[1]; frontNeuron++) {
                neuronError += p_network->inWeights[frontNeuron][neuron] * error[1][frontNeuron];
            }

            error[0][neuron] = neuronError;
        }
    }
}