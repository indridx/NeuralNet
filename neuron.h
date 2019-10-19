#ifndef NEURON_H
#define NEURON_H

typedef enum {
    NEURON_DEFAULT,
    NEURON_SIGMOID,
    NEURON_HYPERTAN
} NeuronType;

typedef struct Neuron {
    double value;                       // Neuron activated value
    NeuronType type;                    // Neuron type, determining activation function
    void (*activate) (struct Neuron *self, double input);    // Run activation function on neuron
} Neuron;

/**
 * @brief Initializes neuron for specific activation function.
 * 
 * @param p_neuron Pointer to neuron
 * @param type NEURON_TYPE
 * @return int Return 0 if succeeeded, else if not. 
 */
int initNeuron(Neuron *p_neuron, NeuronType type);
#endif