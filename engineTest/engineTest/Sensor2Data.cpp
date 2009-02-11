#ifndef SENSORS
#include "Sensors.h"
#endif


Sensor2Data::Sensor2Data(){
	//default
}

Sensor2Data::Sensor2Data(Agent *id, double rD, double rH){
	//Assign values to Sensor2Data object
	agentID = id;
	relDistance = rD;
	relHeading = rH;
}


Sensor2Data::~Sensor2Data(){
	//destructor
}
