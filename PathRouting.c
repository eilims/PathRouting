//
// Created by DanielB on 4/15/2018.
//

#include <limits.h>
#include "PathRouting.h"

int updateVector(struct Node *sourceNode, struct Node *targetNode, int nodeArrayLength, int sourceNodeIndex,
                  int targetNodeIndex){
    int currentNode;
    int pathIndex;
    int isChanged = 0;
        //CurrentNode represents the path from the source to the currentNode
        for(currentNode = 0; currentNode < nodeArrayLength; currentNode++) {
            //Skip if the target node is in the path for time and prevent looping
            int isTargetInPath = 0;
            //make sure that the source has a neighbor to the current node and ensure we are pathing to the same node
            if (sourceNode->neighborTable[currentNode] && currentNode != sourceNodeIndex) {
                //check if the target node is in the path for the sourceNode to currentNode
                for (pathIndex = 0; pathIndex < sourceNode->routingTable[currentNode].elementsInPath; pathIndex++) {
                    if (targetNodeIndex == sourceNode->routingTable[currentNode].path[pathIndex]) {
                        isTargetInPath = 1;
                    }
                }
                if (!isTargetInPath) {
                    //if the path is shorter for the new path from the source node replace the new path with the old one
                    if (targetNode->routingTable[currentNode].elementsInPath > sourceNode->routingTable[currentNode].elementsInPath + 1) {
                        //we must place the targetNode at the front of the path
                        // This was decided for this algorithm to keep standards from initial assignment constant
                        targetNode->routingTable[currentNode].path[0] = targetNodeIndex;
                        for (pathIndex = 0; pathIndex < sourceNode->routingTable[currentNode].elementsInPath; pathIndex++) {
                            targetNode->routingTable[currentNode].path[pathIndex + 1] = sourceNode->routingTable[currentNode].path[pathIndex];
                            targetNode->routingTable[currentNode].elementsInPath = sourceNode->routingTable[currentNode].elementsInPath + 1;
                        }
                        isChanged = 1;
                    }
                }
            }
        }
    return isChanged;
}


