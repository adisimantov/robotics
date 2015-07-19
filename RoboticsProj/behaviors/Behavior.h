/*
 * Behavior.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include <vector>
#include "../Robot.h"
#include "../LocalizationManager.h"
#include "math.h"
using namespace std;

class Behavior {
	vector<Behavior*> _behVect;
protected:
	Robot* _robot;

public:
	Behavior(Robot* robot);
	virtual ~Behavior();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	virtual void printDetails() = 0;
	Behavior* addBeh(Behavior* next);
	Behavior* selectNext();

};

#endif /* BEHAVIOR_H_ */
