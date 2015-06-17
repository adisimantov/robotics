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

	/*Plan plnOA(&robot);
	Manager manager(&robot, &plnOA);
	manager.run();*/

	robot.Move();

}
