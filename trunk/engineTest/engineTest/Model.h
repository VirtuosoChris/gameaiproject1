

#ifndef MODEL
#define MODEL
#include <irrlicht.h>

using namespace irr;

struct Model{
	scene::IAnimatedMesh* mesh;
	video::ITexture* texture;
	double scale;
};

#endif