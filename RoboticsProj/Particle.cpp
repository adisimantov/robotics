
#include "Particle.h"
#include "ConfigurationManager.h"

Particle::Particle(double x, double y, double yaw, double belife, Map* map){
	this->_X = x;
	this->_Y = y;
	this->_Yaw = yaw;
	this->_Bel = belife;
	this->_Map = map;
}

Particle::Particle(double x, double y, double yaw, Map* map):
	Particle(x,y,yaw,1.0, map){
}

Particle::Particle(): Particle(0,0,0,0,NULL){
}

float Particle::probByMov(double detlaX, double deltaY, double deltaYaw){

	double distance = sqrt(pow(detlaX, 2) + pow(deltaY, 2));
	float disProb;

	if (distance < SHORT_DIST){
		disProb = 1;
	}
	else if (distance < LONG_DIST){
		disProb = 1 - (distance/SHORT_DIST) * 0.05;
	}
	else{
		disProb = 0.04;
	}

	double absYaw = deltaYaw > 0 ? deltaYaw : (-1) * deltaYaw;
	float yawProb;

	if (absYaw < SMALL_ANGLE){
		yawProb = 1;
	}
	else if (absYaw < LARGE_ANGLE){
		yawProb = 1 - (absYaw/SMALL_ANGLE) * 0.1;
	}
	else {
		yawProb = 0.4;
	}

	float prob = (disProb + yawProb) / 2.0;

	return prob;
}

float Particle::probByScan(LaserProxy* laser){
	 // Variables definition - Particle probability
	double alfa;

	double minAngle = laser->GetMinAngle();
	double maxAngle = laser->GetMaxAngle();

	int scanCount = laser->GetCount();

	Map::position gridPos = this->getPositionOnGrid();
	Map::position gridPosObs;
	list<Map::position> l;

	// Calculate the scan increment
	double dScanIncrement = (maxAngle - minAngle) / scanCount;

	int hits = 0;

	for(int i = 0; i < scanCount; i++)
	{
		// Calculate the current beam to check if there is an obstacle
		alfa = dScanIncrement * i + minAngle;
		double dLaserBeam = laser->GetRange(i);

		double dObstacleX =  dLaserBeam * ConfigurationManager::getInstance()->getDGridRes()
				* cos(gridPos.dAngle + alfa) + gridPos.nX;
		double dObstacleY =  (-1) * dLaserBeam * ConfigurationManager::getInstance()->getDGridRes()
				* sin(gridPos.dAngle + alfa) + gridPos.nY;
		gridPosObs.nX = dObstacleX;
		gridPosObs.nY = dObstacleY;
		gridPosObs.dAngle = 0;

  /*      if(!((int)dObstacleY >= this->_Map->row_size ||
        		(int)dObstacleX >= this->_Map->col_size ||
        		(int)dObstacleY < 0 || (int)dObstacleX < 0))
        {
		        if(this->_Map->getCellStatus(dObstacleX,dObstacleY) == Map::OCCUPIED)
		        {
		        	hits++;
		        }
	     }*/
		//cout << "laserBeam = " << dLaserBeam << " getCellStatus(" << gridPosObs.nX << "," << gridPosObs.nY << ")" << endl;

		if (gridPosObs.nX >= 0 && gridPosObs.nY >= 0 && gridPosObs.nX < this->_Map->row_size && gridPosObs.nY < this->_Map->col_size){
				//cout << "grid check = (" << obsticlePosition.nX << "," << obsticlePosition.nY << ")" << endl;
				l.push_back(gridPosObs);
				//cout << "laserBeam = " << dLaserBeam << " getCellStatus(" << gridPosObs.nX << "," << gridPosObs.nY <<
				//		") = " << this->_Map->getCellStatus(gridPosObs.nX, gridPosObs.nY) << endl;
				if (dLaserBeam == 4 && (this->_Map->getCellStatus(gridPosObs.nX, gridPosObs.nY) == Map::FREE)){
					hits ++;
				}
				else if (dLaserBeam < 4 && this->_Map->getCellStatus(gridPosObs.nX, gridPosObs.nY) == Map::OCCUPIED){
					hits ++;
				}
			}
	}
	//this->_Map->printParticle(l);
	//cout << "hits = " << hits << endl;

	return (hits / 667.0);
}

//TODO ADI dosent work!
void Particle::update(double deltaX, double deltaY, double deltaYaw , LaserProxy* laser){

	if (deltaX != 0 || deltaY !=0 || deltaYaw != 0){
		this->_X += deltaX;
		this->_Y += deltaY;
		this->_Yaw += deltaYaw;

		this->updateBel(deltaX, deltaY, deltaYaw, laser);
	}
}

void Particle::updateBel(double deltaX, double deltaY, double deltaYaw , LaserProxy* laser)
{
	double predBel = this->_Bel * this->probByMov(deltaX,deltaY,deltaYaw);
	this->_Bel = predBel * this->probByScan(laser) * NORMALIZE_FACTOR;
	if (this->_Bel > 1){
		this->_Bel = 1;
	}
}


Map::position Particle::getPositionOnGrid() const{

	Map::position position;
	position.nX = this->getX();
	position.nY = this->getY();
	position.dAngle = this->getYaw();
	Map::position grid;
	this->_Map->MapPosToGridPos(grid, position);

	return grid;
}

Particle::~Particle() {

}
