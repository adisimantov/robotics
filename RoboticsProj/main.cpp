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
	Robot robot("localhost",6665);

	Map map("roboticLabMap.png");
	Map mapInf = map.inflateMap(ConfigurationManager::getInstance()->getDRobotW(),
				   ConfigurationManager::getInstance()->getDRobotH());

	Manager manager(&robot, &map, &mapInf);
//	manager.run();
	//robot.Move();

}
