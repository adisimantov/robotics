/*
 * Plan.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLAN_H_
#define PLAN_H_
#include "../behaviors/Behavior.h"
#include "../behaviors/GoToWaypoint.h"
#include "../Robot.h"
class Plan {

protected:
	Behavior* _start;
	Behavior** _behaviorsArray;
	Robot* _robot;

public:
	Plan(Robot* robot, LocalizationManager* lm, list<int*> waypointList);
	virtual Behavior* getStartPoint(){return _start;}
	virtual ~Plan();
};

#endif /* PLAN_H_ */
