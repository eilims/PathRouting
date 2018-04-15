#include <stdio.h>
#include <limits.h>
#include "PathRouting.h"

//printing pertinent routing table data for debugging
void printNodeData(struct Node **nodeArray, int numberOfNodes){
    int i;
    int o;
    int q;
    //i serves as the "source" node index who own the printing table
    for (i = 0; i < numberOfNodes; i++) {
        //o serves as the "destination" node index
        for (o = 0; o < numberOfNodes; o++) {
            printf("Node %d Destination: %d Path: ", i, o);
            //q serves as the path index term
            for (q = 0; q < numberOfNodes; q++) {
                if (nodeArray[i]->routingTable[o].path[q] != -1) {
                    printf("%d ", nodeArray[i]->routingTable[o].path[q]);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    printf("Hello, World!\n");
    int numberOfNodes = 3;
    int i;
    int o;
    int q;
    //memory allocation
    struct Node **nodeArray = (struct Node **) malloc(numberOfNodes * sizeof(struct Node *));
    for (i = 0; i < numberOfNodes; i++) {
        nodeArray[i] = (struct Node *) malloc(numberOfNodes * sizeof(struct Node));
        nodeArray[i]->neighborTable = (int *) malloc(numberOfNodes * sizeof(int));
        for (o = 0; o < numberOfNodes; o++) {
            nodeArray[i]->routingTable = malloc(numberOfNodes * sizeof(struct routingEntry));
            for (q = 0; q < numberOfNodes; q++) {
                nodeArray[i]->routingTable[q].path = malloc(numberOfNodes * sizeof(int));
            }
        }
    }

    //instantiation
    for (i = 0; i < numberOfNodes; i++) {
        for (o = 0; o < numberOfNodes; o++) {
            //If the current node is assigning its a path to itself
            if (o == i) {
                nodeArray[i]->neighborTable[o] = 1;
                nodeArray[i]->routingTable[o].elementsInPath = 1;
                nodeArray[i]->routingTable[o].destination = i;
                //If the current node is assigning a path to other nodes
            } else {
                nodeArray[i]->neighborTable[o] = 0;
                nodeArray[i]->routingTable[o].elementsInPath = INT_MAX;
                nodeArray[i]->routingTable[o].destination = -1;
            }
            //Assigned routing table default values
            for (q = 0; q < numberOfNodes; q++) {
                if (i == q && i == o) {
                    nodeArray[i]->routingTable[o].path[q] = i;
                } else {
                    nodeArray[i]->routingTable[o].path[q] = -1;
                }

            }
        }
    }

    nodeArray[0]->routingTable[1].destination = 1;
    nodeArray[0]->routingTable[1].elementsInPath = 2;
    nodeArray[0]->routingTable[1].path[0] = 0;
    nodeArray[0]->routingTable[1].path[1] = 1;
    nodeArray[0]->neighborTable[1] = 1;

    nodeArray[1]->routingTable[0].destination = 0;
    nodeArray[1]->routingTable[0].elementsInPath = 2;
    nodeArray[1]->routingTable[0].path[0] = 1;
    nodeArray[1]->routingTable[0].path[1] = 0;
    nodeArray[1]->neighborTable[0] = 1;

    nodeArray[1]->routingTable[2].destination = 2;
    nodeArray[1]->routingTable[2].elementsInPath = 2;
    nodeArray[1]->routingTable[2].path[0] = 1;
    nodeArray[1]->routingTable[2].path[1] = 2;
    nodeArray[1]->neighborTable[2] = 1;

    nodeArray[2]->routingTable[1].destination = 1;
    nodeArray[2]->routingTable[1].elementsInPath = 2;
    nodeArray[2]->routingTable[1].path[0] = 2;
    nodeArray[2]->routingTable[1].path[1] = 1;
    nodeArray[2]->neighborTable[1] = 1;

    printNodeData(nodeArray, numberOfNodes);

    //i serves as the source node which sends out vectors to neighboring nodes
    for (i = 0; i < numberOfNodes; i++) {
        //o serves as the destination nodes who receives vectors if they are neighbors of i
        for (o = 0; o < numberOfNodes; o++) {
            //check if the destination is a neighbor of the source
            if (nodeArray[i]->neighborTable[o] && i != o) {
                updateVector(nodeArray[i], nodeArray[o], numberOfNodes, i, o);
            }
        }
    }

    printf("\n");

    printNodeData(nodeArray, numberOfNodes);

    //freeing memory
    for (i = 0; i < numberOfNodes; i++) {
        for (o = 0; o < numberOfNodes; o++) {
            free(nodeArray[i]->routingTable[o].path);
        }
        free(nodeArray[i]->neighborTable);
        free(nodeArray[i]->routingTable);
    }
    free(nodeArray);
    return 0;
}