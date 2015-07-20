/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"
#include <fstream>
#include <iostream>

using namespace std;

ConfigurationManager* ConfigurationManager::cm;

ConfigurationManager* ConfigurationManager::getInstance(){
	if (!ConfigurationManager::cm){
		ConfigurationManager::cm= new ConfigurationManager;
	}
	return ConfigurationManager::cm;
}

ConfigurationManager::ConfigurationManager()
{
	loadParameters();
}

void ConfigurationManager::loadParameters()
{
	ifstream fParameters;
	string   sLine;
	fParameters.open("parameters.txt");
	//Check if the file is open
	if(fParameters.is_open())
	{
		//Get map file
		getline(fParameters,sLine);
		sLine = sLine.substr(5);
		this->fileName = (char*)sLine.c_str();

		//Get source position
		getline(fParameters,sLine);
		this->pSourceMap.nX = atoi(sLine.substr(12).c_str());
		getline(fParameters,sLine);
		this->pSourceMap.nY = atoi(sLine.substr(12).c_str());
		getline(fParameters,sLine);
		this->pSourceMap.dAngle = atoi(sLine.substr(16).c_str());

		//Get target position
		getline(fParameters,sLine);
		this->pTargetMap.nX = atoi(sLine.substr(8).c_str());
		getline(fParameters,sLine);
		this->pTargetMap.nY = atoi(sLine.substr(8).c_str());

		//Get robot size
		getline(fParameters,sLine);
		this->dRobotW = atof(sLine.substr(12).c_str());
		getline(fParameters,sLine);
		this->dRobotH = atof(sLine.substr(12).c_str());

		//Get map resolution
		getline(fParameters,sLine);
		this->dMapRes = atof(sLine.substr(17).c_str());

		//Get grid resolution
		getline(fParameters,sLine);
		this->dGridRes = atof(sLine.substr(18).c_str());

		int diference = this->dGridRes / this->dMapRes;
		this->pSource.nX = this->pSourceMap.nX / diference;
		this->pSource.nY = this->pSourceMap.nY / diference;
		this->pSource.dAngle = this->pSourceMap.dAngle;
		this->pTarget.nX = this->pTargetMap.nX / diference;
		this->pTarget.nY = this->pTargetMap.nY / diference;

		fParameters.close();
	}
	else
		cout << "Unable to open parameters file";
}

char* ConfigurationManager::getFileName()
{
	return this->fileName;
}
Map::position ConfigurationManager::getPSource()
{
	return this->pSource;
}
Map::position ConfigurationManager::getPTarget()
{
	return this->pTarget;
}
Map::position ConfigurationManager::getPSourceMap()
{
	return this->pSourceMap;
}
Map::position ConfigurationManager::getPTargetMap()
{
	return this->pTargetMap;
}
double ConfigurationManager::getDRobotW()
{
	return this->dRobotW;
}
double ConfigurationManager::getDRobotH()
{
	return this->dRobotH;
}
double ConfigurationManager::getDMapRes()
{
	return this->dMapRes;
}
double ConfigurationManager::getDGridRes()
{
	return this->dGridRes;
}
