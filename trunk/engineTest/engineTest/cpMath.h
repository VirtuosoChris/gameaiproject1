#ifndef CPMATH
#define CPMATH
#include "irrlicht.h"

inline double degreesToRadians(double degrees){
return 2*3.14159*degrees/360;
}

inline double radiansToDegrees(double radians){
	return radians*= 57.29578;
}


//finds the quadrant a vector is in
inline int quadrant(vector3df a){
	if(a.X >0 && a.Z>0)return 1;
	if(a.X>0 && a.Z<0)return 4;
	if(a.X < 0 && a.Z>0)return 2;
	if(a.X< 0 && a.Z < 0) return 3;
	return 0;
}

#endif