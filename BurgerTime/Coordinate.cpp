#include "Coordinate.h"
#include "Constants.h"

Coordinate:: Coordinate(double x, double y) {
	this->x = x;
	this->y = y;
}

Coordinate::Coordinate() : Coordinate(0, 0) { }

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

void Coordinate::copyFrom(const Coordinate& source) {
	this->x = source.x;
	this->y = source.y;
}

double Coordinate::getX() {
	return this->x;
}

double Coordinate::getY() {
	return this->y;
}

void Coordinate::setX(double x) {
	this->x = x;
}

void Coordinate::setY(double y) {
	this->y = y;
}
