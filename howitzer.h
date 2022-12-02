#pragma once

#include "physics.h"


class howitzer
{

private:
   Physics p;
   double age;
public:
   void moveBarrel();
   void fire();
   void getAngle() const;
   void getPosition() const;
   void canFire() const;
   void setAngle();

};

