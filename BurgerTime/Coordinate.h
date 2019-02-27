#pragma once

class Coordinate {
public:
	double x;
	double y;

	Coordinate(double x, double y) {
		this->x = x;
		this->y = y;
	}

	Coordinate() {
		this->x = 0;
		this->y = 0;
	}

	Coordinate operator+(const Coordinate& rhs) 	{
		return Coordinate(x + rhs.x, y + rhs.y);
	}

	Coordinate operator-(const Coordinate& rhs) {
		return Coordinate(x - rhs.x, y - rhs.y);
	}

	Coordinate operator*(const Coordinate& rhs) {
		return Coordinate(x * rhs.x, y * rhs.y);
	}

	Coordinate operator/(const double& rhs) {
		return Coordinate(x / rhs, y / rhs);
	}

	Coordinate operator*(const double& rhs) {
		return Coordinate(x * rhs, y * rhs);
	}

	double dotProduct(const Coordinate& rhs) {
		return x * rhs.x + y * rhs.y;
	}
};