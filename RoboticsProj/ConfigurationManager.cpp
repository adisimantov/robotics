/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h";
#include <fstream>
#include <iostream>

using namespace std;

void ConfigurationManager::readParameters(char* map, Map::position *pSource, Map::position* pTarget,
						double* dRobotW, double* dRobotH, double* dMapRes, double* dGridRes)
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
		map = (char*)sLine.c_str();

		//Get source position
		getline(fParameters,sLine);
		(*pSource).nX = atoi(sLine.substr(12).c_str());
		getline(fParameters,sLine);
		(*pSource).nY = atoi(sLine.substr(12).c_str());
		getline(fParameters,sLine);
		(*pSource).dAngle = atoi(sLine.substr(16).c_str());

		//Get target position
		getline(fParameters,sLine);
		(*pTarget).nX = atoi(sLine.substr(8).c_str());
		getline(fParameters,sLine);
		(*pTarget).nY = atoi(sLine.substr(8).c_str());

		//Get robot size
		getline(fParameters,sLine);
		*dRobotW = atof(sLine.substr(12).c_str());
		getline(fParameters,sLine);
		*dRobotH = atof(sLine.substr(12).c_str());

		//Get map resolution
		getline(fParameters,sLine);
		*dMapRes = atof(sLine.substr(17).c_str());

		//Get grid resolution
		getline(fParameters,sLine);
		*dGridRes = atof(sLine.substr(18).c_str());

		fParameters.close();
	}
	else
		cout << "Unable to open parameters file";

}


