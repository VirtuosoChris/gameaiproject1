namespace geometry{


class Vector2D{

public:
  double length();
  double dot(Vector2D);
  double normalize();
  double lengthSquared();
  double cross(Vector2D);
  Vector2D operator+(Vector2D);
  Vector2D operator-(Vector2D);
  Vector2D operator*(double);

  Vector2D(double, double);
  ~Vector2D();
};
	
	
class Line2D{
Vector2D start;
Vector2D end;

public:
	bool intersect(Line2D);
	bool intersectSegment(Line2D);
};








};