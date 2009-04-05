#include "mapGraph.h"
#include <string>
#include <vector>


using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;
using namespace std;

//gets the node from the graph closest to the position passed in
int mapGraph::getClosestNode(irr::core::vector3df pos){

int rn=-1;
double closest = std::numeric_limits<double>::max();
	for(unsigned int i = 0; i < NODE_VECTOR.size();i++){
		if((pos - NODE_VECTOR[i]).getLength() < closest){
				rn = i;	
				closest = (pos - NODE_VECTOR[i]).getLength();			
			}
		}
return rn;
}



//performs an a* search from src to tgt, returning the path as a vector of integers representing node numbers
std::vector<int>* mapGraph::astarSearch(unsigned int src, unsigned int tgt){
using namespace std;
	std::vector<int>* solution = new std::vector<int>;
	if(src > NODE_VECTOR.size() || tgt > NODE_VECTOR.size())return solution;

	//solution->push_back(src);
	
	if(src!=tgt){

	bool *visitedArray = new bool[NODE_VECTOR.size()];
	int *parentArray   = new int[NODE_VECTOR.size()];
	double *costArray  = new double[NODE_VECTOR.size()];//cost from each 
	std::vector<int> shortestPathList;


	for(unsigned int i = 0; i < NODE_VECTOR.size(); i++){
	  visitedArray[i] = false; //not on the shortest path tree
	  parentArray[i] = -1; //no parent from the source to node i
	  costArray[i] = std::numeric_limits<double>::max(); //the cost to every node from the source is infinite
	}
	
	parentArray[src] = src; //the source node's parent is itself on the path
	//visitedArray[src] = true; //add the source to the shortest path tree
	costArray[src]=0.0f; //because the cost to the node from itself is 0.0
	

	//while the target hasn't been added to the shortest path tree
	while(!visitedArray[tgt]){

		//go through the edges 
		
		double shortest = std::numeric_limits<double>::max();
		int tNode = -1;
		//int tParent = 0;
		
		for(unsigned int i = 0; i < NODE_VECTOR.size();i++){
			if(!visitedArray[i] && (costArray[i] +  (NODE_VECTOR[tgt] - NODE_VECTOR[i]).getLength())<shortest){
				shortest = costArray[i];
				tNode = i;
			}
		}

		if(tNode == -1){solution->clear(); 
		return solution;}
		visitedArray[tNode] = true;
		shortestPathList.push_back(tNode);

		//look at the new explored node's edges going to any unexplored node and see if we can get a new shortest path 
		for(unsigned int i = 0; i < NODE_VECTOR.size(); i++){
				
			if(adjacencyList[tNode][i] && visitedArray[i] == false){
			
				if(costArray[i] > (costArray[tNode] + costList[tNode][i])){
					costArray[i] = (costArray[tNode] + costList[tNode][i]);
					parentArray[i] = tNode;
				}
				

			}
		}

	}//end while


	solution->push_back(tgt);
	int q = tgt;
	while(q != parentArray[q]){
		solution->push_back(parentArray[q]);
		q = parentArray[q];
	}

	
	delete[] costArray;
	delete[] visitedArray;
	delete[] parentArray;
	
	}//endif

	for(unsigned int i = 0; i < solution->size(); i++){
		cout<<(*solution)[i]<<' ';
	}cout<<'\n';
	
	
	return solution;
}





mapGraph::~mapGraph(){

	
#ifdef NODE_MESH_GENERATOR

//output node mesh files
 core::line3d<f32> line;
 core::vector3df intersection;
 core::triangle3df triangle;

	 FILE *fp = fopen(nodes.c_str(), "w");
	 for(int i = 0; i < NODE_VECTOR.size(); i++){
		 fprintf(fp, "%f %f %f\n", NODE_VECTOR[i].X, NODE_VECTOR[i].Y, NODE_VECTOR[i].Z);
	 }
	fclose(fp);
	fp = fopen(edges.c_str(), "w");
	for(int i = 0; i < NODE_VECTOR.size(); i++){
		for(int j = 0; j < NODE_VECTOR.size(); j++){
			

			line.start = NODE_VECTOR[i];
			line.end = NODE_VECTOR[j];

			if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle)){	
			;
			}else{
			fprintf(fp, "%d %d\n", i, j);
			}
		
		}
	}
	fclose(fp);
#endif


	delete[] adjacencyList;
	delete[] costList;

	for(unsigned int i = 0; i < SCENE_NODE_VECTOR.size(); i++){
		SCENE_NODE_VECTOR[i]->drop();
	}

}






mapGraph::mapGraph(IrrlichtDevice *device,const char *n, const char *e, const char *ex):nodes (n), edges (e), exclude (ex){
	
	 smgr = device->getSceneManager();

ENABLE_DEBUG_OUTPUT = false;

	//load in the adjacency list
FILE *fp = fopen(nodes.c_str(), "r");
if(!fp){
	throw new std::string("COULD NOT OPEN MAP GRAPH FILE");

}
float a[3];
while(!feof(fp)){
	fscanf(fp, "%f %f %f\n", a, &a[1], &a[2]);
	
	NODE_VECTOR.push_back(irr::core::vector3df(a[0],a[1],a[2]));

	scene::ISceneNode * node = smgr->addSphereSceneNode();
	node->setPosition(vector3df(a[0],a[1],a[2]));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	SCENE_NODE_VECTOR.push_back(node);
	node->setVisible(ENABLE_DEBUG_OUTPUT);

	irr::scene::IBillboardTextSceneNode* a = 
    smgr->addBillboardTextSceneNode(0,stringw(
	(NODE_VECTOR.size()-1)).c_str());
		
	a->setPosition(irr::core::vector3df(0.0f, 15.0f,0.0f));
	//a->setPosition(mynodep->getPosition());
	node->addChild(a);
	a->setMaterialFlag(irr::video::EMF_ZBUFFER,true);
	a->setSize(irr::core::dimension2d<f32>(10.0f, 10.0f));

	
}
 
fclose(fp);

int k = NODE_VECTOR.size();

//creates adjacency list
adjacencyList = newDoubleArray<bool>(k,k);
zero2dArray<bool>(adjacencyList, k, k);

fp = fopen(edges.c_str(), "r");
while(!feof(fp)){
	int a, b;
	fscanf(fp,"%d %d\n",&a,&b);
	adjacencyList[a][b] = true;
}

fclose(fp);

//manually remove certain edges
fp = fopen(exclude.c_str(), "r");
while(!feof(fp)){
	int a, b;
	fscanf(fp,"%d %d\n",&a,&b);
	adjacencyList[a][b] = false;
}

fclose(fp);

//creates the array of costs for each edge
costList = newDoubleArray<double>(k,k);

for(int i = 0; i <k; i++){
	for(int j = 0; j < k; j++){
		costList[i][j] = (NODE_VECTOR[i]- NODE_VECTOR[j]).getLength();
	}
}





}




void mapGraph::render(video::IVideoDriver* driver){

if(ENABLE_DEBUG_OUTPUT){
	
	
	//then draw lines to show the node mesh graph		
		
		SMaterial m; 
		m.Lighting=false; 
		m.ZBuffer = 1;
		driver->setMaterial(m); 	
		SColor col;
		for(unsigned int i = 0; i < NODE_VECTOR.size(); i++){
		
			
			for(unsigned int j = 0; j < NODE_VECTOR.size(); j++){
		
				if(adjacencyList[i][j]){
				driver->setTransform(video::ETS_WORLD,SCENE_NODE_VECTOR[i]->getAbsoluteTransformation());
				if(adjacencyList[j][i] && adjacencyList[i][j]){
						col =  SColor(0,255,0,0);
						
					}else
					{
						col = SColor(255,0,0,255);
						
					}
				
				driver->draw3DLine(vector3df(0,0,0), NODE_VECTOR[j]-NODE_VECTOR[i], col);
				}
			
		}}	

		}//don't draw lines if not in debug output mode;


}



void mapGraph::toggleDebugOutput(bool b){
ENABLE_DEBUG_OUTPUT = b;

for(unsigned int i = 0; i < SCENE_NODE_VECTOR.size();i++){
	
	SCENE_NODE_VECTOR[i]->setVisible(b);


}

}



void mapGraph::addNode(irr::core::vector3df pos){

	//add a node to the list
	NODE_VECTOR.push_back(pos);
	scene::ISceneNode * node = smgr->addSphereSceneNode();
	node->setPosition(pos);
	node->setMaterialFlag(video::EMF_LIGHTING, false);

}