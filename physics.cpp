#include "physics.h"


double Physics::Velocity::updateV(double v0, double a)
{
	return v0 + a * 0.01;
}

double Physics::Accleration::updateA(double f, double m)
{
	return f / m;
}

double Physics::DragForce::updateDF(double c, double p, double v, double area)
{
	double force = 0.5 * c * p * v * v * area;
	return force;
}

double Physics::Altitude::updateAlt(double dy)
{
	return dy;
}

void Physics::Angle::setAngle(double angle)
{
	this->radians = angle;
	this->normalize();
}

double Physics::Angle::updateAngle(double hVel, double vVel)
{
	double new_r = atan2(hVel, vVel);
	return new_r;
}

double Physics::Angle::getRadians()
{
	return this->radians;
}


void Physics::Angle::normalize()
{
	if (this->radians < 0) {
		double negativeRadians = fmod(this->radians, 2 * M_PI);
		this->radians = 2 * M_PI + negativeRadians;
	}

	else {
		this->radians = fmod(this->radians, 2 * 3.1415926);
	}
}

Physics::Physics()
{
	m_V.setV(827.0);
	m_A.setA(0);
	m_F.setDF(0);
	m_Alt.setAlt(0);
	m_Angle.setAngle(0);
	airDensity = 1.2250000;
	mach = 0;
	gravity = 9.807;
	dragCoeffcient = 0;
	s_V = 340.0;
	hVel = 0;
	vVel = 0;
	hAcc = 0;
	vAcc = 0;
	x = 0;
	y = 0;
	t = 0;
	time_per_frame = 0.01;
	mass = 46.7;
	diameter = 0.15489;
	area = computeArea(diameter);
}

double Physics::linerInterpolation(double x0, double y0, double x, double x1, double y1)
{
	double y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);
	return y;
}

double Physics::altitudeTo(map<string, double> map)
{
	double y;
	if (this->m_Alt.getAlt() > 0 && this->m_Alt.getAlt() <= 80000.0)
	{
		double x0 = map.at("x0");
		double x1 = map.at("x1");
		double y0 = map.at("y0");
		double y1 = map.at("y1");

		if (x0 == x1) { return y0; }

		y = this->linerInterpolation(x0, y0, this->m_Alt.getAlt(), x1, y1);
	}
	else
	{
		y = 0.0;
	}

	return y;
}

double Physics::machTo(map<string, double> map)
{
	double y;
	if (this->mach > 0 && this->mach <= 5.000)
	{
		double x0 = map.at("x0");
		double x1 = map.at("x1");
		double y0 = map.at("y0");
		double y1 = map.at("y1");

		if (x0 == x1) { return y0; }

		y = this->linerInterpolation(x0, y0, this->mach, x1, y1);
	}
	else
		y = 0.0;

	return y;
}

double Physics::updateMach()
{
	if (this->m_V.getV() < 0)
	{
		mach = -this->m_V.getV() / this->s_V;
	}
	else
		mach = this->m_V.getV() / this->s_V;
	return mach;
}


double Physics::computeVerticalComponent(Angle angle, double total)
{
	double vComp = total * cos(angle.getAngle());
	return vComp;
}

double Physics::computeHorizontalComponent(Angle angle, double total)
{
	double hComp = total * sin(angle.getAngle());
	return hComp;
}

double Physics::computeTotalComponent(double hComp, double vComp)
{
	double total = sqrt(vComp * vComp + hComp * hComp);
	return total;
}

double Physics::computeDistance(double v, double a, double t)
{
	return v * t + 0.5 * a * t * t;
}

double Physics::computeArea(double d)
{
	double area;
	if (d > 0)
	{
		area = M_PI * 0.5 * d * 0.5 * d;
	}
	else
	{
		area = -1;
	}
	return area;

}

double Physics::updateNewPosition(Tables table)
{
	// intial the horizontal and vertical velocity
	this->hVel = computeHorizontalComponent(this->m_Angle, this->m_V.getV());
	this->vVel = computeVerticalComponent(this->m_Angle, this->m_V.getV());

	while (this->m_Alt.getAlt() >= 0)
	{
		// current air density
		this->airDensity = altitudeTo(table.getDensity(this->m_Alt.getAlt()));
		// current gravity
		this->gravity = altitudeTo(table.getGravity(this->m_Alt.getAlt()));
		// current sound speed
		this->s_V = altitudeTo(table.getSpeedOfSound(this->m_Alt.getAlt()));
		// current mach
		this->mach = updateMach();
		// current drag coefficient
		this->dragCoeffcient = machTo(table.getDrag(this->mach));
		// current drag force
		this->m_F.setDF(this->m_F.updateDF(this->dragCoeffcient, this->airDensity, this->m_V.getV(), this->area));

		// the accleeration due to the drag force
		double a_F = this->m_A.updateA(this->m_F.getDF(), this->mass);
		// horizontal acceleration
		this->hAcc = -computeHorizontalComponent(this->m_Angle, a_F);
		// vertical acceleration
		this->vAcc = -this->gravity - computeVerticalComponent(this->m_Angle, a_F);

		// new x and new y
		double xDistance = computeDistance(this->hVel, this->hAcc, this->time_per_frame);
		double yDistance = computeDistance(this->vVel, this->vAcc, this->time_per_frame);
		this->x = this->x + xDistance;
		this->y = this->y + yDistance;

		// new alttitude
		this->m_Alt.setAlt(this->m_Alt.updateAlt(this->y));

		if (this->m_Alt.getAlt() < 0)
		{
			double xPrev = this->x - xDistance;
			double yPrev = this->y - yDistance;
			this->t -= 0.01;
			this->x = this->linerInterpolation(yPrev, xPrev, 0.0, this->y, this->x);
			this->y = 0;
			this->m_Alt.setAlt(-1.0);
		}
		// new acceleration (this is acctually useless)
		this->m_A.setA(-computeTotalComponent(this->hAcc, this->vAcc));
		// new horizontal and vertical velocity
		this->hVel = this->m_V.updateV(this->hVel, this->hAcc);
		this->vVel = this->m_V.updateV(this->vVel, this->vAcc);
		// new angle
		this->m_Angle.setAngle(this->m_Angle.updateAngle(hVel, vVel));
		// new total velocity
		this->m_V.setV(computeTotalComponent(this->hVel, this->vVel));

		this->t = this->t + 0.01;
		return this->x, this->y;
	}

}