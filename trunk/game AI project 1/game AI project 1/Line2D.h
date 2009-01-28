#include "Vector2D.h"
class Line2D{
Vector2D start;
Vector2D end;

public:
	bool intersect(Line2D);
	bool intersectSegment(Line2D);
}
;