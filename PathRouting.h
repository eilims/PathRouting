//
// Created by DanielB on 4/15/2018.
//

#ifndef PATHROUTING_PATHROUTING_H
#define PATHROUTING_PATHROUTING_H

#include <stdlib.h>

struct routingEntry {
    int destination;
    int* path;
    int elementsInPath;
};


struct Node {
    struct routingEntry* routingTable;
    int** totalRoutingTable;
};

void updateVector(struct Node *sourceNode, struct Node *targetNode, int nodeArrayLength, int sourceNodeIndex,
                  int targetNodeIndex);

#endif //PATHROUTING_PATHROUTING_H
