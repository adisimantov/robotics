/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "pngUtil.h"

#include "Plans/Plan.h"
int main()
{

	//ConvertMapBlackToWhiteAndWhiteToBlack("/usr/robotics/PcBotWorld/hospital_section.png");

	Robot robot("localhost",6665);

	Plan plnOA(&robot);
	Map map(138,95,2.5,10);
	map.loadPngToGrid("roboticLabMap.png");
	Map inflatedMap(map,138,95,2.5,10);
	inflatedMap.inflateMap(30,30);

	Manager manager(&robot, &plnOA, &map, &inflatedMap);
	manager.run();

	//robot.Move();

}
