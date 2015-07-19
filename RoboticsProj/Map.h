/*
 * Map.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "Robot.h"
#include <list>

using namespace std;

class Map
{

public:
	int row_size;
	int col_size;
	double map_res;
	double grid_res;

	enum cell
	{
		FREE = 0,
		OCCUPIED = 1,
		UNKNOWN = -1
	};

	struct position
	{
		int nX;
		int nY;
		double dAngle;
	};

private:
	cell **cMap;//[100][100];

public:
	Map(int nRowSize, int nColSize, double nMapRes, double nGridRes);
	Map(const Map& m, int nRowSize, int nColSize, double nMapRes, double nGridRes);
	Map(const char* filename);

	void readMapFromPngIntoGrid();
	Map inflateMap(double fRobotX, double fRobotY);
	void realPosToMapPos(double fX, double fY, position& pMap);
	void mapPosToRealPos(double fX, double fY, position& pReal);
	void realPosToMapPos(position& pReal, position& pMap);
	void mapPosToRealPos(position& pMap, position& pReal);
	void MapPosToGridPos(double fX, double fY, position& pMap);
	void MapPosToGridPos(position& pGrid, position& pMap);
	void gridPosToMapPos(double fX, double fY, position& pReal);
	void loadPngToGrid(const char* filename);
	int  getCellStatus(int nX,int nY) const;
	void updateCellStatus(int nX,int nY, cell cStatus);
	void printParticle(list<position> particlesList);
	void printParticle(list<int*> particlesList);
	bool isOccupied(int x, int y) const;
};

#endif /* MAP_H_ */
