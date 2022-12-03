#pragma once

#include "physics.h"
#include "projectile.h"
#include "position.h"
#include "uiDraw.h"

class Howitzer
{

private:
   Projectile projectile;
   Physics::Angle a;
   Position position = Position(10000,10000);
   double age;
   ogstream gout;

public:
   Howitzer() {
      double howitzerX = position.getMetersX();
      double howitzerY = position.getMetersY();
      projectile.initPosition(howitzerX, howitzerX, 0);
   }
   void moveBarrel();
   void fire();
   void updateProjectilePosition();
   Physics::Angle* getAngle() { return &a; };
   Position getPosition() const;
   bool canFire() const;
   void setAngle();
   Position getProjectilePosition();
   vector<Position>::reverse_iterator getReverseIteratorBegin();
   vector<Position>::reverse_iterator getReverseIteratorEnd();
   void displayProjectileStatus();
   double getProjectileAirTime();

};

