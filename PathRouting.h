//
// Created by DanielB on 4/15/2018.
//

#ifndef PATHROUTING_PATHROUTING_H
#define PATHROUTING_PATHROUTING_H

#include <stdlib.h>

//contains the desintation of the path
//the path not including the source
//and the number of elements in the path
struct routingEntry {
    int destination;
    int* path;
    int elementsInPath;
};

//hols all pertinent data on neighbors of the node and the routing table
struct Node {
    struct routingEntry* routingTable;
    int* neighborTable;
};

int updateVector(struct Node *sourceNode, struct Node *targetNode, int nodeArrayLength, int sourceNodeIndex,
                  int targetNodeIndex);

#endif //PATHROUTING_PATHROUTING_H
