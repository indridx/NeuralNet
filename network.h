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


/**
 * @brief Initializes network based on given parameters.
 * 
 * @param p_net Pointer to network to be intialized.
 * @param types 2D array corresponding to types of neurons in network.
 * @param depth Amount of layers in array, excluding inputs.
 * @param stack 1D array of length (depth) describing amount of neurons per layer.
 * @param numInputs Number of inputs.
 * @param inWeights 2D array of weights between inputs and 1st layer.
 * @param weights 3D array of inter-layer weights for between each layer.
 * @param bias 2D array of bias levels for each neuron.
 * @return int Return -1 if fail, 0 if pass.
 */
int initNetwork(Network *p_net, NeuronType **types, int depth, int *stack, int numInputs, double **inWeights, double ***weights, double **bias);

/**
 * @brief Loads network data from csv save file.
 * 
 * @param fileName File name of csv file to be read.
 */
void loadNetwork(const char *fileName);

/**
 * @brief Saves network data to csv save file.
 * 
 * @param fileName File name of csv file to be written.
 */
void saveNetwork(const char *fileName);

/**
 * @brief Calculates neuron levels.
 * 
 * @param p_net 
 * @param inputs 
 */
void runNetwork(Network *p_net, double *inputs);

/**
 * @brief Displays network data in terminal.
 * 
 * @param p_net Pointer to network to be displayed.
 */
void displayNetwork(Network* p_net);

/**
 * @brief Frees allocated memory for network.
 * 
 * @param p_net Pointer to network to be freed. 
 * @return int 
 */
int freeNetwork(Network *p_net);

#endif