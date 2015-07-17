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

LocalizationManager::LocalizationManager(Map* map, LaserProxy* laser){

	this->map = map;
	//TODO ADI think if not best to start with only one particle at the known location...
	this->_maxX = map->row_size * (map->map_res / map->grid_res);
	this->_maxY = map->col_size * (map->map_res / map->grid_res);
	double x, y, yaw;
	Map::position start = ConfigurationManager::getInstance()->getPSourceMap();
	Particle *p = new Particle(start.nX,start.nY, start.dAngle* M_PI / 180, map);
	this->_particlesList.push_front(p);

	p->probByScan(laser);
	//create a list of Particles
	/*for (int i = 0; i < 200; i++){
		x = rand() % (this->_maxX + 1);
		y =  rand() % (this->_maxY + 1);
		yaw = dRand(0,6.2);

	}*/
}

Map::position LocalizationManager::getBestParticleOnGrid(){

	//TODO ADI think if not best to return particle instead of position......
	Particle* current;
	Particle* bestParticle = new Particle();
	for (list<Particle*>::iterator it = this->_particlesList.begin(); it != this->_particlesList.end(); it++){
			current = *it;
			if (current->getBelief() > bestParticle->getBelief()){
				bestParticle = current;
			}
	}

	return bestParticle->getPositionOnGrid();
}

void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw, LaserProxy* laser){

	Particle* current;
	double x, y, yaw;
	int index = 1;
	int newIndx = 0;
	for (list<Particle*>::iterator it = this->_particlesList.begin(); it != this->_particlesList.end(); it++){
		current = *it;
		cout << index <<  ". x = " << current->getX() << " y = " << current->getY() << " yaw = " << current->getYaw() << " bel " << current->getBelief()<< endl ;
		index++;
		//TODO ADI check why the hell does the beleif function is broken!!!!
		current->update(deltaX,deltaY,deltaYaw,laser);
		cout <<" check create new particles. bel = " << current->getBelief() << endl;
		if (current->getBelief() > 0.7){
			cout << "create!" << endl;
			for (int i = 0; i < 20; i++){
				newIndx++;
				x = dRand(current->getX() - 30 < 0 ? 0 : current->getX() -30,
							current->getX() + 30 > this->_maxX ? this->_maxX : current->getX() + 30);
				y = dRand(current->getY() - 30 < 0 ? 0 : current->getY() -30,
							current->getY() + 30 >this->_maxY ? this->_maxY : current->getY() + 30);
				yaw = dRand(current->getYaw() - 0.5 < 0 ? 0 : current->getYaw() - 0.5,
							current->getYaw() + 1 > 6.2 ? 6.2 : current->getYaw() + 1);
				Particle* p = new Particle(x,y,yaw,current->getBelief(),current->getMap());
				this->_particlesList.push_front(p);
			}
			cout << "belief = " << current->getBelief() << endl;
		}
		else if (current->getBelief() <= 0.3){
			//TODO ADI check if really removes the current particle
	        this->_particlesList.erase(it++);
	        delete current;
		}
	}
	cout << "there are " << newIndx << " new particles" << endl;
}

list<Map::position> LocalizationManager::convertParticleList(){
	list<Map::position> convertedList;
	Particle* current;
	for (list<Particle*>::iterator itr = this->_particlesList.begin(); itr != this->_particlesList.end(); itr++){
		current = *itr;
		Map::position position;
		position.nX = (int)current->getX();
		position.nY = (int)current->getY();
		convertedList.push_front(position);
	}
	return convertedList;

}


LocalizationManager::~LocalizationManager(){
	 _particlesList.clear();
}
