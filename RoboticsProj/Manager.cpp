/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"
//TODO ADI delete
#include <unistd.h>
#include <iostream>
using namespace std;

Manager::Manager(Robot* robot, Map* map, Map* inflatedMap) {

	cout << "manager start" << endl;
	this->_regularMap = map;
	this->_inflatedMap = inflatedMap;
	Map::position start = ConfigurationManager::getInstance()->getPSource();
	Map::position end = ConfigurationManager::getInstance()->getPTarget();

	list<Map::position> l;
	l.push_front(start);
	l.push_front(end);
	map->printParticle(l);
	WaypointsManager w;
	PathPlanner p;
	cout << "start - (" << start.nX << "," << start.nY<< ")" << endl;
	cout << "end - (" << end.nX << "," << end.nY<< ")" << endl;

	cout << "a star start"<< endl;
	list<int*> aStarList = p.a_star_algoritm(start, end, *this->_inflatedMap);
	cout << "a star finish"<< endl;
	//map->printParticle(aStarList);
	cout << "waypoint start"<< endl;
	list<int*> waypointList = w.choosePoints(aStarList);
	cout << "waypoint finish"<< endl;

	//map->printParticle(waypointList);

/*	int *curr;
	while (!waypointList.empty()){
		curr = waypointList.front();
		cout << "(" << curr[0] << "," << curr[1] << ")" << endl;
		waypointList.pop_front();
	}*/
	this->_lm = new LocalizationManager(this->_regularMap, robot->getLaserProxy());
	Plan* pln = new Plan(robot, this->_lm, waypointList);
	this->_robot = robot;
	this->_curr = pln->getStartPoint();
}

void Manager::run()
{
	double x,y,yaw, x1,y1,yaw1;

	_robot->read();
	x1 = _robot->getPosX();
	y1 = _robot->getPosY();
	yaw1 = _robot->getYaw();

	if(!(_curr->startCond()))
		return;
	_curr->action();
	//cout << "start manager loop" << endl;
	while(_curr !=NULL)
	{
		_robot->read();

		//cout << "check stop cond" << endl;
		while(_curr->stopCond() == false)
		{
			_robot->read();

			x =  _robot->getPosX();
			y =  _robot->getPosY();
			yaw =  _robot->getYaw();
			//cout << "dx = " << (x - x1) << " dy " <<(y - y1) << " dyaw " << (yaw - yaw1) << endl;
			this->_lm->update((x - x1),(y - y1),(yaw - yaw1),_robot->getLaserProxy());
			//this->_lm->update((0.234),(0.123),(0.1012),_robot->getLaserProxy());

			_robot->read();

			x1 = x;
			y1 = y;
			yaw1 = yaw;

			_curr->action();
		}
		_curr = _curr->selectNext();
		_robot->setSpeed(0,0);
		_robot->read();
	}
}

Manager::~Manager() {
	delete _robot;
	delete _regularMap;
	delete _inflatedMap;
	delete _curr;
}
