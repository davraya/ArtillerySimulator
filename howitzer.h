#pragma once

#include "physics.h"
#include "projectile.h"
#include "position.h"

 
class Howitzer
{

private:
   Projectile projectile;
   Physics::Angle a;
   Position position = Position(10000,10000);
   double age;

public:
   void moveBarrel();
   void fire();
   Physics::Angle* getAngle() { return &a; };
   Position getPosition() const;
   bool canFire() const;
   void setAngle();

};

