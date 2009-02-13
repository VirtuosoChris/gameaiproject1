#ifndef SENSORS
#include "Sensors.h"
#endif

WallSensorData::WallSensorData(){
	//default
}

WallSensorData::WallSensorData(int nf,double a, float mr){
	maxRange = mr;
	angle = a;
	numFeelers = nf;
	feelerDistances = new float[nf];
}

WallSensorData::~WallSensorData(){
	//destructor
}

int WallSensorData::getNumFeelers(){
return numFeelers;
}


double WallSensorData::getAngle(){

return angle;
}
