#define NUMFEELERS 4
#include "Agent.h"

#ifndef INPUTHANDLER
#include "InputHandler.h"
#endif
#include <cmath>
#include <string>
#include <vector>

using namespace irr;
using namespace irr::core;
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
 
 double  baseAngle = -.5f*s1d->getAngle();
 
 baseAngle +=orientation;
 
 double  increment = s1d->getAngle() / (double)s1d->getNumFeelers();

		//	printf("ori%f\n", orientation);
		////	printf("inc%f\n", increment);
		//	printf("getA%f\n", s1d->getAngle());
		//	printf("ba%f\n", baseAngle);
		//	printf("%f\n", 0.0f-90.0f/2.0);


//printf("%d\n",s1d->getNumFeelers()); 
		 for(int i = 0; i < s1d->getNumFeelers(); i++){
				
			double angle = i * increment + baseAngle;
			
			//printf("%f\n", angle);
			
			core::vector3df feelerVector = core::vector3df((float)cos(degreesToRadians(angle)), 0.0f, -(float)sin(degreesToRadians(angle)));

			 float t1 = 0.0f;
			 
			 line.start = mynodep->getPosition();
			 line.end = line.start + feelerVector * s1d->maxRange;
			 //printf("s1dmr%d\n", s1d->maxRange();
 
			 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle)){
				 
	//			 if(feelerParticles.at(i)){
	//			 feelerParticles.at(i)->setPosition(intersection);


					 
				 float t1 = (intersection.X - mynodep->getPosition().X); 
				 t1 *= t1; 
				 float t2 = (intersection.Z - mynodep->getPosition().Z);
				 t2*=t2;
				 
				
				 
				 s1d->feelerDistances[i] = sqrt( t2+ t1);
				
				// printf("%f\n", s1d->feelerDistances[i]);

				 //if(ENABLE_DEBUG_OUTPUT){
				 //feelerParticles.at(i)->setVisible(true);
				// feelerParticles.at(i)->setText(stringw(
				//	 (int)s1d->feelerDistances[i]
				 
				 //).c_str());
				 //}else{
				//	 feelerParticles.at(i)->setVisible(false);
				 //}
				 
			 //}
				 
			 }
		    else{

				//if(feelerParticles.at(i))feelerParticles.at(i)->setVisible(false);
			 s1d->feelerDistances[i] =s1d->maxRange;
			 
			}
		 }}


void Agent::updateSensor2(){
	//Clear all previous entries
	s2d.clear();

	//Run sensor and store values in vector
	this->proximitySensor(1000.0);
}

void Agent::updatePieSensor(){
	//Clear all previous entries
	pie->clear();

	//Run sensor and store values in array
	Agent::PieDetect();
	Agent::showPieSensor();

}
void Agent::update(irr::ITimer* timer){

updateSensor1();
updateSensor2();
updatePieSensor();


if(orientation >360.0f || -orientation >=360.0f){
orientation = fmod((double)orientation, (double)360.0f);
}

if(orientation <0.0f){
	orientation = 360.0f +orientation; 
}
 
}


void Agent::processMessage(Message*){

}



Agent::Agent(Model m, irr::core::vector3df p, irr::scene::ISceneManager* mgr):position(p),model(m){
	

	s1d = new Sensor1Data(NUMFEELERS,45);
	pie = new PieSensor(2);


	//mgr->addBillboardTextSceneNode(0,L"HAI");
	//mgr->


	if(mgr){
	mynodep = mgr->addAnimatedMeshSceneNode(m.mesh);
	mynodep->setPosition(p);
	mynodep->setMaterialTexture(0,m.texture);
	mynodep->setMaterialFlag(video::EMF_LIGHTING, false);
	mynodep->setMD2Animation(scene::EMAT_STAND);
	mynodep->setRotation(irr::core::vector3df(0.0f,(irr::f32)(90.0f),0.0f));
	mynodep->setScale(irr::core::vector3df((irr::f32)m.scale,(irr::f32)m.scale,(irr::f32)m.scale));
	
	}

orientation = 360.0f - 90.0f;

	LASTUPDATE = 0;

	smgr= mgr;
	
	irr::scene::IBillboardTextSceneNode* a = 
 
    mgr->addBillboardTextSceneNode(0,stringw(
	((int)this)).c_str() );
		
	a->setPosition(vector3df(0.0f, 25.0f,0.0f));
	//a->setPosition(mynodep->getPosition());
	mynodep->addChild(a);
	
	a->setMaterialFlag(video::EMF_ZBUFFER,false);
	a->setSize(core::dimension2d<f32>(20.0f, 20.0f));

	
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
	magAdj = abs(nearAgent->position.X );

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

		//convert from radians to degrees
		//1 radian = 57.29578 degrees
		nearAngle *= 57.29578;
	}

	//Compensates depending on the quadrant nearAgent is located in
	switch(quad){
		case 1:
			nearAngle += 0;
			break;
		case 2:
			nearAngle = 180 - nearAngle;
			break;
		case 3:
			nearAngle += 180;
			break;
		case 4:
			nearAngle = 360 - nearAngle;
			break;
		default:
			nearAngle += 0;
			break;
	}

	return nearAngle;

}


//This is Sensor 2, updates list of nearby agents
void Agent::proximitySensor(double sensorRange)
{	
	//variables
	double alpha, theta, mod;
	int remainder;

	//get the agentList size
	int aListSize = Agent::agentList->size();

	//Temp sensor data storage, this gets added to the list
	Sensor2Data *temp ;
	temp = new Sensor2Data[aListSize];

	//Traverse entire list
	for(int x=0 ; x< aListSize ; x++)
	{
		//Ignore entry in list that is self
		if((*agentList)[x]!= this)
		{
			//Get relative distance between agents and store in temp
			temp[x].relDistance = (*agentList)[x]->agentProximity(this);

			//If agents are within range, then add to the list
			if(temp[x].relDistance <= sensorRange)
			{
				//Set ID to pointer
				temp[x].agentID = (int)(*agentList)[x];

				//Get relative bearing and store in temp
				alpha = Agent::agentBearing((*agentList)[x]);
				theta = this->orientation ;
				//Modify based on increasing orientation
				remainder = (int)(theta/360);
				remainder *= 360;
				mod = theta - abs(remainder);
				theta = mod;
				temp[x].relHeading = abs(alpha - theta);

				//Add temp to proxSenseList for return
				this->s2d.push_back(&temp[x]);
			}
		}
	}
}

void Agent::PieDetect(){
	//irr::core::vector3df self_normal = irr::core::vector3df(cos(degreesToRadians(orientation)), 0, sin(degreesToRadians(orientation))); 
	for(int i = 0; i < Agent::agentList->size(); i++){
		double distance = (*agentList)[i]->agentProximity(this);
		if(distance <= pie->range){
			//this is the magnitude of the agent vector AND the distance between myself and the agent 
			//double mag = sqrt( (abc[i]->getPosition().X * abc[i]->getPosition().X) + (abc[i]->getPosition().Y * abc[i]->getPosition().Y) + (abc[i]->getPosition().Z * abc[i]->getPosition().Z) );
			//irr::core::vector3df agent_normal = irr::core::vector3df( (abc[i]->getPosition().X / mag), (abc[i]->getPosition().Y / mag), (abc[i]->getPosition().Z / mag) ); 
			double self_angle = this->orientation;
			//Modify based on increasing orientation
			double remainder = (int)(self_angle/360);
			remainder *= 360;
			double mod = self_angle - abs(remainder);
			self_angle = mod;
			double agent_angle = Agent::agentBearing((*agentList)[i]);
			double ang_between_players = abs(agent_angle - self_angle);
			int place_in_bucket = ang_between_players / pie->angle;
			pie->areas[place_in_bucket]++;
		}
	}
}

void Agent::showPieSensor(){
	using std::cout;
	using std::endl;
	cout << "Going counterclockwise starting from the front.\n";
	cout << "[ ";
	for(int i = 0; i < (pie->num_slices * 2); i++)
		cout << pie->areas[i] << " ";
	cout << "]" << endl;
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