#include "geometry.h"

namespace gameInterface{

using namespace geometry;



class Entity{
public:
geometry::Vector2D position;
void updateSensors();
};



class Agent:public Entity{
	geometry::Vector2D heading;
};




class Wall{

double width;
geometry::Line2D wall;

public:
	Wall(geometry::Line2D,double);
  ~Wall();

  bool intersect(geometry::Line2D);

};



class Game{
public:
void addEntity(Entity);
void addAgent(Agent);
void addWall(Wall);
void gameUpdate();
};





};