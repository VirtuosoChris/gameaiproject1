//Wall feeler sensor
class Sensor1Data{
	int numFeelers;
	double angle;
	float* feelerDistances;

	public: 
		Sensor1Data();
		Sensor1Data(int nf,double a);
		~Sensor1Data();

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


class Sensor3Data{
	//put variables here

public:
	Sensor3Data();
	~Sensor3Data();

};


