/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include "Map.h";
#include <fstream>
#include <iostream>
using namespace std;

class ConfigurationManager
{

public:
	void readParameters(char* map, Map::position* pSource, Map::position* pTarget,
						double* dRobotW, double* dRobotH, double* dMapRes,
						double* dGridRes);
};





#endif /* CONFIGURATIONMANAGER_H_ */
