/*
 * Behavior.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {
	_robot = robot;
}

Behavior*  Behavior::addBeh(Behavior* next)
{
	_behVect.push_back(next);
	return next;
}
Behavior* Behavior::selectNext()
{
	//Run over vector and return first true startCond of the first behavior
	for (vector<Behavior*>::iterator it = this->_behVect.begin(); it != this->_behVect.end(); it++){
	    if ((*it)->startCond()){
	    	(*it)->printDetails();
	    	return (*it);
	    }
	}
	return NULL;
}


Behavior::~Behavior() {
//TODO ADI delete vector!
}
