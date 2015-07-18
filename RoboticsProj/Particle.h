/*
 * Particle.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Map.h"
#include "math.h"
#include "Robot.h"

#define LARGE_ANGLE 5.0
#define SMALL_ANGLE 0.5
#define SHORT_DIST 3
#define LONG_DIST 57
//TODO: ADI find normalize factor
#define NORMALIZE_FACTOR 1.7

class Particle
{
private:

    double _X;
    double _Y;
    double _Yaw;
    double _Bel;
    Map* _Map;

public:
    Particle(double x, double y, double yaw, Map* map);
    Particle(double x, double y, double yaw, double belief, Map* map);
    Particle();

    // Properties
    Map::position getPositionOnGrid() const;

    double getBelief() const{
    	return this->_Bel;
    }
    double getX() const{
    	return this->_X;
    }
    double getY() const{
    	return this->_Y;
    }
    double getYaw() const{
    	return this->_Yaw;
    }
    Map* getMap() const{
        return this->_Map;
    }

    // Methods
    void update(double deltaX, double deltaY, double deltaYaw , LaserProxy* laser);
    void updateBel(double deltaX, double deltaY, double deltaYaw , LaserProxy* laser);
    float probByMov(double deltaX, double deltaY, double deltaYaw);
    float probByScan(LaserProxy* laser);

	virtual ~Particle();

};

#endif /* PARTICLE_H_ */
