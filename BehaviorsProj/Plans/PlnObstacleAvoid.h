/*

 * PlnObstacleAvoid.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user


#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_


#include "../behaviors/A.h"
#include "../behaviors/B.h"
#include "../behaviors/C.h"


class PlnObstacleAvoid: public Plan {
	Behavior* _beh[3];

public:
	PlnObstacleAvoid(Robot* robot);
	Behavior* getStartPoint(){return _start;}
	virtual ~PlnObstacleAvoid();
};

#endif  PLNOBSTACLEAVOID_H_
*/
