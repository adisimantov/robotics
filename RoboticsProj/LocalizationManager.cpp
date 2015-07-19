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
	this->_maxX = map->row_size / (map->map_res / map->grid_res);
	this->_maxY = map->col_size / (map->map_res / map->grid_res);
	Map::position start = ConfigurationManager::getInstance()->getPSourceMap();
	Particle *p = new Particle(start.nX,start.nY, start.dAngle* M_PI / 180, map);
	this->_particlesList.push_front(p);

//	p->probByScan(laser);

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
	Particle* bestParticle = NULL;
	for (list<Particle*>::iterator it = this->_particlesList.begin(); it != this->_particlesList.end(); it++){
			current = *it;
			if (bestParticle == NULL || current->getBelief() > bestParticle->getBelief()){
				bestParticle = current;
			}
	}
	cout << "best Particle: (" << bestParticle->getX() << "," << bestParticle->getY() << "," << bestParticle->getYaw() << "," << bestParticle->getBelief() << ")" << endl;
	cout << "best Particle: (" << bestParticle->getX() << "," << bestParticle->getY() << "," << bestParticle->getYaw()*3.14/180 << "," << bestParticle->getBelief() << ")" << endl;

	return bestParticle->getPositionOnGrid();
}

bool compare_particle (Particle* first, Particle* second)
{
	return first->getBelief() >= second->getBelief();
}
void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw, LaserProxy* laser)
{

	Particle* current;
	double x, y, yaw;
	int newIndx = 0;
	list<Particle*> newParticales;
	list<Particle*> delParticales;
	deltaX 	 *= ConfigurationManager::getInstance()->getDMapRes();
	deltaY 	 *= ConfigurationManager::getInstance()->getDMapRes();
	for (list<Particle*>::iterator it = this->_particlesList.begin(); it != this->_particlesList.end(); ){
		current = *it;
		//cout << " x = " << current->getX() / 4 << " y = " << current->getY() / 4 << " yaw = " << current->getYaw() << " bel " << current->getBelief()<< endl ;
		current->update(deltaX,deltaY,deltaYaw,laser);
		//cout <<" check create new particles. bel = " << current->getBelief() << endl;
		if (current->getBelief() > 0.7){
			//cout << "create!" << endl;
			//	cout << "Create from Particle (" << current->getX()<< "," << current->getY() << "," << current->getYaw() << "," << current->getBelief() << ")" << endl;
			for (int i = 0; i < 20; i++){
				newIndx++;
				x = dRand(current->getX() - 30 < 0 ? 0 : current->getX() -30,
							current->getX() + 30 > this->_maxX ? this->_maxX : current->getX() + 30);
				y = dRand(current->getY() - 30 < 0 ? 0 : current->getY() -30,
							current->getY() + 30 >this->_maxY ? this->_maxY : current->getY() + 30);
				yaw = dRand(current->getYaw() - 0.2 < 0 ? 0 : current->getYaw() - 0.2,
							current->getYaw() + 0.2 > 6.2 ? 6.2 : current->getYaw() + 0.2);
				//yaw = dRand(current->getYaw() - 0.5 ,current->getYaw() + 0.5);
				if (yaw > M_PI)
				{
					yaw = -(2*M_PI - yaw);
				}
				else if (yaw < -M_PI)
				{
					yaw = (2*M_PI + yaw);
				}
				Particle* p = new Particle(x,y,yaw,current->getBelief() - 0.0001,current->getMap());
				//p->updateBel(deltaX,deltaY,deltaYaw,laser);
				//Particle* p = new Particle(x,y,yaw,-1,current->getMap());
				//cout << "New Particle (" << p->getX()<< "," << p->getY() << "," << p->getYaw() << "," << p->getBelief() << ")" << endl;
				//this->_particlesList.push_front(p);
				newParticales.push_back(p);
			}
			it++;
			//cout << "belief = " << current->getBelief() << endl;
		}
		else if (current->getBelief() <= 0.3){

	        it = this->_particlesList.erase(it);
	        delParticales.push_back(current);
		} else
		{
			it++;
		}

	}
	//cout << "there are " << newIndx << " new particles" << endl;
	_particlesList.splice(_particlesList.end(),newParticales);
	/*if (!_particlesList.empty()){
		this->map->printParticle(this->convertParticleList());
	}*/
	if (_particlesList.size() < 20){
		cout << "less then 20!! " << _particlesList.size() << "!! and  " << newIndx << " new ones..." << endl;
		//cout << "add paarticles" << endl;
		delParticales.sort(compare_particle);
		while (_particlesList.size() < 20 && delParticales.size() > 0)
		{
			Particle *addPar = delParticales.front();
			delParticales.pop_front();
			_particlesList.push_back(addPar);
		}
		//this->map->printParticle(this->convertParticleList());

	}
	else if (_particlesList.size() > 200)
	{
		_particlesList.sort(compare_particle);
		while(_particlesList.size() != 200)
		{
			_particlesList.pop_back();
		}
	}
	while(!delParticales.empty()){
		Particle *dellPar = delParticales.front();
		delParticales.pop_front();
		delete dellPar;
	}
}

list<Map::position> LocalizationManager::convertParticleList(){
	list<Map::position> convertedList;
	Particle* current;
	for (list<Particle*>::iterator itr = this->_particlesList.begin(); itr != this->_particlesList.end(); itr++){
		current = *itr;
		convertedList.push_front(current->getPositionOnGrid());
	}
	return convertedList;
}


LocalizationManager::~LocalizationManager(){
	this->map->printParticle(convertParticleList());
	_particlesList.clear();
}
