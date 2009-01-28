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