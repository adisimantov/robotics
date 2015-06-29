/*
 * Node.h
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>

class Node
{
private:
	int xPos;
	int yPos;
	int distance;
	int priority;
public:
	Node(int x,int y, int d,int p);
	int getxPos() const;
	int getyPos() const;
	int getDistance() const;
	int getPriority() const;
	void updatePriority(const int & xDest, const int & yDest);
	void updateDistance();
	const int & estimateDistance(const int & xDest, const int & yDest) const;
	bool operator< (const Node & b) const;

};



#endif /* NODE_H_ */
