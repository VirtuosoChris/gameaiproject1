#include "Sensors.h"


Sensor1Data::Sensor1Data(int nf,double a){
angle = a;
numFeelers = nf;
feelerDistances = new float[nf];

}