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
    void (*activate) (Neuron *self);    // Run activation function on neuron
} Neuron;

/**
 * @brief Creates neuron of given type.
 * 
 * @param type 
 * @return Neuron 
 */
Neuron initNeuron(NeuronType type);
#endif