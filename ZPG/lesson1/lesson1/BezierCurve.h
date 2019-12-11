#pragma once
#include <vector>
#include "glm/vec2.hpp"
using namespace std;

typedef glm::vec2 Point;
class BezierCurve
{
private:
	vector<Point> points;
	float bernsteionPolymonial(unsigned int n, unsigned int i, float t);
	float binomialCoeff(float n, float k);
public:
	BezierCurve(vector<Point> points);
	Point getPoint(float t);
};

