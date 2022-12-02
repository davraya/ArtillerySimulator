#include "projectile.h"

Projectile::Projectile()
{

}

void Projectile::computeNewPosition()
{
	this->x, this->y = this->physics.updateNewPosition();
}