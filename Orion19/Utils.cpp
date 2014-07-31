#include "Utils.h"

namespace Utils
{
	/* Retains an angle in degrees whilst adding */
	double AddToAngle(double amount, double angle)
	{
		double tmpAngle = angle;
		tmpAngle += amount;
		if(tmpAngle > 360) tmpAngle = tmpAngle - 360;
		return tmpAngle;
	}

	/* Retains an angle in degrees whilst minusing */
	double MinusFromAngle(double amount, double angle)
	{
		double tmpAngle = angle;
		tmpAngle -= amount;
		if(tmpAngle < 0) tmpAngle = tmpAngle + 360;
		return tmpAngle;
	}

	void GetXYInFrontOfPoint(double &X, double &Y, double angle, double distance)
	{
		X += (distance * cos(angle * M_PI / 180));
		Y += (distance * sin(angle * M_PI / 180));
	}

	double DegreesToRadians(double degrees)
	{
		return (double)(degrees * (M_PI / 180));
	}

	double RadiansToDegrees(double radians)
	{
		return (double)(radians * (180 / M_PI));
	}
};