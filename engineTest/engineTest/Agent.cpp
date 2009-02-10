#include "Agent.h"
#include "InputHandler.h"
#include <cmath>

using namespace irr;
//double degreesToRadians(double degrees){
//return 2*3.14159*degrees/360;/
//}


void Agent::update(irr::ITimer* timer){
 ;
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
	mynodep->setRotation(irr::core::vector3df(0.0f,orientation = 90.0f,0.0f));
	mynodep->setScale(irr::core::vector3df(m.scale,m.scale,m.scale));
	
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




void Agent::createCollisionAnimator(irr::scene::ITriangleSelector* selector ,irr::scene::ISceneManager* mgr){

scene::ISceneNodeAnimator *nodeAnimator;
	nodeAnimator = mgr->createCollisionResponseAnimator(selector, mynodep, 
		core::vector3df(30*model.scale,25*model.scale,30*model.scale),//collision volume radii
	core::vector3df(0,-10,0),//gravity 
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
std::vector<Sensor2Data*> *Agent::proximitySensor(std::vector<Agent*> globalAgentList, double sensorRange)
{
	//Create list for return
	std::vector<Sensor2Data*> proxSenseList ;

	//Traverse entire list
	for(int x=0 ; x< globalAgentList.size() ; x++)
	{
		//Temp sensor data storage, this gets added to the list
		Sensor2Data temp;

		//Get relative distance between agents and store in temp
		temp.relDistance = globalAgentList[x]->agentProximity(this);

		//If agents are within range, then add to the list
		if(temp.relDistance <= sensorRange)
		{
			//Set ID to pointer
			temp.agentID = (int)globalAgentList[x];

			//Get relative bearing and store in temp
			temp.relHeading = globalAgentList[x]->agentBearing(this);

			//Add temp to proxSenseList for return
			proxSenseList.push_back(&temp);
		}
	}

	//return pointer to the proximity sensor list
	return &proxSenseList;
}
