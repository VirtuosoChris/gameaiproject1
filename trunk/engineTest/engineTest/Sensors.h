#define SENSORS

#include<string>
#include<iostream>
#include<vector>

//dummy agent class
class Agent;

//Wall feeler sensor
class Sensor1Data{

	int numFeelers;
	double angle;

	public: 

		
	float maxRange;

		Sensor1Data();
		Sensor1Data(int nf,double a, float mr = 5000.0f);
		~Sensor1Data();

		int getNumFeelers();
		double getAngle();

		float* feelerDistances;


};

class Sensor2Data{
	public:
		//Agent Identification Number
		int agentID;

		//Relative distance to agent
		double relDistance;

		//Relative heading to agent
		double relHeading;
		
		Sensor2Data();
		Sensor2Data(int id, double rD, double rH);
		~Sensor2Data();
};
class PieSensor{
	public:
		//Agent *pt;
		int num_slices;
		double range;
		double orientation;
		double angle;
		int *areas;
	
		double degreesToRadians(double degrees){return 2*3.14159*degrees/360;}
		PieSensor();
		PieSensor(int);
		~PieSensor();
		void Detect(std::vector<Agent*> *);
		void showPieSensor();
};

