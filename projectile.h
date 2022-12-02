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
private:

	void computeNewPosition(Tables &tables);

	Physics physics;
	Position  projectilePath[20];
	double x;
	double y;
	double mass;
	double diameter;
	double area;

};