#include "howitzer.h"



void Howitzer::fire()
{
    
   projectile.initPosition(position.getMetersX(), position.getMetersY(), a.getRadians());

}

void Howitzer::updateProjectilePosition()
{
   projectile.increaseAirTime(0.5);
   projectile.computeNewPosition();

}

Position Howitzer::getPosition() const
{
    return position;
}

Position Howitzer::getProjectilePosition()
{
   
   return projectile.getPosition();

}

vector<Position>::reverse_iterator Howitzer::getReverseIteratorBegin()
{
   vector<Position>::reverse_iterator begin = projectile.paths.rbegin();
   return begin;

}

vector<Position>::reverse_iterator Howitzer::getReverseIteratorEnd()
{
   vector<Position>::reverse_iterator end = projectile.paths.rend();
   return end;

}

void Howitzer::displayProjectileStatus()
{

   Position label;
   label.setPixelsX(560);
   label.setPixelsY(460);
   gout.setPosition(label);
   gout << "hang time: " << projectile.getAirTime() << "s\n"
      << "distance:  " << projectile.getPosition().getMetersX() << "m\n"
      << "altitude:  " << projectile.getAltitude() << " m\n"
      << "speed:     " << projectile.getSpeed() << " m/s\n";

}

double Howitzer::getProjectileAirTime()
{
   return projectile.getAirTime();
}
