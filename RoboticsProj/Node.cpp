/*
path =(direction+dir/2)%dir+path; //we work our way back * Node.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include "ConfigurationManager.h"

/** constructor **/
Node::Node(int x,int y, int d,int p)
{
    xPos=x;
    yPos=y;
    distance=d;
    priority=p;
}

/** getters for variables **/
//current node xPosition
int Node::getxPos() const {
    return xPos;
}

//current node yPosition
int Node::getyPos() const {
    return yPos;
}

//gscore
int Node::getDistance() const {
    return distance;
}

//fscore
int Node::getPriority() const {
    return priority;
}

void Node::updatePriority(const int & xDest, const int & yDest){
    priority = distance + estimateDistance(xDest,yDest)*ConfigurationManager::getInstance()->getDGridRes();
}

void Node::updateDistance(){//const int & direction
    distance +=ConfigurationManager::getInstance()->getDGridRes();
}

const int & Node::estimateDistance(const int & xDest, const int & yDest) const{
    static int xDistance,yDistance,totalDistance;
    xDistance=xDest-xPos;
    yDistance=yDest-yPos;

    //totalDistance=abs(xDistance)+abs(yDistance);
    totalDistance = sqrt(pow(xDistance,2) + pow(yDistance,2));

    return (totalDistance);
}

bool Node::operator< (const Node & b) const{
    return (this->getPriority() > b.getPriority());
}

