#include "Agent.h"
#include "InputHandler.h"
#include <cmath>

using namespace irr;
//double degreesToRadians(double degrees){
//return 2*3.14159*degrees/360;/
//}


void Agent::updateSensor1(){


 core::line3d<f32> line;
 core::vector3df intersection;
 core::triangle3df triangle;

 core::vector3df orientVector;

 line.start = mynodep->getPosition();
 line.end = line.start + orientVector * s1d->maxRange;
 
	//	billboard->setVisible(true);
		 

 
 double  baseAngle = orientation - s1d->getAngle()/2.0;
 double  increment = s1d->getAngle() / s1d->getNumFeelers();

		 for(int i = 0; i < s1d->getNumFeelers(); i++){
				

			double angle = i * increment + baseAngle;
			 core::vector3df feelerVector = core::vector3df(cos(angle), 0, sin(angle));

			 float t1 = 0.0f;
			 
			 line.start = mynodep->getPosition();
			 line.end = line.start + orientVector * s1d->maxRange;
 

			 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle))
				 s1d->feelerDistances[i] = (t1= (intersection.X - mynodep->getPosition().X)) * t1 + (t1 = (intersection.Z - mynodep->getPosition().Z)* t1);
			 //billboard->setPosition(intersection);
		    else{
			 s1d->feelerDistances[i] =s1d->maxRange;
			}
		 }

	


}

void Agent::update(irr::ITimer* timer){

updateSensor1();
 
}


void Agent::processMessage(Message*){

}



Agent::Agent(Model m, irr::core::vector3df p, irr::scene::ISceneManager* mgr):position(p),model(m){
	

	s1d = new Sensor1Data(3,90);

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

//This finds the relative distance between two agents
double Agent::agentProximity(Agent *nearAgent)
{
	//Calculate magnitude
	double x,z,mag ;
	x = nearAgent->position.X - this->position.X ;
	z = nearAgent->position.Z - this->position.Z ;
	mag = sqrt((x*x)+(z*z)) ; //pythagorean theorem

	return mag ;	
}

//This finds the relative bearing between two agents
double Agent::agentBearing(Agent *nearAgent)
{
	//Calculate bearing between nearAgent and origin
	double opp, adj, nearBear, thisBear;
	opp = nearAgent->position.X - this->position.X ;
	adj = nearAgent->position.Z - this->position.Z ;
	nearBear = atan(opp/adj);
	thisBear = this->orientation;

	//Subtract nearBearing from currentBearing and return
	return (nearBear - thisBear);
}


//This is Sensor 2, returns a list of Sensor2Data 
std::vector<Sensor2Data*> *Agent::proximitySensor(double sensorRange)
{
	//Create list for return
	std::vector<Sensor2Data*> proxSenseList ;

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
				temp.relHeading = (*agentList)[x]->agentBearing(this);

				//Add temp to proxSenseList for return
				proxSenseList.push_back(&temp);
			}
		}
	}

	//return pointer to the proximity sensor list
	return &proxSenseList;
}