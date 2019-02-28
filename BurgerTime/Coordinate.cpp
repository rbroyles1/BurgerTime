#include "Coordinate.h"

Coordinate::Coordinate(double x, double y) {
	this->x = x;
	this->y = y;
}

Coordinate::Coordinate() {
	this->x = 0;
	this->y = 0;
}

Coordinate Coordinate::operator+(const Coordinate& rhs) {
	return Coordinate(x + rhs.x, y + rhs.y);
}

Coordinate Coordinate::operator-(const Coordinate& rhs) {
	return Coordinate(x - rhs.x, y - rhs.y);
}

Coordinate Coordinate::operator*(const Coordinate& rhs) {
	return Coordinate(x * rhs.x, y * rhs.y);
}

Coordinate Coordinate::operator/(const double& rhs) {
	return Coordinate(x / rhs, y / rhs);
}

Coordinate Coordinate::operator*(const double& rhs) {
	return Coordinate(x * rhs, y * rhs);
}

double Coordinate::dotProduct(const Coordinate& rhs) {
	return x * rhs.x + y * rhs.y;
}