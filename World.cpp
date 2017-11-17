/*
 * World.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: potato
 */

#include "World.h"
#include "elements.cpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>     /* srand, rand */

using namespace std;
World::World() {
	// TODO Auto-generated constructor stub
	for(int i = 0;i<10;i++)
		for(int j=0;j<10;j++)
			if(i==9&&j==9)
				states[i][j] = state(goal,Vector2D(i,j));
			else if((j==5&&i==8) ||(i==5&&j==7))
				states[i][j] = state(obstacle,Vector2D(i,j));
			else
				states[i][j] = state(normal,Vector2D(i,j));



	agentPos = Vector2D(0,0);

}

World::~World() {
	// TODO Auto-generated destructor stub
}
void World::getLegalActions(state current,std::vector<char> & chars){
	chars.clear();
	chars.push_back('N');
	chars.push_back('E');
	chars.push_back('S');
	chars.push_back('W');
}
Vector2D World::getAgentPos(){
	return agentPos;
}

state World::getState(int x,int y){
	return states[x][y];
}

double World::getReward(state current,char action,state next){
	return -0.01;
}

std::vector<std::pair<state,float> > World::getProb(state current,char action){
	state nState;
	state wState;
	state sState;
	state eState;
	std::vector<std::pair<state,float> > fillVec;

	state states[4];
	int counter=0;
	int chosen=0;

	if(current.position.x > 0){
		states[1]= getState(current.position.x-1,current.position.y);
	}
	//eState = getState(current.position.x-1,current.position.y);

	if(current.position.x<9){
		states[3]=getState(current.position.x+1,current.position.y);
	}
	//wState = getState(current.position.x+1,current.position.y);
	if(current.position.y>0){

		states[0] = getState(current.position.x,current.position.y-1);
		//nState = getState(current.position.x,current.position.y-1);
	}
	if(current.position.y<9){

		states[2] = getState(current.position.x,current.position.y+1);
		//sState = getState(current.position.x,current.position.y+1);
	}



	switch(action){
	case 'N':
		chosen = 0;
		break;
	case 'W':
		chosen = 1;
		break;
	case 'S':
		chosen = 2;
		break;
	case 'E':
		chosen = 3;
		break;
	}
	for(int i = 0;i<4;i++)
		if(chosen!=i)
			if(!states[i].isInvalid())
				counter++;

	for(int i = 0;i<4;i++)
		if(chosen!=i){
			if(!states[i].isInvalid())
				fillVec.push_back(std::pair<state,float>(states[i],0.25/counter));
		}else
			if(!states[i].isInvalid())
				fillVec.push_back(std::pair<state,float>(states[i],0.75));
			else
				fillVec.push_back(std::pair<state,float>(current,0.75));

	return fillVec;
}




std::pair<state,double> World::agentMoved(char action){
	int chance = rand()%100 + 1;
	std::vector<std::pair<state,float> > vec;
	vec = getProb(getState(agentPos.x,agentPos.y),action);
	Vector2D prevPos = agentPos;
	float a[vec.size()];

	for(int i = 0 ; i<vec.size();i++){
		float base = 0;
		for(int j=i-1;j>=0;j--){
			base += vec[j].second;
		}
		if(chance-(100*base)<int(100*vec[i].second)){
			agentPos = vec[i].first.getPos();
			return std::pair<state,double>(getState(agentPos.x,agentPos.y),getReward(getState(prevPos.x,prevPos.y),action,getState(agentPos.x,agentPos.y)));
			break;
		}
	}
}

void World::reset(bool useRandom){
	if(useRandom)
		agentPos = Vector2D(rand()%10,rand()%10);
	else
		agentPos = Vector2D(0,0);
}




