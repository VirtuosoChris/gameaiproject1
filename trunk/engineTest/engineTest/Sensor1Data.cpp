#include "Sensors.h"


Sensor1Data::Sensor1Data(){
	//default
}

Sensor1Data::Sensor1Data(int nf,double a){
	angle = a;
	numFeelers = nf;
	feelerDistances = new float[nf];
}

Sensor1Data::~Sensor1Data(){
	//destructor
}

int Sensor1Data::getNumFeelers(){
return numFeelers;
}
