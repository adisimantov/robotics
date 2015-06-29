/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"
//TODO ADI delete
#include <unistd.h>
#include <iostream>
using namespace std;



Manager::Manager(Robot* robot, Plan* pln, Map* map, Map* inflatedMap) {
	this->_robot = robot;
	this->_curr = pln->getStartPoint();
	this->_regularMap = map;
	this->_inflatedMap = inflatedMap;
}
void Manager::run()
{
	LocalizationManager lm(this->_regularMap);
	double x,y,yaw, x1,y1,yaw1;

/*	_robot->read();
	if(!(_curr->startCond()))
		return;
	_curr->action();
	while(_curr !=NULL)
	{
		while(_curr->stopCond() == false)
		{
			//x = _robot->_pp->
			_curr->action();*/
	_robot->read();
	x1 = _robot->getPosX();
	y1 = _robot->getPosY();
	yaw1 = _robot->getYaw();
	int i = 1;

	while (true){
		_robot->setSpeed(0.2,0.01);
		if (i % 2 == 0){
			_robot->read();
			x =  _robot->getPosX();
			y =  _robot->getPosY();
			yaw =  _robot->getYaw();

			lm.update(x - x1,y - y1,yaw - yaw1,_robot->getLaserProxy());

			x1 = x;
			y1 = y;
			yaw1 = yaw;
		}

		i++;
	}
	/*	}
		_curr = _curr->selectNext();
		_robot->read();
	}*/
}

Manager::~Manager() {
	delete _robot;
	delete _regularMap;
	delete _inflatedMap;
	delete _curr;
}
