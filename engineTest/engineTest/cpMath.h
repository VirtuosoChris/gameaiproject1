#ifndef CPMATH
#define CPMATH

inline double degreesToRadians(double degrees){
return 2*3.14159*degrees/360;
}

inline double radiansToDegrees(double radians){
	return radians*= 57.29578;
}

#endif