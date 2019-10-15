#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "network.h"
// #include "train.h"


int initNetwork(Network *p_net, NeuronType **types, int depth, int *stack, int numInputs, double **inWeights, double ***weights, double **bias) {
	if (NULL == p_net) {
        return -1;  // Neuron is not initialized so fail.
    }

    // Amount of layers
	p_net->depth = depth;

	// Array of amount of neurons per layer
	p_net->stack = malloc(depth * sizeof(int));
    memcpy(p_net->stack, stack, depth * sizeof(int));

	// Amount of inputs to network
	p_net->numInputs = numInputs;

	// ! 2D array allocation for input weight matrix
	p_net->inWeights = (double **) malloc(stack[0] * sizeof(double *));
	for (int outputNeuron = 0; outputNeuron < stack[0]; outputNeuron++) {
		p_net->inWeights[outputNeuron] = (double *) malloc(numInputs * sizeof(double));
	}
	if (NULL == inWeights) {
		// Random initialization if no weights given, othwerise transfer

		srand(time(0)); // Generate random sequence given time seed

		for (int outputNeuron = 0; outputNeuron < stack[0]; outputNeuron++) {
			for (int input = 0; input < numInputs; input++) {
				p_net->inWeights[outputNeuron][input] = ((double) rand() / RAND_MAX);
			}
		}
	} else {
		// Transfer data, didn't use memcpy b/c performance doesn't matter for this part

		for (int outputNeuron = 0; outputNeuron < stack[0]; outputNeuron++) {
			for (int input = 0; input < numInputs; input++) {
				p_net->inWeights[outputNeuron][input] = inWeights[outputNeuron][input];
			}
		}
	}

	// ! 3D array allocation for inter-layer weight matrix
	p_net->weights = (double ***) malloc((depth - 1) * sizeof(double **));
	for (int inputLayer = 0; inputLayer < depth - 1; inputLayer++) {
		p_net->weights[inputLayer] = (double **) malloc(stack[inputLayer + 1] * sizeof(double *));

		for (int outputNeuron = 0; outputNeuron < stack[inputLayer]; outputNeuron++) {
			p_net->weights[inputLayer][outputNeuron] = (double *) malloc(stack[inputLayer] * sizeof(double));
		}
	}
    if (NULL == weights) {
		// Random initialization if no weights given, othwerise transfer

		srand(time(0)); // Generate random sequence given time seed
		
		// Init random weights
		for (int layer = 0; layer < depth - 1; layer++) {
			for (int i = 0; i < stack[layer + 1]; i++) {
				for (int j = 0; j < stack[layer]; j++) {
					p_net->weights[layer][i][j] = ((double) rand() / RAND_MAX);
					// p_net->weights[layer][i][j] = 0.00001;
				}
			}
		}
	} else {

		// Transfer data, didn't use memcpy b/c performance doesn't matter for this part
		for (int layer = 0; layer < depth - 1; layer++) {
			for (int i = 0; stack[layer + 1]; i++) {
				for (int j = 0; j < stack[layer]; j++) {
					p_net->weights[layer][i][j] = weights[layer][i][j];
				}
			}
		}	
	};

	// ! 2D array allocation for bias input matrix
	p_net->bias = (double **) malloc(depth * sizeof(double *));
	for (int layer = 0; layer < depth; layer++) {
		p_net->bias = (double *) malloc(stack[layer] * sizeof(double));
	}
	if (NULL == bias) {
		// Random initialization if no bias given, othwerise transfer
		
		srand(time(0)); // Generate random sequence given time seed

		for (int layer = 0; layer < depth; layer++) {
			for (int neuron = 0; neuron < stack[layer]; neuron++) {
				p_net->bias[layer][neuron] = ((double) rand() / RAND_MAX);
			}
		}
	} else {
		// Transfer data, didn't use memcpy b/c performance doesn't matter for this part

		for (int layer = 0; layer < depth; layer++) {
			for (int neuron = 0; neuron < stack[layer]; neuron++) {
				p_net->bias[layer][neuron] = bias[layer][neuron];
			}
		}	
	}

	// ! 2D array allocation for neuron types
	p_net->neurons = (Neuron **) malloc(depth * sizeof(Neuron *));
	for (int layer = 0; layer < depth; layer++) {
		p_net->bias = (Neuron *) malloc(stack[layer] * sizeof(Neuron));
	}
	if (NULL == types) {
		// Default initialization if no types given, othwerise transfer

		for (int layer = 0; layer < depth; layer++) {
			for (int neuron = 0; neuron < stack[layer]; neuron++) {
				initNeuron(&p_net->neurons[layer][neuron], NEURON_DEFAULT);
			}
		}
	} else {
		// Transfer data, didn't use memcpy b/c performance doesn't matter for this part

		for (int layer = 0; layer < depth; layer++) {
			for (int neuron = 0; neuron < stack[layer]; neuron++) {
				initNeuron(&p_net->neurons[layer][neuron], types[layer][neuron]);
			}
		}
	}

	return 0; // Ran successfully
}

void loadNetwork(const char *fileName) {
    
}

void runNetwork(Network *p_net, double *inputs) {
	for (int neuron = 0; neuron < p_net->stack[0]; neuron++) {
		// Calculated weighted sum going into neuron
		double weightedSum = 0;
		for (int input = 0; input < p_net->numInputs; input++) {
			weightedSum += p_net->inWeights[neuron][input] *  inputs[input];
		}

		// Apply neuron activation function on weighted input sum to get neuron value
		p_net->neurons[0][neuron].activate(&p_net->neurons[0][neuron], weightedSum);
	}

	// Iterate through neural network layers
	for (int layer = 1; layer < p_net->depth; layer++) {		
		for (int outputNeuron = 0; outputNeuron < p_net->stack[layer]; outputNeuron++) {
			// Calculated weighted sum going into neuron
			double weightedSum = 0;
			for (int inputNeuron = 0; inputNeuron < p_net->numInputs; inputNeuron++) {
				weightedSum += p_net->inWeights[outputNeuron][inputNeuron] *  inputs[inputNeuron];
			}

			// Apply neuron activation function on weighted input sum to get neuron value
			p_net->neurons[layer][outputNeuron].activate(&p_net->neurons[layer][outputNeuron], weightedSum);
		}
	}
}

void displayNetwork(Network* p_net) {
	for (int layer = 0; layer < p_net->weights - 1; layer++) {
		printf("\nLayer: %d\n------------------------------------------------------------------\n", layer);
		for (int i = 0; i < p_net->stack[layer + 1]; i++) {
			for (int j = 0; j < p_net->stack[layer]; j++) {
				printf("%1.8f   |   ", p_net->weights[layer][i][j]);
			}
			printf("\n");
		}
	}
}

void freeNetwork(Network *p_net) {

}