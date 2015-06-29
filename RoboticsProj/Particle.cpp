/*
 * Particle.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "Particle.h"

Particle::Particle(double x, double y, double yaw, double belife, Map* map){
	this->_X = x;
	this->_Y = y;
	this->_Yaw = yaw;
	this->_Bel = belife;
	this->_Map = map;
}

Particle::Particle(double x, double y, double yaw, Map* map):
	Particle(x,y,yaw,1.0, map){
}


Particle::Particle(): Particle(0,0,0,0,NULL){
}

float Particle::probByMov(double detlaX, double deltaY, double deltaYaw){

	double distance = sqrt(pow(detlaX, 2) + pow(deltaY, 2));
	float disProb;

	if (distance < SHORT_DIST){
		disProb = 1;
	}
	else if (distance < LONG_DIST){
		disProb = 1 - (distance/SHORT_DIST) * 0.05;
	}
	else{
		disProb = 0.04;
	}

	double absYaw = deltaYaw > 0 ? deltaYaw : (-1) * deltaYaw;
	float yawProb;

	if (absYaw < SMALL_ANGLE){
		yawProb = 1;
	}
	else if (absYaw < LARGE_ANGLE){
		yawProb = 1 - (absYaw/SMALL_ANGLE) * 0.1;
	}
	else {
		yawProb = 0.4;
	}

	float prob = (disProb + yawProb) / 2.0;

	return prob;
}

float Particle::probByScan(LaserProxy* laser){

	int gridX;
	int gridY;
	int obsticleDistanceCm;
	int match = 0;

	//TODO ADI
	for (int i = 0; i < 666; i++){
		obsticleDistanceCm = (*laser)[i] * 100;
		gridX = this->_X + (obsticleDistanceCm / this->_Map->grid_res) * cos(this->_Yaw + Robot::getRadianByIndex(i));
		gridY = this->_Y + (obsticleDistanceCm / this->_Map->grid_res) * sin(this->_Yaw + Robot::getRadianByIndex(i));

		//TODO: check if the X,Y cell is occupied
		if (gridX >= 0 && gridY >= 0 && gridY <= this->_Map->col_size && gridX <= this->_Map->row_size){

			if (obsticleDistanceCm >= 4 && (this->_Map->getCellStatus(gridX, gridY) == 0)){
				match ++;
			}
			else if (this->_Map->getCellStatus(gridX, gridY) == 1){
				match ++;
			}
		}
	}

	return (match / 666.0);
}

void Particle::update(double deltaX, double deltaY, double deltaYaw , LaserProxy* laser){
	this->_X += deltaX;
	this->_Y += deltaY;
	this->_Yaw += deltaYaw;

	double predBel = this->_Bel * this->probByMov(deltaX,deltaY,deltaYaw);
	this->_Bel = predBel * this->probByScan(laser) * NORMALIZE_FACTOR;
}

Particle::~Particle() {

}
