#include "howitzer.h"



void Howitzer::controlBarrel(const Interface* pUI)
{

   // move a large amount
   if (pUI->isRight())
      a += 0.05;
   if (pUI->isLeft())
      a -= 0.05;

   // move by a little

   if (pUI->isUp())
      a += 0.01;
   if (pUI->isDown())
      a -= 0.01;

   // fire that gun
   if (pUI->isSpace())
   {
      if (canFire)
      {
         fire();
         canFire = false;
      }

   }

}

void Howitzer::fire()
{  
    delete projectile;
    projectile = NULL;
    projectile = new Projectile();
   projectile->initStatus();
   projectile->initPosition(position.getMetersX(), position.getMetersY(), a.getDegrees());

}

void Howitzer::updateProjectilePosition()
{
   projectile->increaseAirTime(0.5);

}

Position Howitzer::getPosition() const
{
    return position;
}


Position Howitzer::getProjectilePosition()
{
   
   return projectile->getPosition();

}

vector<Position>::reverse_iterator Howitzer::getReverseIteratorBegin()
{
   vector<Position>::reverse_iterator begin = projectile->paths.rbegin();
   return begin;

}

vector<Position>::reverse_iterator Howitzer::getReverseIteratorEnd()
{
   vector<Position>::reverse_iterator end = projectile->paths.rend();
   return end;

}

void Howitzer::displayProjectileStatus()
{

   Position label;
   label.setPixelsX(560);
   label.setPixelsY(460);
   gout.setPosition(label);
   gout << "hang time: " << projectile->getAirTime() << "s\n"
      << "distance:  " << projectile->getPosition().getMetersX() << "m\n"
      << "altitude:  " << projectile->getAltitude() << " m\n"
      << "speed:     " << projectile->getSpeed() << " m/s\n";

}

double Howitzer::getProjectileAirTime()
{
   return projectile->getAirTime();
}

void Howitzer::setPositionX(double x)
{
    this->position.setMetersX(x);
}

