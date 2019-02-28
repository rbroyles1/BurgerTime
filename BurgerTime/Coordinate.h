#pragma once

class Coordinate {
public:
	double x;
	double y;

	Coordinate(double x, double y);
	Coordinate();

	Coordinate operator+(const Coordinate& rhs);
	Coordinate operator-(const Coordinate& rhs);
	Coordinate operator*(const Coordinate& rhs);
	Coordinate operator/(const double& rhs);
	Coordinate operator*(const double& rhs);

	double dotProduct(const Coordinate& rhs);
};