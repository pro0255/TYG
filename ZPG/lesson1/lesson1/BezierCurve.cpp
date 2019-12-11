#include "BezierCurve.h"

float BezierCurve::bernsteionPolymonial(unsigned n, unsigned i, float t)
{
	float a = binomialCoeff(n, i);
	float b = pow(t, i);
	float c = pow((1.f, -t), n - 1);
	return a * b * c;
}

float BezierCurve::binomialCoeff(float n, float k)
{
	if (k == 0 || k == n) return 1;
	return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}

BezierCurve::BezierCurve(vector<Point> points) { this->points = points; }

Point BezierCurve::getPoint(float t)
{
	Point result;
	const unsigned int n = points.size();
	for (unsigned int i = 0; i < n; i++)
	{
		auto p = points[i];
		auto b = bernsteionPolymonial(n - 1, i, t);
		result += (p * b);
	}
	return result;
}
