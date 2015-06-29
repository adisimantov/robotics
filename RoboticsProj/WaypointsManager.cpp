/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */
#include "WaypointsManager.h"
#include <list>

using namespace std;
list<int*> WaypointsManager::choosePoints(list<int*> list)
{
	std::list<int*> lResult;
	int nPrevX,nPrevY,nXdir,nYdir;

	int *currNode, *prev;
	if(!list.empty())
	{
		prev = list.front();
		//nPrevX = currNode[0];
		//nPrevY = currNode[1];
		list.pop_front();
		while(!list.empty())
		{
			currNode = list.front();
			if(currNode[0]-prev[0] != nXdir || currNode[1]-prev[1] != nYdir)
			{
				lResult.push_back(prev);
				nXdir = currNode[0] - prev[0];
				nYdir = currNode[1]-prev[1];

			}

			prev = currNode;
			list.pop_front();
		}
	}
	lResult.push_back(prev);
	return lResult;
}


