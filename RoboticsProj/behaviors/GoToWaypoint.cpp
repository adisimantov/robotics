/*
 * TurnRight.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "GoToWaypoint.h"
 #include <unistd.h>

GoToWaypoint::GoToWaypoint(Robot* robot, int x, int y, LocalizationManager* lm):Behavior(robot) {

	this->_wayPointX = x;
	this->_wayPointY = y;
	this->_lm = lm;
}


bool GoToWaypoint::startCond()
{
	return true;
}

void GoToWaypoint::action()
{
	//TODO ADI check what happends when there is an opsticle
	Map::position p = this->_lm ->getBestParticleOnGrid();
	float angle = atan2(p.nX - this->_wayPointX, p.nY - this->_wayPointY);
	angle += p.dAngle;
	if (angle > M_PI){
		angle = -(2*M_PI - angle);
	}
	cout << "angle = " << angle << endl;

	this->_robot->setSpeed(0.3, angle);
	//sleep(1);
	//this->_robot->setSpeed(0.3,0);
	cout << "move" << endl;
}

bool GoToWaypoint::stopCond()
{
	Map::position p = this->_lm ->getBestParticleOnGrid();
	double dis = sqrt(pow(p.nX - this->_wayPointX, 2) +
			pow(p.nY - this->_wayPointY, 2));
	cout << "stopCond " << dis << endl;
	if (dis < 3){
		return true;
	}

	return false;
}

GoToWaypoint::~GoToWaypoint() {
	// TODO Auto-generated destructor stub
}
