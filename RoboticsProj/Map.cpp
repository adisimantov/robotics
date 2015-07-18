/*
 * Map.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include "pngUtil.h"
#include "math.h"
#include "ConfigurationManager.h"

using namespace std;

// Constructor
Map::Map(int nRowSize, int nColSize, double nMapRes, double nGridRes)
{
	// Initialize map attributes
	this->row_size = nRowSize;
	this->col_size = nColSize;
	this->map_res  = nMapRes;
	this->grid_res = nGridRes;

	// Build the grid and initialize in -1(UNKNOWN)
	this->cMap = new cell*[nRowSize];

	// Initialize the map in -1(UNKNOWN)
	for(int nRowI=0; nRowI<nRowSize; nRowI++)
	{
		this->cMap[nRowI] = new cell[nColSize];
		for(int nColI=0; nColI<nColSize; nColI++)
		{
			this->cMap[nRowI][nColI] = UNKNOWN;
		}
	}
}

//TODO: AA NOY get only map
Map::Map(const Map& m,int nRowSize, int nColSize, double nMapRes, double nGridRes)
{
	// Initialize map attributes
	this->row_size = nRowSize;
	this->col_size = nColSize;
	this->map_res  = nMapRes;
	this->grid_res = nGridRes;

	// Build the grid and initialize it according to the m parameter
	this->cMap = new cell*[nRowSize];

	// Initialize the map in -1(UNKNOWN)
	for(int nRowI=0; nRowI<nRowSize; nRowI++)
	{
		this->cMap[nRowI] = new cell[nColSize];
		for(int nColI=0; nColI<nColSize; nColI++)
		{
			this->cMap[nRowI][nColI] = m.cMap[nRowI][nColI];
		}
	}
}

Map::Map(const char* filename)
{
	// Initialize map attributes

	this->map_res  = ConfigurationManager::getInstance()->getDMapRes();
	this->grid_res = ConfigurationManager::getInstance()->getDGridRes();

	int nDeference = this->grid_res / this->map_res;

	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);
	this->row_size = ceil(width / nDeference)+ 1;
	this->col_size = ceil(height / nDeference) + 1;

	// Build the grid and initialize in -1(UNKNOWN)
	this->cMap = new cell*[this->row_size];

	// Initialize the map in -1(UNKNOWN)
	for(int nRowI=0; nRowI<this->row_size; nRowI++)
	{
		this->cMap[nRowI] = new cell[this->col_size];
		for(int nColI=0; nColI<this->col_size; nColI++)
		{
			this->cMap[nRowI][nColI] = UNKNOWN;
		}
	}

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels

	navImage.resize(this->row_size * this->col_size * 4 );

	// Put on grid
	cell cMapStatus, cGridStatus;
	//unsigned char color;

	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			cGridStatus = this->cMap[x / nDeference][y / nDeference];
			if (cGridStatus != OCCUPIED)
			{
				/**if (image[y * width * 4 + x * 4 + 0] == 255
						  && image[y * width * 4 + x * 4 + 1] == 255
						  && image[y * width * 4 + x * 4 + 2] == 255)*/
				if (image[y * width * 4 + x * 4 + 0]
				  || image[y * width * 4 + x * 4 + 1]
				  || image[y * width * 4 + x * 4 + 2])
				{
					cMapStatus = FREE;
				}

				else
				{
					cMapStatus = OCCUPIED;

				}
				this->cMap[x / nDeference][y / nDeference] = cMapStatus;
			}
		}
	}

	std::vector<unsigned char>().swap(image);

	unsigned char color;

	for (y = 0; y < this->col_size; y++)
		for (x = 0; x < this->row_size; x++)
		{
			if (this->cMap[x][y] == OCCUPIED)
				color = 0;
			else
				color = 255;
			navImage[y * this->row_size * 4 + x * 4 + 0] = color;
			navImage[y * this->row_size * 4 + x * 4 + 1] = color;
			navImage[y * this->row_size * 4 + x * 4 + 2] = color;
			navImage[y * this->row_size * 4 + x * 4 + 3] = 255;
		}
	encodeOneStep("NoyTest.png", navImage, this->row_size, this->col_size);

	std::vector<unsigned char>().swap(navImage);
}

void Map::loadPngToGrid(const char* filename)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels

	navImage.resize(this->row_size * this->col_size * 4 );

	// Put on grid
	cell cMapStatus, cGridStatus;
	//unsigned char color;
	int nDeference = this->grid_res / this->map_res;//this->map_res / this->grid_res;
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			cGridStatus = this->cMap[x / nDeference][y / nDeference];
			if (cGridStatus != OCCUPIED)
			{
				/**if (image[y * width * 4 + x * 4 + 0] == 255
				          && image[y * width * 4 + x * 4 + 1] == 255
				          && image[y * width * 4 + x * 4 + 2] == 255)*/
				if (image[y * width * 4 + x * 4 + 0]
				  || image[y * width * 4 + x * 4 + 1]
				  || image[y * width * 4 + x * 4 + 2])
				{
					cMapStatus = FREE;
				}

				else
				{
					cMapStatus = OCCUPIED;

				}
				this->cMap[x / nDeference][y / nDeference] = cMapStatus;
			}
		}
	}

	std::vector<unsigned char>().swap(image);

	unsigned char color;

	for (y = 0; y < this->col_size; y++)
		for (x = 0; x < this->row_size; x++)
		{
			if (this->cMap[x][y] == OCCUPIED)
				color = 0;
			else
				color = 255;
			navImage[y * this->row_size * 4 + x * 4 + 0] = color;
			navImage[y * this->row_size * 4 + x * 4 + 1] = color;
			navImage[y * this->row_size * 4 + x * 4 + 2] = color;
			navImage[y * this->row_size * 4 + x * 4 + 3] = 255;
		}
	encodeOneStep("NoyTest.png", navImage, this->row_size, this->col_size);

	std::vector<unsigned char>().swap(navImage);

}

Map Map::inflateMap(double fRobotX, double fRobotY)
{
	Map inflate(this->row_size, this->col_size,this->map_res, this->grid_res);
	int x,y,inflateX,inflateY;
	int nRobotXGrid, nRobotYGrid;
	nRobotXGrid = ceil(fRobotX / this->grid_res);
	nRobotYGrid = ceil(fRobotY / this->grid_res);

	for(x = 0; x < this->row_size; x++)
	{
		for(y = 0; y < this->col_size; y++)
		{
			if(this->cMap[x][y] == OCCUPIED)
			{
				// Inflate the cell
				for(inflateX = x - nRobotXGrid; inflateX < x + nRobotXGrid; inflateX++)
				{
					if(inflateX >= 0 && inflateX < this->row_size)
					{
					for(inflateY = y - nRobotYGrid; inflateY < y + nRobotYGrid; inflateY++)
					{
						if(inflateY >= 0 && inflateY < this->col_size)
						{
							inflate.cMap[inflateX][inflateY] = OCCUPIED;
							//this->cMap[inflateX][inflateY] = OCCUPIED;
						}
					}
					}
				}
			}
		}
	}
	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(this->row_size * this->col_size * 4);
	unsigned char color;

	for (y = 0; y < this->col_size; y++)
		for (x = 0; x < this->row_size; x++)
		{
			if (inflate.cMap[x][y] == OCCUPIED)
				color = 0;
			else
				color = 255;
			navImage[y * this->row_size * 4 + x * 4 + 0] = color;
			navImage[y * this->row_size * 4 + x * 4 + 1] = color;
			navImage[y * this->row_size * 4 + x * 4 + 2] = color;
			navImage[y * this->row_size * 4 + x * 4 + 3] = 255;
		}

	encodeOneStep("InflateTest.png", navImage, this->row_size, this->col_size);
	std::vector<unsigned char>().swap(navImage);
	return inflate;
}


void Map::printParticle(list<int*> particlesList)
{
	int *currNode;
	unsigned x, y;
	unsigned char color;
	std::vector<unsigned char> navImage; //the raw pixels

	navImage.resize(this->row_size * this->col_size * 4);

		for (y = 0; y < this->col_size; y++)
			for (x = 0; x < this->row_size; x++)
			{
				if (this->cMap[x][y] == OCCUPIED)
					color = 0;
				else
					color = 255;
				navImage[y * this->row_size * 4 + x * 4 + 0] = color;
				navImage[y * this->row_size * 4 + x * 4 + 1] = color;
				navImage[y * this->row_size * 4 + x * 4 + 2] = color;
				navImage[y * this->row_size * 4 + x * 4 + 3] = 255;

			}
		while(!particlesList.empty())
		{
			currNode = particlesList.front();
			x=currNode[0];
			y=currNode[1];
			navImage[y * this->row_size * 4 + x * 4 + 0] = 0;
			navImage[y * this->row_size * 4 + x * 4 + 1] = 0;
			navImage[y * this->row_size * 4 + x * 4 + 2] = 255;
			navImage[y * this->row_size * 4 + x * 4 + 3] = 255;
			particlesList.pop_front();
			delete currNode;
		}
		encodeOneStep("NoyTestInts.png", navImage, this->row_size, this->col_size);

		std::vector<unsigned char>().swap(navImage);
}

void Map::realPosToMapPos(double fX, double fY, position& pMap)
{
	pMap.nX = fX / map_res;
	pMap.nY = fY / map_res;
}

void Map::mapPosToRealPos(double fX, double fY, position& pReal)
{
	pReal.nX = fX * map_res;
	pReal.nY =  fY * map_res;
}

void Map::MapPosToGridPos(double fX, double fY, position& pMap)
{
	int difrence = this->grid_res / this->map_res;
	pMap.nX = fX / difrence;
	pMap.nY = fY / difrence;
}

void Map::gridPosToMapPos(double fX, double fY, position& pReal)
{
	int difrence = this->grid_res / this->map_res;
	pReal.nX = fX * difrence;
	pReal.nY =  fY * difrence;
}

void Map::MapPosToGridPos(position& pGrid, position& pMap)
{
	int difrence = this->grid_res / this->map_res;
	pGrid.nX = pMap.nX / difrence;
	pGrid.nY = pMap.nY / difrence;
	pGrid.dAngle = pMap.dAngle;
}

void Map::realPosToMapPos(position& pReal, position& pMap)
{
	pMap.nX = pReal.nX / grid_res;
	pMap.nY = pReal.nY / grid_res;
	pMap.dAngle = pReal.dAngle;

}
void Map::mapPosToRealPos(position& pMap, position& pReal)
{
	pReal.nX = pMap.nX * grid_res;
	pReal.nY = pMap.nY * grid_res;
	pMap.dAngle = pReal.dAngle;
}

int  Map::getCellStatus(int nX,int nY) const
{
	return this->cMap[nX][nY];
}

void Map::updateCellStatus(int nX,int nY, cell cStatus)
{
	this->cMap[nX][nY] = cStatus;
}

void Map::printParticle(list<position> particlesList)
{
	position currNode;
	unsigned x, y;
	unsigned char color;
	std::vector<unsigned char> navImage; //the raw pixels

	navImage.resize(this->row_size * this->col_size * 4);

		for (y = 0; y < this->col_size; y++)
			for (x = 0; x < this->row_size; x++)
			{
				if (this->cMap[x][y] == OCCUPIED)
					color = 0;
				else
					color = 255;
				navImage[y * this->row_size * 4 + x * 4 + 0] = color;
				navImage[y * this->row_size * 4 + x * 4 + 1] = color;
				navImage[y * this->row_size * 4 + x * 4 + 2] = color;
				navImage[y * this->row_size * 4 + x * 4 + 3] = 255;

			}
		while(!particlesList.empty())
		{
			currNode = particlesList.front();
			x=currNode.nX;
			y=currNode.nY;
			navImage[y * this->row_size * 4 + x * 4 + 0] = 0;
			navImage[y * this->row_size * 4 + x * 4 + 1] = 255;
			navImage[y * this->row_size * 4 + x * 4 + 2] = 0;
			navImage[y * this->row_size * 4 + x * 4 + 3] = 255;
			particlesList.pop_front();
		}
		encodeOneStep("NoyTest.png", navImage, this->row_size, this->col_size);

		std::vector<unsigned char>().swap(navImage);
}
