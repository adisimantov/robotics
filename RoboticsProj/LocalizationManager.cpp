/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"


double dRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

LocalizationManager::LocalizationManager(Map* map){

	this->map = map;
	this->_maxX = map->col_size;
	this->_maxY = map->row_size;
	double x, y, yaw;
	//create a list of Particles
	for (int i = 0; i < 100; i++){
		x = rand() % (this->_maxX + 1);
		y =  rand() % (this->_maxY + 1);
		yaw = dRand(0,6.2);
		Particle* p = new Particle(x,y,yaw, map);
		this->_particlesList.push_front(*p);
	}
}

void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw, LaserProxy* laser){

	Particle current;
	double x, y, yaw;
	int index = 1;
	for (list<Particle>::iterator it = this->_particlesList.begin(); it != this->_particlesList.end(); it++){
		current = *it;
		cout << index <<  ". x = " << current.getX() << " y = " << current.getY() << " yaw = " << current.getYaw() << endl ;
		index++;
		current.update(deltaX,deltaY,deltaYaw,laser);
		if (current.getBelief() > 0.7){
			for (int i = 0; i < 50; i++){
					x = dRand(current.getX() - 30 < 0 ? 0 : current.getX() -30,
							current.getX() + 30 > this->_maxX ? this->_maxX : current.getX() + 30);
					y = dRand(current.getY() - 30 < 0 ? 0 : current.getY() -30,
							current.getY() + 30 >this->_maxY ? this->_maxY : current.getY() + 30);
					yaw = dRand(current.getYaw() - 0.5 < 0 ? 0 : current.getYaw() - 0.5,
							current.getYaw() + 1 > 6.2 ? 6.2 : current.getYaw() + 1);
					Particle* p = new Particle(x,y,yaw,current.getBelief(),current.getMap());
					this->_particlesList.push_front(*p);
				}
			cout << "belief = " << current.getBelief() << endl;
		}
		else if (current.getBelief() <= 0.3){
			//TODO ADI check if really removes the current particle
	        this->_particlesList.erase(it++);
		}
	}
}

LocalizationManager::~LocalizationManager(){
	 _particlesList.clear();
}
