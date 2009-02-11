#define NUMFEELERS 10
#include "Agent.h"
#include "InputHandler.h"
#include <cmath>
#include <string>
#include <vector>

using namespace irr;
inline double degreesToRadians(double degrees){
return 2*3.14159*degrees/360;
}



void Agent::updateSensor1(){


 core::line3d<f32> line;
 core::vector3df intersection;
 core::triangle3df triangle;

 core::vector3df orientVector;

 
 orientVector = core::vector3df((float)cos(degreesToRadians(orientation)),0.0f,(float)sin(degreesToRadians(orientation)));
 line.start = mynodep->getPosition();
 line.end = line.start + orientVector * s1d->maxRange;
 
	//	billboard->setVisible(true);
		 
//std::vector<Agent*> a;
//a = *agentList;
//(*agentList)[0] = NULL;
// a[0] = NULL;
 
 double  baseAngle = orientation - s1d->getAngle()/2.0;
 double  increment = s1d->getAngle() / s1d->getNumFeelers();



		 for(int i = 0; i < s1d->getNumFeelers(); i++){
				
			double angle = i * increment + baseAngle;
			core::vector3df feelerVector = core::vector3df(
				(float)cos(degreesToRadians(angle)), 0.0f, 
				(float)sin(
				degreesToRadians(angle)
				));

			 float t1 = 0.0f;
			 
			 line.start = mynodep->getPosition();
			 line.end = line.start + orientVector * s1d->maxRange;
 

			 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle))
				 s1d->feelerDistances[i] = 
				 (t1= (intersection.X - mynodep->getPosition().X)) * t1 + (t1 = (intersection.Z - mynodep->getPosition().Z)* t1);
			
		    else{
			 s1d->feelerDistances[i] =s1d->maxRange;
			}
		 }
}


void Agent::updateSensor2(){
	//Clear all previous entries
	s2d.clear();

	//Run sensor and store values in vector
	this->proximitySensor(1000.0);
}
void Agent::update(irr::ITimer* timer){

updateSensor1();
updateSensor2();
 
}


void Agent::processMessage(Message*){

}



Agent::Agent(Model m, irr::core::vector3df p, irr::scene::ISceneManager* mgr):position(p),model(m){
	

	s1d = new Sensor1Data(5,45);

	if(mgr){
	mynodep = mgr->addAnimatedMeshSceneNode(m.mesh);
	mynodep->setPosition(p);
	mynodep->setMaterialTexture(0,m.texture);
	mynodep->setMaterialFlag(video::EMF_LIGHTING, false);
	mynodep->setMD2Animation(scene::EMAT_STAND);
	mynodep->setRotation(irr::core::vector3df(0.0f,(irr::f32)(orientation = 90.0f),0.0f));
	mynodep->setScale(irr::core::vector3df((irr::f32)m.scale,(irr::f32)m.scale,(irr::f32)m.scale));
	
	}
	LASTUPDATE = 0;

	smgr= mgr;
}



/*
Agent::Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p)
:mynodep(a),position(p)
{	LASTUPDATE = 0;
	
mynodep->setPosition(p);
 mynodep->setMaterialFlag(video::EMF_LIGHTING, false);
	mynodep->setRotation(irr::core::vector3df(0.0f,orientation = 90.0f,0.0f));
	//position = mynodep->getPosition();
	
 mynodep->setMD2Animation(scene::EMAT_STAND); //set the animation to stand?
}
*/


Agent::~Agent(){

}




void Agent::createCollisionAnimator(irr::scene::ITriangleSelector* sel ,irr::scene::ISceneManager* mgr){

	selector = sel;
scene::ISceneNodeAnimator *nodeAnimator;
	nodeAnimator = mgr->createCollisionResponseAnimator(selector, mynodep, 
		core::vector3df((irr::f32)(30.0f*model.scale),(irr::f32)(25.0f*model.scale),(irr::f32)(30.0f*model.scale)),//collision volume radii
	core::vector3df((irr::f32)0.0f,(irr::f32)-10.0f,(irr::f32)0.0f),//gravity 
	model.mesh->getBoundingBox().getCenter()); //collision volume position
 
 mynodep->addAnimator(nodeAnimator);
 //mynodep->setScale(core::vector3df(1.75f,1.75f,1.75f));
 nodeAnimator->drop();

 smgr = mgr;


}
//Finds the hypoteneuse
double Agent::hypo(double opp, double adj)
{
	double mag ;
	mag = sqrt((opp*opp)+(adj*adj)) ; //pythagorean theorem
	return mag;
}

//This finds the relative distance between two agents
double Agent::agentProximity(Agent *nearAgent)
{
	//Calculate magnitude
	double x,z ;
	x = nearAgent->position.X - this->position.X ;
	z = nearAgent->position.Z - this->position.Z ;
	return hypo(x,z) ;	
}

//This finds the relative bearing between X axis and agent
double Agent::agentBearing(Agent *nearAgent)
{
	//Some variables
	double magAdj, magHypo;
	
	//Quadrant of nearAgent
	int quad;

	//nearAgent angle for return
	double nearAngle = -1;

	//math
	magHypo = hypo(nearAgent->position.X,nearAgent->position.Z);
	magAdj = abs(nearAgent->position.X);

	//Determine which quadrant the nearAgent is in
	if(nearAgent->position.X > 0)
	{
		//First quad check
		if(nearAgent->position.Z > 0)
			quad = 1;
		//Fourth quad check
		else if(nearAgent->position.Z < 0)
			quad = 4;
		//Angle zero
		else if(nearAgent->position.Z == 0)
			nearAngle = 0;
	}
	else if(nearAgent->position.X < 0)
	{
		//Second quad check
		if(nearAgent->position.Z > 0)
			quad = 2;
		//Third quad check
		else if(nearAgent->position.Z < 0)
			quad = 3;
		//Angle 180
		else if(nearAgent->position.Z == 0)
			nearAngle = 180;

	}
	else if(nearAgent->position.X == 0)
	{
		//Angle 90
		if(nearAgent->position.Z > 0)
			nearAngle = 90;
		//Angle 270
		else if(nearAgent->position.Z < 0)
			nearAngle = 270;
	}

	//If angle has been determined, don't calculate
	if(nearAngle < 0)
	{
		//calculate cos of the triangle
		nearAngle = acos(magAdj/magHypo);
	}

	//Compensates depending on the quadrant nearAgent is located in
	switch(quad){
		case 1:
			nearAngle += 0;
		case 2:
			nearAngle = 180 - nearAngle;
		case 3:
			nearAngle += 180;
		case 4:
			nearAngle = 360 - nearAngle;
		default:
			nearAngle += 0;
	}

	return nearAngle;

}


//This is Sensor 2, updates list of nearby agents
void Agent::proximitySensor(double sensorRange)
{	
	//variables
	double alpha, theta;

	//Traverse entire list
	for(int x=0 ; x< Agent::agentList->size() ; x++)
	{
		//Temp sensor data storage, this gets added to the list
		Sensor2Data temp;

		//Ignore entry in list that is self
		if((*agentList)[x]!= this)
		{
			//Get relative distance between agents and store in temp
			temp.relDistance = (*agentList)[x]->agentProximity(this);

			//If agents are within range, then add to the list
			if(temp.relDistance <= sensorRange)
			{
				//Set ID to pointer
				temp.agentID = (*agentList)[x];

				//Get relative bearing and store in temp
				alpha = Agent::agentBearing((*agentList)[x]);
				theta = this->orientation ;
				temp.relHeading = abs(alpha - theta);

				//Add temp to proxSenseList for return
				this->s2d.push_back(&temp);
			}
		}
	}
}


std::string Agent::sensor1ToString(){


	std::string s("Wall Feelers:\n");
	
 double  baseAngle = orientation - s1d->getAngle()/2.0;
 double  increment = s1d->getAngle() / s1d->getNumFeelers();


 for(int i = 0; i < s1d->getNumFeelers(); i++){

		double angle = i * increment + baseAngle;

		char str[100];
		sprintf(str,"%f", angle);
		s+= std::string(str);
		//s +="Angle:"+angle;
		s+="\tDistance-Squared:";
		sprintf(str,"%f",s1d->feelerDistances[i]);
		s+= std::string(str);
	  
	}
 return s;
}