/*
 * Map.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "Robot.h"

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

	void readMapFromPngIntoGrid();
	void inflateMap(double fRobotX, double fRobotY);
	void realPosToMapPos(double fX, double fY, position& pMap);
	void mapPosToRealPos(double fX, double fY, position& pReal);
	void loadPngToGrid(const char* filename);
};

#endif /* MAP_H_ */
