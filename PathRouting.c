//
// Created by DanielB on 4/15/2018.
//

#include "PathRouting.h"

int updateVector(struct Node *sourceNode, struct Node *targetNode, int nodeArrayLength, int sourceNodeIndex,
                  int targetNodeIndex){
    int currentNode;
    int currentEdge;
    int pathIndex;
    int isChanged = 0;
    for(currentNode = 0; currentNode < nodeArrayLength; currentNode++){
        for(currentEdge = 0; currentEdge < nodeArrayLength; currentEdge++){
            int isTargetInPath = 0;
            //Make sure no loops are apparent
            for(pathIndex = 0; pathIndex < sourceNode->routingTable[currentEdge].elementsInPath; pathIndex++){
                if(targetNodeIndex == sourceNode->routingTable[currentEdge].path[pathIndex]){
                    isTargetInPath = 1;
                }
            }
            if (!isTargetInPath){
                if(targetNode->routingTable[currentEdge].elementsInPath > sourceNode->routingTable[currentEdge].elementsInPath + 1){
                    targetNode->routingTable[currentEdge].path[0] = targetNodeIndex;
                    for(pathIndex = 0; pathIndex < sourceNode->routingTable[currentEdge].elementsInPath; pathIndex++){
                        targetNode->routingTable[currentEdge].path[pathIndex + 1] = sourceNode->routingTable[currentEdge].path[pathIndex];
                        targetNode->routingTable[currentEdge].elementsInPath = sourceNode->routingTable[currentEdge].elementsInPath + 1;
                    }
                    isChanged = 1;
                }
            }
        }
    }
    return isChanged;
}


