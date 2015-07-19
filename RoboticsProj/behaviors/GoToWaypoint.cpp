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
	cout << "Best particle on grid: (" << p.nX*4 << "," << p.nY*4 << "," << p.dAngle/3.14*180 << ")" << endl;
	//cout << "Way Point:     (" << _wayPointX << "," << _wayPointY << ")" << endl;
	//float angle = atan2(p.nX - this->_wayPointX, p.nY - this->_wayPointY);
	float angle = - atan2(this->_wayPointY - p.nY, this->_wayPointX - p.nX);
	cout << "worldangle = " << angle/3.14*180 << endl;
	cout << "P angle = " << p.dAngle/3.14*180 << endl;
	angle -= p.dAngle;
	//angle = p.dAngle - angle;
	//angle += p.dAngle;
	if (angle > M_PI){
		angle = -(2*M_PI - angle);
	}
	cout << "angle = " << angle/3.14*180 << endl;
	//this->_robot->setSpeed(0.0, 0);
	double angularSpeed;
	double xSpeed;
	float angleSpeed;
	if ((-0.1 < angle && angle < 0.1) && this->_robot->isForwardFree())
	{
		//cout << "setSpeed 0.3 (FWD)" << endl;
		xSpeed = 0.3;
		angularSpeed = 0;
	}
	else
	{
	//	cout << "setYAW " << angle  << endl;
		if (!(-0.1 < angle && angle < 0.1)){
			angleSpeed =  0.5;
		}
		else{
			angleSpeed = 0.2;
		}
		xSpeed = 0.05;

		angularSpeed = (angle > 0) ? angleSpeed : (-1) * angleSpeed;
	}
	/*if (-0.2 < angle && angle < 0.2)
	{
		cout << "setSpeed 0.3 (FWD)" << endl;
		this->_robot->setSpeed(0.3, 0);
	}
	else
	{
		cout << "setYAW " << angle  << endl;
		const float ANGLE_SPEED = 0.5;
		this->_robot->setSpeed(0.05, angle > 0 ? ANGLE_SPEED : -ANGLE_SPEED);
	}
*/
	//cout << "Speed: " << xSpeed << "Angle: " << angleSpeed << endl;
	this->_robot->setSpeed(xSpeed,angularSpeed);
}

bool GoToWaypoint::stopCond()
{
	Map::position p = this->_lm ->getBestParticleOnGrid();
	double dis = sqrt(pow(p.nX - this->_wayPointX, 2) +
			pow(p.nY - this->_wayPointY, 2));
	//cout << "stopCond " << dis << endl;
	cout << "Stop condition: paticle pos: (" << p.nX << "," << p.nY << ") WayPoint: (" << _wayPointX << "," << _wayPointY << ")" << endl;
	cout << "Distance = " << dis << endl;
	if (dis < 5){
		return true;
	}

	return false;
}

void GoToWaypoint::printDetails(){
	cout << "new behavior! x - " << this->_wayPointX << " y - " << this->_wayPointY << endl;
}

GoToWaypoint::~GoToWaypoint() {
	// TODO Auto-generated destructor stub
}
