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

    
}