/*
 * WaypointsManager.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <list>
#include "Map.h"
using namespace std;
class WaypointsManager
{
public:
	list<int*> choosePoints(list<int*> list, const Map& map);
};


#endif /* WAYPOINTSMANAGER_H_ */
