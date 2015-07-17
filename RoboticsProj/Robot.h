/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include "math.h"

using namespace PlayerCc;


#define SAMPLES_NUM 666
#define MIN_ANGLE -120
#define ANGULAR_RESULUTION 0.36

class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Robot(char* ip, int port);
	LaserProxy* getLaserProxy(){
		return this->_lp;
	}
	PlayerClient* getPlayerClient(){
		return this->_pc;
	}
	Position2dProxy* getPositionProxy(){
		return this->_pp;
	}

	void read() {
		this->_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		this->_pp->SetSpeed(xSpeed, angularSpeed);
	}
	double getPosX() {
		return	this->_pp->GetXPos();
	}
	double getPosY() {
			return	this->_pp->GetYPos();
		}
	double getYaw() {
			return	this->_pp->GetYaw();
		}
	bool isRightFree() {
		if ((*_lp)[50] > 0.5)
			return true;
		else
			return false;
	}
	bool isForwardFree() {
		if ((*_lp)[332] > 0.5)
			return true;
		else
			return false;
	}

	static int getIndexByAngle(float angle);
	static float getAngleByIndex(int index);
	static float getRadianByIndex(int index);

	virtual ~Robot();
};

#endif /* ROBOT_H_ */
