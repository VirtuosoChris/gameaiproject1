#include "Line2D.h"

class Wall{

double width;
Line2D wall;

public:
  Wall(Line2D,double);
  ~Wall();

  bool intersect(Line2D);

};
