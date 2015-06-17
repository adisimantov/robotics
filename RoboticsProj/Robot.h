/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;


#define SAMPLES_NUM 666
#define MIN_ANGLE 120
#define MAX_ANGLE 360
#define ANGULAR_RESULUTION 0.36

class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Robot(char* ip, int port);
	int Move();
	void read() {
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		_pp->SetSpeed(xSpeed, angularSpeed);
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

	int getIndexByAngle(int angle){

		return ((angle + MIN_ANGLE) / ANGULAR_RESULUTION);
	}

	virtual ~Robot();
};

#endif /* ROBOT_H_ */
