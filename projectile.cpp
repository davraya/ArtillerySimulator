#include "projectile.h"

Projectile::Projectile()
{

}

void Projectile::initPosition(double x, double y, double angle)
{
	this->physics.setMyAlt(y);
	this->physics.setMyAngle(angle);
	this->physics.setMyXPosition(x);
	this->physics.setMyYPosition(y);
}

pair<double, double> Projectile::getNewPositionInTime()
{
	pair<double, double> pxy;
	for (int i = 0; i < 50; i++)
	{
		pxy = this->physics.updateNewPosition();
	}
	return pxy;
}

void Projectile::computeNewPosition()
{
	
	pair<double, double> pxy = this->getNewPositionInTime();
	this->getPosition().setMetersX(pxy.first);
	this->getPosition().setMetersY(pxy.second);

	paths.push_back(this->getPosition());
	if (paths.size() == 20)
	{
		paths.erase(paths.begin());
	};
}

