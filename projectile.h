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
	Projectile();
	Position &getPosition() { return this->p; };
	double getDegree() { return this->physics.getDegrees(); };
	void initPosition(double x, double y, double angle);

	void computeNewPosition();
	vector<Position> paths;
private:

	Physics physics;
	double mass;
	double diameter;
	double area;
	Position p;
	pair<double, double> getNewPositionInTime();
	int count = 0;
};