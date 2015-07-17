
/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	_pp->SetOdometry(0,0,0);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		read();
}

// TODO ADI remove this function!
int Robot::getIndexByAngle(float angle){

	return ((angle + MIN_ANGLE) / ANGULAR_RESULUTION);
}
float Robot::getAngleByIndex(int index){

		return ((float)index * ANGULAR_RESULUTION - 120);

}
float Robot::getRadianByIndex(int index){
	//return (Robot::getAngleByIndex(index) * M_PI / 180);

		return ((float)(index * ANGULAR_RESULUTION + MIN_ANGLE) * M_PI / 180);
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
