#include "howitzer.h"



Position Howitzer::getPosition() const
{
    return position;
}

void Howitzer::setPositionX(double x)
{
    this->position.setMetersX(x);
}