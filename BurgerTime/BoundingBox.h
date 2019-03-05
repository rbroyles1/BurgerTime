#pragma once
#include "Coordinate.h"

class BoundingBox {
	Coordinate* boxSize;

public:
	BoundingBox(Coordinate* boxSize);

	bool isIntersecting(Coordinate* thisCenter, Coordinate* targetCenter, BoundingBox* boundingBox);

	~BoundingBox();
};

