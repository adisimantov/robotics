/*
 * GoToWaypoint.h
 *
 */

#ifndef GOTOWAYPOINT_H_
#define GOTOWAYPOINT_H_

#include "Behavior.h"
#include "../WaypointsManager.h"

class GoToWaypoint: public Behavior {
private:
	int _wayPointX;
	int _wayPointY;
	LocalizationManager* _lm;
public:
	GoToWaypoint(Robot* robot, int x, int y, LocalizationManager* lm);
	bool startCond();
	bool stopCond();
	void action();
	void printDetails();
	virtual ~GoToWaypoint();
};

#endif /* GOTOWAYPOINT_H_ */
