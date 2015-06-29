/*
 * PathPlanner.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include <iostream>
#include "Map.h"
#include <list>

using namespace std;

class PathPlanner
{
public:
	list<int*> a_star_algoritm(Map::position pStart, Map::position pGoal,const Map& map);
private:
	list<int*> reconstruct_path(int x,int y, int** dir_map);
};





#endif /* PATHPLANNER_H_ */
