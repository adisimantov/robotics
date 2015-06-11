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

int Robot::Move(){

	double d1;
	double d2;
	bool checkFront;


	while (true) {
		read();

		d1 = 10000;
		d2 = 10000;
		checkFront = false;

		for (int i = getIndexByAngle(-20); i<= getIndexByAngle(20) && !checkFront; i++ ){
			if ((*_lp)[i] < 0.8){
				checkFront = true;
				//cout << "index = " <<  i <<  endl;
			}
		}

		if (checkFront){
			for(int i = getIndexByAngle(-120); i<=getIndexByAngle(-10);i++){
				if ((*_lp)[i] < d1){
					d1 = (*_lp)[i];
				}
			}
			for(int i = getIndexByAngle(10); i<=getIndexByAngle(120);i++){
				if ((*_lp)[i] < d2){
					d2 = (*_lp)[i];
				}
			}


			if (d1 > d2){
				//cout << "d1 = " <<  d1 << " d2 = " << d2 << endl;

				setSpeed(0.01, -0.3);
			}
			else {
				//cout << "d2 = " <<  d2 << " d1 = " << d1 << endl;

				setSpeed(0.01, 0.3);

			}
		}
		else{
			setSpeed(0.8, 0.0);
		}
	}
	return 0;
}



Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
