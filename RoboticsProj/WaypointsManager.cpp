/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */
#include "WaypointsManager.h"
#include <list>
#include <math.h>

using namespace std;
list<int*> WaypointsManager::choosePoints(list<int*> list,const Map& map)
{
	std::list<int*> lResult;
	int nPrevX,nPrevY,nXdir,nYdir;

	int *currNode, *prev, *prev2, *last, *newP;
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

	int distance,x,y;
	double angle;
	bool isFree;
	// Less points:
	std::list<int*> testList;
	if(!lResult.empty())
	{
		prev2 = lResult.front();
		//nPrevX = currNode[0];
		//nPrevY = currNode[1];
		testList.push_back(prev2);
		lResult.pop_front();

		if(!lResult.empty())
		{
			prev = lResult.front();
			lResult.pop_front();

			while(!lResult.empty())
			{
				currNode = lResult.front();
				// Check if the way is empty
				//--------------------------
				//Calac distance
				isFree = true;
				distance = sqrt(pow(currNode[0]-prev2[0],2) + pow(currNode[1]-prev2[1],2));
				angle = atan2(currNode[1]-prev2[1], currNode[0]-prev2[0]);
				for(int i=1; i<distance && isFree;i++){
					x= i * cos(angle) + prev2[0];
					y= i * sin(angle) + prev2[1];
					if(map.getCellStatus(x,y) == Map::OCCUPIED)
					{
						isFree = false;
					}

				}

				if(isFree)
				{
					prev = currNode;
				}
				else
				{
					testList.push_back(prev);
					prev2 = prev;
					prev = currNode;
				}

				lResult.pop_front();
			}

		}
		testList.push_back(prev);
	}


	// Add points
	if(!testList.empty())
		{
			prev = testList.front();
			//nPrevX = currNode[0];
			//nPrevY = currNode[1];
			lResult.push_back(prev);
			testList.pop_front();
			while(!testList.empty())
			{
				currNode = testList.front();
				distance = sqrt(pow(currNode[0]-prev[0],2) + pow(currNode[1]-prev[1],2));
				if(distance > 10)
				{
					// Add new one
					x= distance / 10 * cos(angle) + prev[0];
					y= distance / 10 * sin(angle) + prev[1];
					newP = new int[2];
					newP[0] = x;
					newP[1] = y;
					lResult.push_back(newP);
				}

				lResult.push_back(currNode);
				prev = currNode;
				testList.pop_front();
			}
		}
		lResult.push_back(prev);

	return lResult;
}


