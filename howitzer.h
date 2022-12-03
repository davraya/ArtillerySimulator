#pragma once

#include "physics.h"
#include "projectile.h"
#include "position.h"

 
class Howitzer
{

private:
   Projectile projectile;
   Physics::Angle a;

   double age;

public:
	Position position;
   void moveBarrel();
   void fire();
   Physics::Angle* getAngle() { return &a; };
   Position getPosition() const;
   bool canFire() const;
   void setAngle();
   void setPositionX(double x);

};

