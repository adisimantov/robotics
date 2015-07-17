/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "PathPlanner.h"
#include <queue>
#include "Node.h"
#include "Map.h"
#include <string>
#include <sstream>
#include <list>
//using namespace std;

//Dimensions
const int horizontalSize = 556; //X
const int verticalSize = 380;   //Y

//Directions
/**const int dir = 4;
static int dirX[dir] = {1,0,-1,0};
static int dirY[dir] = {0,1,0,-1};
*/
const int dir = 8;
static int dirX[dir] = {1,0,-1,0,-1,-1,1,1};
static int dirY[dir] = {0,1,0,-1,-1,1,-1,1};


//static int came_from[horizontalSize][verticalSize];
list<int*> PathPlanner::a_star_algoritm(Map::position pStart, Map::position pGoal,
									const Map& map)
{

	//Nodes set
	static int **closeGrid = new int*[map.row_size];
	static int **openGrid = new int*[map.row_size];
	static int **dir_map = new int*[map.row_size];
	//static int **came_from = new int*[map.row_size];


	Node *startNode, *currentNode, *neighborNode;
	int neighborX,neighborY,index=0;
	std::priority_queue<Node> openset[2];

	// Initialize the map in -1(UNKNOWN)
	for(int nRowI=0; nRowI<map.row_size; nRowI++)
	{
		closeGrid[nRowI] = new int[map.col_size];
		openGrid[nRowI] = new int[map.col_size];
		dir_map[nRowI] = new int[map.col_size];
		//came_from[nRowI] = new int[map.col_size];

		for(int nColI=0; nColI<map.col_size; nColI++)
		{
			closeGrid[nRowI][nColI] = 0;
			openGrid[nRowI][nColI]=0;
			dir_map[nRowI][nColI]=-1;
		}
	}

	// Create start node and push it into the openset
	startNode = new Node(pStart.nX,pStart.nY,0,0); //g_score = 0
	startNode->updatePriority(pGoal.nX,pGoal.nY);  //Calc f_score

	openset[index].push(*startNode);
	openGrid[pStart.nX][pStart.nY] = startNode->getPriority();

	while(!openset[index].empty())
	{
		//Get the node in openset having the lowest f_score value
		currentNode = new Node(openset[index].top().getxPos(),
								openset[index].top().getyPos(),
								openset[index].top().getDistance(),
								openset[index].top().getPriority());
		//If the node is the goal
		if(currentNode->getxPos()==pGoal.nX && currentNode->getyPos()==pGoal.nY)
		{
			return reconstruct_path(currentNode->getxPos(),currentNode->getyPos(),dir_map);
		}
		else
		{
			//Remove current from openset
			openset[index].pop();
			openGrid[currentNode->getxPos()][currentNode->getyPos()]=0;

			//Add current to closeset
			closeGrid[currentNode->getxPos()][currentNode->getyPos()]=1;

			//Add possible neighbors
			for(int i=0;i<dir;i++)
			{
				neighborX = currentNode->getxPos()+dirX[i];
				neighborY = currentNode->getyPos()+dirY[i];

				//Check if the cell is valid
				if(neighborX >= 0 && neighborY >= 0 &&
					neighborX < map.row_size && neighborY < map.col_size)
				{
					if(map.getCellStatus(neighborX,neighborY) != Map::OCCUPIED &&
					   closeGrid[neighborX][neighborY] == 0)
					{
						 neighborNode = new Node (neighborX,
												  neighborY,
												  currentNode->getDistance(),
												  currentNode->getPriority());

						 //calculate the fscore and gscore
						 neighborNode->updateDistance();
						 neighborNode->updatePriority(pGoal.nX,pGoal.nY);

						 //If neighbor is not in openset
						 if(openGrid[neighborX][neighborY]==0)
						 {
							 //Add neighbor to openset
							 openGrid[neighborX][neighborY] = neighborNode->getPriority();
							 openset[index].push(*neighborNode);
							 //Set parent in dirmap
							 dir_map[neighborX][neighborY] = i;
						 }
						 else
						 {
							 //Check if the path to the neighbor is better
							 if(openGrid[neighborX][neighborY] > neighborNode->getPriority())
							 {
								 openGrid[neighborX][neighborY] = neighborNode->getPriority();
								 dir_map[neighborX][neighborY] = i;

								 //Switch neighbor
								 while(!openset[index].empty())
								 {
									 if(openset[index].top().getxPos()==neighborX &&
									 	openset[index].top().getyPos()==neighborY)
									 {
										 openset[1-index].push(*neighborNode);
									 }
									 else
									 {
										 openset[1-index].push(openset[index].top());
									 }
									 openset[index].pop();
								 }

								 index = 1-index;
							 }
							 else
								 delete neighborNode;
						 }
					}
				}
			}
		}

		delete currentNode;
	}
}

list<int*> PathPlanner::reconstruct_path(int x,int y, int** dir_map)
{
	list<int*> lPath;
	int *currNode = new int[2];

	string path;
	stringstream ss;
	int nextX,nextY,direction;
	while(dir_map[x][y] != -1)
	{
		currNode = new int[2];
		currNode[0]=x;
		currNode[1]=y;
		lPath.push_front(currNode);
		direction = dir_map[x][y];
		x = dirX[direction]*(-1) + x;
		y = dirY[direction]*(-1) + y;
	}

	return lPath;
	/**
	if(dir_map[x][y] == -1)
		lPath.push_front()
		return "";
	else
	{
		return reconstruct_path(nextX,nextY, dir_map) + path;
	}*/
}


