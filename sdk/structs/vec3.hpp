#pragma once
#include <math.h>
#include <tuple>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct vec3
{
	double x, y, z;

	double distance(const vec3& other)
	{
		return sqrt(pow(y - other.y, 2) + pow(sqrt(pow(x - other.x, 2) + pow(z - other.z, 2)), 2));
	}

	std::pair<double, double> getAngles(const vec3& other)
	{
		double dX = other.x - x;
		double dY = other.y - y;
		double dZ = other.z - z;

		return std::make_pair((atan2(dZ, dX) * 180.f / M_PI) - 90.f, -atan2(dY, sqrt(dX * dX + dZ * dZ)) * 180.f / M_PI);
	}
};

inline float wrapTo180(float value)
{
	if (value >= 180.f)
		value -= 360.f;
	if (value < -180.f)
		value += 360.f;
	return value;
}

inline double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}