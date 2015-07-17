/*
 * Plan.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Plan.h"

Plan::Plan(Robot* robot, LocalizationManager* lm, list<int*> waypointList) {

	cout << "plan start" << endl;
	this->_robot = robot;
	int size = waypointList.size();
	//Creating behaviors
	this->_behaviorsArray = new Behavior*[size];

	int* current;
	int i = 0;
	cout << "plan behaviors" << endl;
	for (list<int*>::iterator it = waypointList.begin(); it != waypointList.end(); it++){
		current = *it;
		this->_behaviorsArray[i++] = new GoToWaypoint(_robot,current[0], current[1], lm);
	}

	for (int j = size - 2; j >= 0; j--){
		this->_behaviorsArray[j]->addBeh(this->_behaviorsArray[j+1]);
	}

    this->_start = this->_behaviorsArray[0];
    cout << "plan end" << endl;

}

Plan::~Plan() {
	// TODO Auto-generated destructor stub

}
