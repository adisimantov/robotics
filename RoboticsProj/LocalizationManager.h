/*
 * LocalizationManager.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

using namespace std;
#include "Robot.h"
#include "Particle.h"
#include "Map.h"
#include <list>

class LocalizationManager
{
private:
	list<Particle> _particlesList;
	int _maxX;
	int _maxY;
	Map* map;

public:
	LocalizationManager(Map* map);
	void update(double deltaX, double deltaY, double deltaYaw, LaserProxy* laser);
	virtual ~LocalizationManager();
};


#endif /* LOCALIZATIONMANAGER_H_ */
