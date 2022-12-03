#pragma once

#include <iostream>
#include <map>
#include <string>
#include <math.h>
#include <cmath>
#include "tables.h"

using namespace std;

#define M_PI 3.14159265358979323846


class Physics
{
	

public:

	class Angle
	{
	public:
		Angle()
		{
			this->radians = 0;
		}
		void setAngle(double angle);
		double getRadians() { return this->radians; };
		double updateAngle(double vVel, double hVel);
		double getDegrees();
	private:
		
		void normalize();
		double radians;
	};

	class Altitude
	{
	public:
		double getAlt() { return altitude; }
		void setAlt(double alt) { this->altitude = alt; }
		double updateAlt(double dy);
	private:
		double altitude;
	};

	class Velocity
	{

	public:
		double getV() { return velocity; }
		void setV(double v) { this->velocity = v; }
		double updateV(double v0, double a);
	private:
		double velocity;
	};

	class Accleration
	{
	public:
		double getA() { return accleration; }
		void setA(double a) { this->accleration = a; }
		double updateA(double f, double m);
	private:
		double accleration;
	};

	class DragForce
	{
	public:
		double getDF() { return dragForce; }
		void setDF(double df) { this->dragForce = df; }
		double updateDF(double c, double p, double v, double area);
	private:
		double dragForce;
	};

	Physics();

	void setMyAlt(double alt) { this->m_Alt.setAlt(alt); }
	void setMyAngle(double angle) {
		while (angle > 360) {
			angle -= 360;
		}
		double radians = (angle * M_PI) / 180.0;
		this->m_Angle.setAngle(radians);
	}
	void setMyVel(double v) { this->m_V.setV(v); }
	void setMyAcc(double a) { this->m_A.setA(a); }
	void setMyXPosition(double x) { this->x = x; }
	void setMyYPosition(double y) { this->y = y; }
	double getDegrees() { return this->m_Angle.getDegrees(); }


	// lab 07 demo
	pair<double, double> updateNewPosition();

	double t;
private:
	//  test purpose
	Velocity m_V;
	Accleration m_A;
	DragForce m_F;
	Altitude m_Alt;
	Angle m_Angle;
	Tables tables;
	double mach;
	double gravity;
	double dragCoeffcient;
	double airDensity;
	double s_V;
	double hVel;
	double vVel;
	double hAcc;
	double vAcc;
	double time_per_frame;
	// demo
	double x;
	double y;
	double mass;
	double diameter;
	double area;

	double computeArea(double d);
	double machTo(map<string, double> map);
	double altitudeTo(map<string, double> map);
	double updateMach();
	double linerInterpolation(double d0, double r0, double d, double d1, double r1);
	double computeVerticalComponent(Angle angle, double total);
	double computeHorizontalComponent(Angle angle, double total);
	double computeTotalComponent(double hComp, double vComp);
	double computeDistance(double v, double a, double t);

}; 
