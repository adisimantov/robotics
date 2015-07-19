
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
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		read();
}

bool Robot::isRightFree(){
	for (int i = 100; i<=200 ; i++ ){
				if (this->getLaserProxy()->GetRange(i) < 1){
					return false;
					//cout << "index = " <<  i <<  endl;
				}
			}
	return true;
}

bool Robot::isLeftFree(){
	for(int i = 466; i<=566;i++){
				if (this->getLaserProxy()->GetRange(i) < 1){
					return false;
					//cout << "index = " <<  i <<  endl;
				}
			}
	return true;
}

bool Robot::isForwardFree(){
	for (int i = 300; i<= 366 ; i++ ){
				if (this->getLaserProxy()->GetRange(i) < 1){
					return false;
					//cout << "index = " <<  i <<  endl;
				}
			}
	return true;
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
