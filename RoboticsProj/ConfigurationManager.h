/*

 * ConfigurationManager.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
*/


#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

class ConfigurationManager
{
	static ConfigurationManager* cm;
private:
	 char* fileName;
	 Map::position pSource;
	 Map::position pSourceMap;
	 Map::position pTarget;
	 Map::position pTargetMap;
	 double dRobotW;
	 double dRobotH;
	 double dMapRes;
	 double dGridRes;


	ConfigurationManager();
public:
	 static ConfigurationManager* getInstance();
		void loadParameters();

		char* getFileName();
		Map::position getPSource();
		Map::position getPTarget();
		Map::position getPSourceMap();
		Map::position getPTargetMap();
		double getDRobotW();
		double getDRobotH();
		double getDMapRes();
		double getDGridRes();

};


#endif  CONFIGURATIONMANAGER_H_
