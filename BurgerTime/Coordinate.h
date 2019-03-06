#pragma once

class Coordinate {
	double x;
	double y;

public:
	Coordinate(double x, double y);
	Coordinate();

	Coordinate operator+(const Coordinate& rhs);
	Coordinate operator-(const Coordinate& rhs);
	Coordinate operator*(const Coordinate& rhs);
	Coordinate operator/(const double& rhs);
	Coordinate operator*(const double& rhs);

	double dotProduct(const Coordinate& rhs);
	void copyFrom(const Coordinate& source);

	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};