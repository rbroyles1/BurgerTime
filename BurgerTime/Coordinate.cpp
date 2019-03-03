#include "Coordinate.h"
#include "Constants.h"

Coordinate:: Coordinate(double x, double y, bool useSetter) {
	if (useSetter) {
		this->setX(x);
		this->setY(y);
	} else {
		this->x = x;
		this->y = y;
	}
}

Coordinate::Coordinate(double x, double y) : Coordinate(x, y, true) { }

Coordinate::Coordinate() : Coordinate(0, 0) { }

Coordinate Coordinate::operator+(const Coordinate& rhs) {
	return Coordinate(x + rhs.x, y + rhs.y, false);
}

Coordinate Coordinate::operator-(const Coordinate& rhs) {
	return Coordinate(x - rhs.x, y - rhs.y, false);
}

Coordinate Coordinate::operator*(const Coordinate& rhs) {
	return Coordinate(x * rhs.x, y * rhs.y, false);
}

Coordinate Coordinate::operator/(const double& rhs) {
	return Coordinate(x / rhs, y / rhs, false);
}

Coordinate Coordinate::operator*(const double& rhs) {
	return Coordinate(x * rhs, y * rhs, false);
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
	this->x = x * RESOLUTION_MULTIPLIER;
}

void Coordinate::setY(double y) {
	this->y = y * RESOLUTION_MULTIPLIER;
}
