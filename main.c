#include <stdio.h>
#include <string.h>

#include "network.h"
#include "train.h"



void main(int argc, char **argv) {
    if (1 == argc || 2 == argc && (0 == strcmp("help", argv[1]) || 0 == strcmp("h", argv[1]))) {
        // TODO: List commands

        // TODO: Exit program
    }

    if (3 == argc && 0 == strcmp("train", argv[1])) {
        // TODO: Train on dataset


    }

    if (3 == argc && 0 == strcmp("run", argv[1])) {
        // TODO: Run on dataset
    }

    Network network;
    int stack[] = {3, 3, 3};
    double input[] = {0.0, 0.0, 0.0};

    initNetwork(&network, NULL, 3, stack, 3, NULL, NULL, NULL);

    runNetwork(&network, input);

    displayNetwork(&network);


}