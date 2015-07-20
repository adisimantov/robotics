/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "pngUtil.h"
#include "ConfigurationManager.h"

#include "Plans/Plan.h"
int main()
{

	/*float angle = atan2(0 + 1, 0 - 1);
	//angle += (0.25 * M_PI);

	cout << angle << endl;*/
	try{

//	Robot robot("10.10.245.65",6665);
Robot robot("localhost",6665);

	Map map("roboticLabMap.png");
	Map mapInf = map.inflateMap(ConfigurationManager::getInstance()->getDRobotW()*1.3,
				   ConfigurationManager::getInstance()->getDRobotH()*1.3);

	Manager manager(&robot, &map, &mapInf);
	manager.run();
	//robot.Move
	} catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}


