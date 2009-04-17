#define NUMFEELERS 6//3
#include "Agent.h"
#include <iostream>


#include "InputHandler.h"
#include "MessageHandler.h"

#include "cpMath.h"
#include <cmath>
#include <string>
#include <vector>
#include <limits>


#include "mapGraph.h"
//#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::video;

//std::vector<int>* astarSearch(unsigned int src, unsigned int tgt);
//extern irr::core::vector3df SEEK_POS;


std::vector<Agent*>* Agent::agentList;
std::vector<coverObject*>* Agent::coverObjectList;




//update method
void Agent::update(const irr::ITimer* timer){
	
//compute the time interval between now and the last frame for use in time based updating
irr::u32 ctime= 0;
TIMEELAPSED = (irr::f32)((ctime = timer->getTime()) - LASTUPDATE);
LASTUPDATE = ctime;




static double runningAverage = 0;
static int runs = 0;

runs+=1;
runningAverage += TIMEELAPSED;
if(runs%100 == 0){
	std::cout<< (runningAverage/ (double) runs)<<"\n" ;
	runningAverage = runs = 0;
}

//update sensors
updateWallSensor();
updateProximitySensor();
updatePieSensor();

//running update() on the state machine
AgentStateMachine->update(timer);

/*
irr::u32 ctime= 0;
irr::f32 TIMEELAPSED = (irr::f32)((ctime = timer->getTime()) - LASTUPDATE);
LASTUPDATE = ctime;
//this->expectedArrivalTime = 0;
//this->pathStartTime = 0;
//LASTUPDATE = timer->getTime();


static double runningAverage = 0;
static int runs = 0;

runs+=1;
runningAverage += TIMEELAPSED;
if(runs%100 == 0){
	std::cout<< (runningAverage/ (double) runs)<<"\n" ;
	runningAverage = runs = 0;
}

//update sensors
updateWallSensor();
updateProximitySensor();
updatePieSensor();
//irr::f32 MAXSPEED = .3f;

//running update() on the state machine
AgentStateMachine->update(timer);


//seek to the current seek target
vector3df tp = currentSeekTarget;
tp.Y = 0;
vector3df ap = mynodep->getPosition();
ap.Y = 0;
tp = tp-ap;
 
core::vector3df tv = (-mynodep->getPosition() + currentSeekTarget);
tv.Y = 0;
if( tv.getLength()<RADIUS){
	if(!pathList.empty()){
		previousSeekTarget = currentSeekTarget;//mynodep->getPosition();
		currentSeekTarget = pathList.front();
		pathList.erase(pathList.begin()); //ZOMG WTF obscure bug avoidance tip #666 : don't use list.remove(pathList.begin()) when you mean list.erase(pathList.begin())
	
		//std::cout<<"Arrival\n";
		int p = this->graph->getClosestNode(previousSeekTarget);
		int q = this->graph->getClosestNode(currentSeekTarget);
		//std::cout<<"Going from"<<p<<"to"<<q<<std::endl;
		//if(graph->adjacencyList[p][q]){
		//	std::cout<<"ok\n";
		//}else{
		//	std::cout<<"WTF BAD EDGE POPPED\n";
		//}

		this->pathStartTime = timer->getTime();
		//correctPath();		
		this->expectedArrivalTime = pathStartTime+(currentSeekTarget - this->getPosition()).getLength() /  MAXSPEED;



	}else{
		velocity = core::vector3df(0,0,0);
		currentSeekTarget = mynodep->getPosition();
		previousSeekTarget = mynodep->getPosition();
		this->pathStartTime = timer->getTime();
		this->expectedArrivalTime = pathStartTime+(currentSeekTarget - this->getPosition()).getLength() /  MAXSPEED;
	}
}

//check to see if the path needs to be corrected
if( (timer->getTime() - this->pathStartTime) > TIMEMULTIPLIER*(this->expectedArrivalTime - this->pathStartTime) ){
	this->pathStartTime = timer->getTime();
	correctPath();		
	this->expectedArrivalTime = pathStartTime+(pathList.front() - this->getPosition()).getLength() /  MAXSPEED;
}


irr::core::vector3df wallavoidaccel;
wallavoidaccel = vector3df(0,0,0);
for(int i = 0; i < s1d->getNumFeelers(); i++){
	//if(s1d->feelerDistances[i] < 50){
//	wallavoidaccel+=s1d->triangle[i].getNormal()*(1/(s1d->feelerDistances[i]*s1d->feelerDistances[i]));
	//if(velocity.getLength() - s1d->feelerDistances[i] > 0.0){
	double tmp = (s1d->maxRange - s1d->feelerDistances[i]);
	tmp/=5000000;//1
	//if(tmp>0.0f){
		wallavoidaccel+=s1d->triangle[i].getNormal()*tmp;
		//std::cout<<s1d->feelerDistances[i]<<"\n";

		
	//}
	//}
	//}
}

wallavoidaccel.Y = 0;
//wallavoidaccel = wallavoidaccel.normalize(); 

if(wallavoidaccel.getLength() > .025f){

wallavoidaccel = wallavoidaccel.normalize();
wallavoidaccel*=.025f;
}
//
//irr::core::vector3df pathseekaccel;
//pathseekaccel = vector3df(0,0,0);
//irr::core::vector3df pathvector = currentSeekTarget - previousSeekTarget;
//pathvector.Y = 0;
//if(pathvector.getLength()!=0.0f){/
//	irr::core::vector3df vectorprojection = (pathvector.dotProduct( this->velocity ) / pathvector.getLength()) * pathvector.normalize();
//pathseekaccel = (vectorprojection+-velocity)/mass;
//pathseekaccel = pathseekaccel.normalize()*.015;
//}

//if((pathseekaccel).getLength() >.01){
//std::cout<<"magnitude of seek:"<<seek(currentSeekTarget).getLength()<<"\n";
//std::cout<<"magnitude of pathforce:"<<(pathseekaccel).getLength()<<"\n";
//}else{pathseekaccel= vector3df(0,0,0);}

//

if(wallavoidaccel.getLength() >0.0f){
//std::cout<<"magnitude of seek:"<<seek(currentSeekTarget).getLength()<<"\n";
//std::cout<<"magnitude of pathforce:"<<(wallavoidaccel).getLength()<<"\n";
}
irr::core::vector3df accel = seek(currentSeekTarget) + wallavoidaccel;//.normalize()*MAXSPEED;// +  .0000001*wallavoidaccel;//- seek(currentSeekTarget).normalize()*wallavoidaccel.getLength();



if(!(velocity+(accel*TIMEELAPSED)).getLength() == 0.0f){
	velocity+=accel*TIMEELAPSED;
	
	if(velocity.getLength() > MAXSPEED){
	velocity = velocity.normalize()*MAXSPEED;
	}

	}else{
		//velocity = velocity.normalize()*.001; //core::vector3df(0,0,0);
		velocity = vector3df(0,0,0);

}

if(velocity.getLength() > .01f){
	mynodep->setPosition(mynodep->getPosition() + (TIMEELAPSED * velocity));
	
	if(!MOVING){
	MOVING= true;
	((irr::scene::IAnimatedMeshSceneNode*)mynodep)->setMD2Animation(scene::EMAT_RUN);
	}
}else if(MOVING){
MOVING = false;
((irr::scene::IAnimatedMeshSceneNode*)mynodep)->setMD2Animation(scene::EMAT_STAND);
}



vector3df abc = velocity;//SEEK_POS - mynodep->getPosition();
abc.Y = 0;
//abc.Z*=-1;
abc = abc.normalize();
double tAngle = radiansToDegrees(acos(fabs(abc.X)));

switch(
	   quadrant(velocity.normalize()
	   )){
case 1:break;
case 2:tAngle = 180-tAngle;break;
case 3:tAngle = 180+tAngle;break;
case 4:tAngle = 360-tAngle;break;
default:;
}


//printf("%f\n", tAngle);

if(velocity.getLength()!=0){
orientation = tAngle;
mynodep->setRotation(irr::core::vector3df(0.0f,(irr::f32)fabs(360-orientation),0.0f));
}

position = mynodep->getPosition();

 


*/



}


bool Agent::processMessage(const Message* m){
	return AgentStateMachine->processMessage(m);
}


//ctor
Agent::Agent(Model m, irr::core::vector3df p, irr::scene::ISceneManager* mgr, Agent_Type T,mapGraph* g):model(m),type(T),graph(g){
	IT = SPOTTED = NULL;
	this->LAST_OBSTACLE_CORRECTANCE = 0;
	s1d = new WallSensorData(NUMFEELERS,ANGLE);
	pie = new PieSensor(4);

	this->position = p;

	MOVING = false;

	velocity = vector3df(0.0f,0.0f,0.0f);

	//set up state machine
	AgentStateMachine = new StateMachine<Agent>(*this);

	//setting the current state for the agent, which'll be different if the agent is a predator that if the agent is prey
	if(type == PREDATOR){
		//wait 5 secs 
		AgentStateMachine->SetCurrentState(Patrol::GetInstance());
	}

	if(type == PREY){
		AgentStateMachine->SetCurrentState(Flee::GetInstance());
	}

	//if(mgr == NULL){
	//	std::cout<<"NO SCENE MANAGER WTF";}
	//else{
	//	std::cout<<"HAS SCENE MANAGER WHOO";
	//}

	if(mgr){
	mynodep = mgr->addAnimatedMeshSceneNode(m.mesh);

//	std::cout<<"\nADDED MESH SCENE NODE LOL\n";
	mynodep->setPosition(p);
	mynodep->setMaterialTexture(0,m.texture);
	mynodep->setMaterialFlag(video::EMF_LIGHTING, true);
	((irr::scene::IAnimatedMeshSceneNode*)mynodep)->setMD2Animation(scene::EMAT_ATTACK);
	mynodep->setRotation(irr::core::vector3df(0.0f,(irr::f32)(0.0f),0.0f));
	mynodep->setScale(irr::core::vector3df((irr::f32)m.scale,(irr::f32)m.scale,(irr::f32)m.scale));
	mynodep->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	//mynodep->addShadowVolumeSceneNode();

//extern IrrlichtDevice* device;
//if(device){Model SG =  createModel("../media/Marine_shotgun.md2", "../media/Gshotgun.pcx", device, 3.0f);
///	smgr->addAnimatedMeshSceneNode(SG.mesh);
//}

//	extern IrrlichtDevice* device;
//	Model CHUCKIERAIL = createModel("../media/w_railgun.md2","../media/w_railgun.pcx",device,1.0f);
//
//	mynodep->addChild( mgr->addAnimatedMeshSceneNode(CHUCKIERAIL.mesh));

	
	}

orientation = //360.0f - 
0.0f;

	LASTUPDATE = 0;

	smgr= mgr;
	
	
	irr::scene::IBillboardTextSceneNode* a = 
 
    mgr->addBillboardTextSceneNode(0,stringw(
	"I'm it!").c_str());
		
	a->setPosition(vector3df(0.0f, 25.0f,0.0f));
	//a->setPosition(mynodep->getPosition());
	mynodep->addChild(a);
	a->setMaterialFlag(video::EMF_ZBUFFER,true);
	a->setMaterialFlag(video::EMF_LIGHTING, false);
	a->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	a->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	a->setVisible(true);
	//mynodep->addChild(smgr->addLightSceneNode(0,vector3df(-10,25*model.scale,-10),video::SColor(255,255,255,255),1000));
	currentSeekTarget = mynodep->getPosition();
	previousSeekTarget = mynodep->getPosition();
}





Agent::~Agent(){
	//deleting the state machine
	delete AgentStateMachine;
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
	double diffX, diffZ;
	
	//Quadrant of nearAgent
	int quad = -1;

	//nearAgent angle for return
	double nearAngle = -1;

	//math
	diffX= nearAgent->position.X - this->position.X;
	diffZ= nearAgent->position.Z - this->position.Z;
	magHypo = hypo(diffX,diffZ);
	magAdj = abs(diffX);

	//Determine which quadrant the nearAgent is in
	if(diffX > 0)
	{
		//First quad check
		if(diffZ > 0)
			quad = 1;
		//Fourth quad check
		else if(diffZ < 0)
			quad = 4;
		//Angle zero
		else if(diffZ == 0)
			nearAngle = 0;
	}
	else if(diffX < 0)
	{
		//Second quad check
		if(diffZ > 0)
			quad = 2;
		//Third quad check
		else if(diffZ < 0)
			quad = 3;
		//Angle 180
		else if(diffZ == 0)
			nearAngle = 180;

	}
	else if(diffX == 0)
	{
		//Angle 90
		if(diffZ > 0)
			nearAngle = 90;
		//Angle 270
		else if(diffZ < 0)
			nearAngle = 270;
	}

	//If angle has been determined, don't calculate
	if(nearAngle < 0)
	{
		//calculate cos of the triangle
		nearAngle = acos(magAdj/magHypo);
		
		//convert from radians to degrees
		nearAngle = radiansToDegrees(nearAngle);
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
	double alpha, theta;

	//get the agentList size
	int aListSize = Agent::agentList->size();

	//Temp sensor data storage, this gets added to the list
	ProximitySensorData *temp ;
	temp = new ProximitySensorData[aListSize];

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
				alpha = this->agentBearing((*agentList)[x]);
				theta = this->orientation ;
				//Calculate angle between
				if( abs(alpha-theta) < (360-abs(alpha-theta)))
					temp[x].relHeading = alpha-theta;
				else{
					//if the alternate angle has a smaller magnitude 
					//we take it instead
					
					//assumed that this will return a positive value less than or equal to 
					//360
					temp[x].relHeading = 360 - abs(alpha - theta);
					
					//if the original angle was less than zero then the alternate is positive
					if(alpha-theta <0.0);
					//otherwise we know that the alternative angle is negative
					else{temp[x].relHeading*=-1;}

				}
				//Add temp to proxSenseList for return
				this->s2d.push_back(&temp[x]);
			}
		}
	}
}

void Agent::PieDetect(){
	//irr::core::vector3df self_normal = irr::core::vector3df(cos(degreesToRadians(orientation)), 0, sin(degreesToRadians(orientation))); 
	for(unsigned int i = 0; i < Agent::agentList->size(); i++){
		if( (*agentList)[i] == this) continue;
		double distance = Agent::agentProximity( (*agentList)[i] );
		if(distance <= pie->range){
			//this is the magnitude of the agent vector AND the distance between myself and the agent 
			//double mag = sqrt( (abc[i]->getPosition().X * abc[i]->getPosition().X) + (abc[i]->getPosition().Y * abc[i]->getPosition().Y) + (abc[i]->getPosition().Z * abc[i]->getPosition().Z) );
			//irr::core::vector3df agent_normal = irr::core::vector3df( (abc[i]->getPosition().X / mag), (abc[i]->getPosition().Y / mag), (abc[i]->getPosition().Z / mag) ); 
			double self_angle = this->orientation;

			//Modify based on increasing orientation
			double agent_angle = Agent::agentBearing((*agentList)[i]);
			double ang_between_players;
			if ( (agent_angle - self_angle) < 0){
				ang_between_players = 360.0 - fabs(agent_angle - self_angle);
			}
			else{
				ang_between_players = agent_angle - self_angle;
			}
			
			double final_angle;
			
			final_angle = ang_between_players + pie->offset; 
			if(final_angle > 360) final_angle-=360;

			int place_in_bucket = int( final_angle / fabs(pie->angle) );
			
			if (place_in_bucket > ( (pie->num_slices * 2) -1) ) exit(0);
			pie->areas[place_in_bucket]++;
		}
	}
}

void Agent::showPieSensor(){
	using std::cout;
	using std::endl;
	//cout << "Going counterclockwise starting from the front.\n";
	//cout << "[ ";
	//for(int i = 0; i < (pie->num_slices * 2); i++)
	//	cout << pie->areas[i] << " ";
	//cout << "]" << endl;
}

std::string Agent::WallSensorToString(){
	
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



void Agent::drawPieSlices(irr::video::IVideoDriver * driver){

	SMaterial m; 
		m.Lighting=false; 
		m.ZBuffer = 1;
		driver->setMaterial(m); 	
		//SColor col;


		 driver->setTransform(video::ETS_WORLD, mynodep->getAbsoluteTransformation());
//blue is velocity
driver->draw3DLine(vector3df(0,0,0), vector3df(500,0,0), SColor(255,0,0,255));
//red is line to targets

   //irr::core::matrix4 abc = irr::core::IdentityMatrix;
  // const float dat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, currentSeekTarget.X, currentSeekTarget.Y, currentSeekTarget.Z, 1};
   //abc.setM(dat);
 driver->setTransform(video::ETS_WORLD, graph->SCENE_NODE_VECTOR[ graph->getClosestNode(previousSeekTarget)]->getAbsoluteTransformation() );
 driver->draw3DLine( vector3df(0,0,0), this->currentSeekTarget-this->previousSeekTarget, SColor(255, 0, 255,0));
   
   
  

//green line is path
//driver->draw3DLine(this->previousSeekTarget - mynodep->getPosition(), this->currentSeekTarget - mynodep->getPosition(), SColor(255, 0, 255,0));


/*

irr::f32 angle = (irr::f32)pie->offset;
	for(int i = 0; i < pie->num_slices*2;i++){
		
	driver->draw3DLine(
			vector3df(0,0,0), 
			vector3df(
			(irr::f32)(250*cos( degreesToRadians(angle) )),
						0,
						(irr::f32)(250*sin( degreesToRadians(angle) ))), 
						SColor(255,255,255,255));
	angle +=(irr::f32)pie->angle;
   
	  // core::matrix4()); 
  //driver->draw3DLine(vector3df(0,0,0), vector3df(0,0,250));
		//driver->draw3DLine(mynodep->getPosition(), mynodep->getPosition()+5000*vector3df(cos(0.0f), mynodep->getAbsolutePosition().Y, sin(0.0f)),video::SColor(255,255,255,255));
	}*/

}






void Agent::createPatrolRoute(mapGraph* mg){

pathList.clear();

mapGraph* minspanningtree = mg->minimumSpanningTree(0);
//std::cout<<"got the tree\n";
std::vector<int>* result = minspanningtree->depthFirstSearch(mg->getClosestNodeUnobstructedSpannable(mynodep->getPosition(),smgr, selector));
//delete minspanningtree;
//minspanningtree= 0;


if(result->size()){
	//pathList.resize(mg->NODE_VECTOR.size());
	for(unsigned int i = 0; i < result->size(); i++){
	
		pathList.push_back( mg->nodePosition((*result)[i]));
					
	}
	//pathList.push_back(fin);


	currentSeekTarget = pathList.front();
	previousSeekTarget = mynodep->getPosition();

	}else{
	
		this->pathList.push_back(mynodep->getPosition());
		this->velocity = vector3df(0,0,0);
	}
//	printf("%d %d\n", sNode1, sNode2);


for(int i = 0; i < result->size(); i++){

	std::cout<<(*result)[i]<<" ";
}


/*
std::list<irr::core::vector3df>::const_iterator iter = pathList.begin();
for(int i = 0; i < pathList.size()-1; i++){

		
 core::line3d<f32> line;
 core::vector3df intersection;
 core::triangle3df triangle;
 line.start = *iter;
 iter++;
 line.end = *iter;

 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle)){
	 std::cout<<"WTF SOMEHOW THE PATH IS WRONG\n";///exit(0);
	 std::cout<<"From node:"<< mg->getClosestNode(line.start)<<"To Node:"<<mg->getClosestNode(line.end) << std::endl;			

	}

}
std::cout<<std::endl;
*/

delete result;


}


//this function generates a list of waypoints to seek to a target location
void Agent::newTargetLocation(irr::core::vector3df fin){

	mapGraph* mg = this->graph;
	//extern std::vector<irr::core::vector3df> NODE_VECTOR;

	pathList.clear();


	//get the unobstructed node closest to the target location
 int sNode2 = mg->getClosestNodeUnobstructed(fin,smgr, selector);
	//get the unobstructed node closest to the agent
 int sNode1 = mg->getClosestNodeUnobstructed(mynodep->getPosition(), smgr,selector);

 std::vector<int>* result = mg->astarSearch(sNode1, sNode2);

	if(result->size()){
	for(unsigned int i = 0; i < result->size(); i++){
		pathList.push_front( mg->nodePosition( (*result)[i]));
	}
	pathList.push_back(fin);

	}else{
		velocity = vector3df(0,0,0);
		pathList.push_back(mynodep->getPosition());
	}


	
	currentSeekTarget = pathList.front();
	previousSeekTarget = mynodep->getPosition();
	printf("%d %d\n", sNode1, sNode2);

////
	//agent2.createPatrolRoute(&graph);
//mg->selector = selector;


//line.start = NODE_VECTOR[

//if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle)){
//	 std::cout<<"WTF SOMEHOW THE PATH IS WRONG\n";///exit(0);
//	}


	delete result;
}




//}


//if the agent needs to correct its path: in the event it gets lost, eg, falls off a bridge, misses a doorway, etc, a-star to the currentSeekTarget and prepend the path to the pathlist
void Agent::correctPath(){


	std::cout<<"correcting path\n";
int src = this->graph->getClosestNodeUnobstructed(this->getPosition(),smgr,selector);
int tgt = this->graph->getClosestNodeUnobstructed(currentSeekTarget,smgr,selector);


//when the agent is getting stuck on the torch, they're closest to the node behind the torch, so source is equal to target and no path correction is getting done
//this makes the agent backtrack and try again, but it will prevent them from getting stuck permanently
if(src == tgt){
	//std::cout<<"Source equal to target in path correction, doing path correction correction\n";
    src = this->graph->getClosestNodeUnobstructed(this->previousSeekTarget,smgr,selector);
}



	std::vector<int>* result = this->graph->astarSearch( src, tgt);
	pathList.push_front(this->currentSeekTarget);
	if(result->size()){
	for(unsigned int i = 0; i < result->size(); i++){
		pathList.push_front( this->graph->nodePosition( (*result)[i]));
	}
	}

	currentSeekTarget = pathList.front();
	previousSeekTarget = mynodep->getPosition();
	

//	std::cout<<"PATH CORRECTION IN PLACE\n";
	delete result;

}


