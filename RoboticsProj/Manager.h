/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/Plan.h"
#include "Robot.h"
#include "Map.h"
#include "LocalizationManager.h"
#include "PathPlanner.h"
#include "ConfigurationManager.h"
class Manager {
private:
	Behavior* _curr;
	Robot* _robot;
	Map* _regularMap;
	Map* _inflatedMap;
	LocalizationManager* _lm;

public:
	Manager(Robot* robot, Map* map, Map* inflatedMap);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
