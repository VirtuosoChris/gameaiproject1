#include<string>

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
		Agent *agentID;

		//Relative distance to agent
		double relDistance;

		//Relative heading to agent
		double relHeading;
		
		Sensor2Data();
		Sensor2Data(Agent *id, double rD, double rH);
		~Sensor2Data();
};


class Sensor3Data{
	//put variables here

public:
	Sensor3Data();
	~Sensor3Data();

};


