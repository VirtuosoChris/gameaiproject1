#include "Agent.h"
#include "cpMath.h"


void Agent::updateWallSensor(){



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
			
			core::vector3df feelerVector = core::vector3df((float)cos(degreesToRadians(angle)), 0.0f, (float)sin(degreesToRadians(angle)));

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

				 s1d->triangle[i] = triangle;
				
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


void Agent::updateProximitySensor(){
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



/*#include "Agent.h"
#include "cpMath.h"


void Agent::updateWallSensor(){



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

// double* coverDistances = new double[this->coverObjectList->size()];
 //double* coverFeelerDistances = new double[this->coverObjectList->size()];


 //precompute the distance to each cover object
 //for(int k = 0; k < coverObjectList->size(); k++){
 
	 //coverDistances[k] = (this->mynodep->getPosition() - ((*coverObjectList)[k])->getSceneNode()->getPosition()).getLength();

////	 if(coverDistances[k] > s1d->maxRange){
	//	 coverDistances[k] = std::numeric_limits<double>::max();
	//	 }

		 //optimization: rule out ones not facing. later, to avoid bugs
	// coverFeelerDistances[k] = std::numeric_limits<double>::max();
 //}

 //for(int p = 0; p < (*this->coverObjectList).size(); p++){
//				 if(smgr->getSceneCollisionManager()->getSceneNodeFromRayBB(line) == (*this->coverObjectList)[p]->getSceneNode()){
//					 std::cout<<"ZOMG DETECTED\n";
//				 }
//			 }

//printf("%d\n",s1d->getNumFeelers()); 
		 for(int i = 0; i < s1d->getNumFeelers(); i++){
				

		
//irr::scene::ISceneNode* tnode; 
//tnode= smgr->getSceneCollisionManager()->getSceneNodeFromRayBB(line);

			double angle = i * increment + baseAngle;
			
			//printf("%f\n", angle);
			
			core::vector3df feelerVector = core::vector3df((float)cos(degreesToRadians(angle)), 0.0f, (float)sin(degreesToRadians(angle)));

			// float t1 = 0.0f;
			 
			 line.start = mynodep->getPosition();
			 line.end = line.start + feelerVector * s1d->maxRange;

			 



					
					//printf("s1dmr%d\n", s1d->maxRange();
 
			 if(!smgr ||!selector ||!smgr->getSceneCollisionManager())return;
			 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle)){
				 
	//			 if(feelerParticles.at(i)){
	//			 feelerParticles.at(i)->setPosition(intersection);


					 
				 float t1 = (intersection.X - mynodep->getPosition().X); 
				 t1 *= t1; 
				 float t2 = (intersection.Z - mynodep->getPosition().Z);
				 t2*=t2;
				 
				
				 
				 s1d->feelerDistances[i] = sqrt( t2+ t1);

				 s1d->triangle[i] = triangle;
				
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




			/*
 for(int p = 0; p < (*this->coverObjectList).size(); p++){

	 if( tnode == (*this->coverObjectList)[p]->getSceneNode()){
				 std::cout<<"ZOMG DETECTED\n";

					irr::core::vector3df ipoint;
					ipoint = (*this->coverObjectList)[p]->getSceneNode()->getPosition();
					ipoint = this->getSceneNode()->getPosition() - ipoint;
					ipoint = ipoint.normalize();
					ipoint*= (*this->coverObjectList)[p]->getRadius() + 20;
					double tDistance = (ipoint - this->getSceneNode()->getPosition()).getLength();
							
					if(tDistance < s1d->feelerDistances[i]){
						s1d->feelerDistances[i] = tDistance;
					}

				 }
			 }
*/

/*
			//***go though each cover object, and record the intersection point along this feeler line
			for(int xyzzy = 0; xyzzy < s1d->getNumFeelers(); xyzzy++){
			
				if((*this->coverObjectList)[xyzzy]->getSceneNode()->getBoundingBox().intersectsWithLine(line)){
				
					std::cout<<"line intersects cover\n";
					irr::core::vector3df ipoint;
					ipoint = (*this->coverObjectList)[xyzzy]->getSceneNode()->getPosition();
					ipoint = this->getSceneNode()->getPosition() - ipoint;
					ipoint = ipoint.normalize();
					ipoint*= (*this->coverObjectList)[xyzzy]->getRadius();
					coverFeelerDistances[xyzzy] = (ipoint - this->getSceneNode()->getPosition()).getLength();
				}
			
			}


			//*****now go through the values gathered from the level selector and all the physics objects, and pick the closest distance along this feeler
			for(int x = 0; x < s1d->getNumFeelers(); x++){
				

				if(coverFeelerDistances[x] < s1d->feelerDistances[i]){
				s1d->feelerDistances[i] = coverFeelerDistances[x];

				std::cout<<"Cover replaces wall\n";
				}
				
			}//****end for
*/

////		 }

	//	 delete []coverDistances;
	//	 delete []coverFeelerDistances;

/*
}


void Agent::updateProximitySensor(){
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

}*/