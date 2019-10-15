#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "network.h"
// #include "train.h"


void initNetwork(Network *p_net, int depth, int *stack, int numInputs, double **inWeights, double ***weights, double **bias) {
    // Amount of layers
	p_net->depth = depth;

	// Array of amount of neurons per layer
	p_net->stack = malloc(depth * sizeof(int));
    memcpy(p_net->stack, stack, depth * sizeof(int));

	// ! 2D array allocation for input weight matrix
	p_net->inWeights = (double **) malloc(stack[0] * sizeof(double *));
	for (int outputNeuron = 0; outputNeuron < stack[0]; outputNeuron++) {
		p_net->inWeights[outputNeuron] = (double *) malloc(numInputs * sizeof(double));
	}
	if (NULL == inWeights) { // Random initialization if no weights given, othwerise transfer
		srand(time(0)); // Generate random sequence given time seed

		for (int outputNeuron = 0; outputNeuron < stack[0]; outputNeuron++) {
			for (int input = 0; input < numInputs; input++) {
				p_net->inWeights[outputNeuron][input] = ((double) rand() / RAND_MAX);
			}
		}
	} else {
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
    if (NULL == weights) { // Random initialization if no weights given, othwerise transfer
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
	if (NULL == bias) { // Random initialization if no bias given, othwerise transfer
		srand(time(0)); // Generate random sequence given time seed

		for (int layer = 0; layer < depth; layer++) {
			for (int neuron = 0; neuron < stack[layer]; neuron++) {
				p_net->bias[layer][neuron] = ((double) rand() / RAND_MAX);
			}
		}
	} else {
		for (int layer = 0; layer < depth; layer++) {
			for (int neuron = 0; neuron < stack[layer]; neuron++) {
				p_net->bias[layer][neuron] = bias[layer][neuron];
			}
		}	
	}
}

void loadNetwork(const char *fileName) {
    
}

void runNetwork(Network *p_net, double *inputs) {
	for (int neuron = 0; neuron < p_net->stack[0]; neuron++) {

	}

	// Iterate through neural network layers
	for (int layer = 1; layer < p_net->depth; layer++) {

		
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
