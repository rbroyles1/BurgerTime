#include <cmath>
#include "BoundingBox.h"

BoundingBox::BoundingBox(Coordinate * boxSize) {
	this->boxSize = boxSize;
}

bool BoundingBox::isIntersecting(Coordinate* thisCenter, Coordinate* targetCenter, BoundingBox * boundingBox) {
	return abs(thisCenter->getX() - targetCenter->getX()) * 2 < this->boxSize->getX() + boundingBox->boxSize->getX()
		&& abs(thisCenter->getY() - targetCenter->getY()) * 2 < this->boxSize->getY() + boundingBox->boxSize->getY();
}

BoundingBox::~BoundingBox() {
	delete this->boxSize;
}