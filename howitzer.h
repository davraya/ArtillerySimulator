#pragma once

#include "physics.h"
#include "projectile.h"
#include "position.h"
#include "uiDraw.h"
#include <stdlib.h>
#include <ctime>
#include "uiInteract.h" // for INTERFACE

class Howitzer
{

private:
   
   Physics::Angle a;

   double age;
   ogstream gout;

public:

   Howitzer() {
      projectile = new Projectile();
      srand((int)time(0));
      int randX = (rand() % (28000 - 1000)) + 1000;
      this->setPositionX(randX);
      double howitzerX = position.getMetersX();
      double howitzerY = position.getMetersY();
      projectile->initPosition(howitzerX, howitzerX, 0);
      canFire = true;
   }

	Position position;

   void controlBarrel(const Interface* pUI);
   void fire();
   void updateProjectilePosition();
   Physics::Angle* getAngle() { return &a; };
   Position getPosition() const;
   bool canFire;

   Projectile *projectile;

   Position getProjectilePosition();
   vector<Position>::reverse_iterator getReverseIteratorBegin();
   vector<Position>::reverse_iterator getReverseIteratorEnd();
   void displayProjectileStatus();
   double getProjectileAirTime();
   void setPositionX(double x);



};

