#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "physics.h"
#include "position.h"
#include "tables.h"

using namespace std;

class Projectile
{
public:
	Projectile() { airTime = 0.0; };
	Position &getPosition() { return this->p; };
	double getDegree() { return this->physics.getDegrees(); };
	void initPosition(double x, double y, double angle);
	double getAltitude() { return this->physics.getAltitude(); };
	double getSpeed() { return this->physics.getSpeed(); };
	double getAirTime() { return airTime; };
	double setAirTime(double airTime) { this->airTime = airTime; };
	void increaseAirTime(double increment) { airTime += increment; };

	void computeNewPosition();
	vector<Position> paths;
private:
	double airTime;
	Physics physics;
	double mass;
	double diameter;
	double area;
	Position p;
	pair<double, double> getNewPositionInTime();
	int count = 0;
};