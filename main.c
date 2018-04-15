#include <stdio.h>
#include <limits.h>
#include "PathRouting.h"

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
        nodeArray[i]->totalRoutingTable = (int **) malloc(numberOfNodes * sizeof(int *));
        for (o = 0; o < numberOfNodes; o++) {
            nodeArray[i]->totalRoutingTable[o] = malloc(numberOfNodes * sizeof(int));
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
                nodeArray[i]->routingTable[o].elementsInPath = 1;
                nodeArray[i]->routingTable[o].destination = i;
                //If the current node is assigning a path to other nodes
            } else {
                nodeArray[i]->routingTable[o].elementsInPath = INT_MAX;
                nodeArray[i]->routingTable[o].destination = -1;
            }
            //Assigned routing table default values
            for (q = 0; q < numberOfNodes; q++) {
                if (i == q && i == o) {
                    nodeArray[i]->routingTable[o].path[q] = i;
                    nodeArray[i]->totalRoutingTable[o][q] = 0;
                } else {
                    nodeArray[i]->routingTable[o].path[q] = -1;
                    nodeArray[i]->totalRoutingTable[o][q] = INT_MAX;
                }

            }
        }
    }

    nodeArray[0]->routingTable[1].destination = 1;
    nodeArray[0]->routingTable[1].elementsInPath = 2;
    nodeArray[0]->routingTable[1].path[0] = 0;
    nodeArray[0]->routingTable[1].path[1] = 1;

    nodeArray[1]->routingTable[0].destination = 0;
    nodeArray[1]->routingTable[0].elementsInPath = 2;
    nodeArray[1]->routingTable[0].path[0] = 1;
    nodeArray[1]->routingTable[0].path[1] = 0;

    nodeArray[1]->routingTable[2].destination = 2;
    nodeArray[1]->routingTable[2].elementsInPath = 2;
    nodeArray[1]->routingTable[2].path[0] = 1;
    nodeArray[1]->routingTable[2].path[1] = 2;

    nodeArray[2]->routingTable[1].destination = 1;
    nodeArray[2]->routingTable[1].elementsInPath = 2;
    nodeArray[2]->routingTable[1].path[0] = 2;
    nodeArray[2]->routingTable[1].path[1] = 1;

    updateVector(nodeArray[1], nodeArray[0], numberOfNodes, 1, 0);
    updateVector(nodeArray[1], nodeArray[2], numberOfNodes, 1, 2);
    for(i = 0; i < numberOfNodes; i++){
        for(o = 0; o < numberOfNodes; o++){
            printf("Node %d Destination: %d Path: ", i, o);
            for(q = 0; q < numberOfNodes; q++){
                if(nodeArray[i]->routingTable[o].path[q] != -1){
                    printf("%d ", nodeArray[i]->routingTable[o].path[q]);
                }
            }
            printf("\n");
        }
    }

    for (i = 0; i < numberOfNodes; i++) {
        for (o = 0; o < numberOfNodes; o++) {
            for (q = 0; q < numberOfNodes; q++) {
                free(nodeArray[i]->routingTable[q].path);
            }
            free(nodeArray[i]->totalRoutingTable[o]);
            free(nodeArray[i]->routingTable);
        }
        free(nodeArray[i]->totalRoutingTable);
        free(nodeArray[i]);
    }
    return 0;
}