#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <math.h>

namespace Utils
{
	double AddToAngle(double amount, double angle);
	double MinusFromAngle(double amount, double angle);
	void GetXYInFrontOfPoint(double &X, double &Y, double angle, double distance);
	double DegreesToRadians(double degrees);
	double RadiansToDegrees(double radians);
};

#endif