#include "projectile.h"

Projectile::Projectile()
{

}

void Projectile::computeNewPosition(Tables &tables)
{
	this->x, this->y = this->physics.updateNewPosition(tables);
}