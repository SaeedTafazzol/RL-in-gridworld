/*
 * Agent.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: potato
 */

#include "Agent.h"
#include "World.h"
#include "elements.cpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>     /* srand, rand */
#include <math.h>

using namespace std;
Agent::Agent(World * myWorld) {
	wm = myWorld;

	discound = 0.95;
	learningRate = 0.1;
	explorationRate = 0.5;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++){
			std::vector<char> vec;
			wm->getLegalActions(wm->getState(i,j),vec);
			for(int k=0;k<vec.size();k++)
				Qvalues[std::pair<int,char>(j*10+i,vec[k])] = 0;

		}
	// TODO Auto-generated constructor stub

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}


double Agent::getQvalue(state thestate,char action){
	return Qvalues[std::pair<int,char>(thestate.position.x+thestate.position.y*10,action)];
}

void Agent::setQvalue(state thestate,char action,double value){
	Qvalues[std::pair<int,char>(thestate.position.x+thestate.position.y*10,action)] = value;
}

double Agent::getValue(state theState){
	if(theState.getType()==goal)
		return +1;
	if(theState.getType()==obstacle){
		return -1;
	}
	std::vector<char> vec;
	wm->getLegalActions(theState,vec);
	double max = -9999;
	for(int i=0;i<vec.size();i++)
		max = std::max(max,getQvalue(theState,vec[i]));
	return max;
}

char Agent::getPolicy(state theState){
	if(theState.getType()==goal)
		return 'G';
	if(theState.getType()==obstacle)
		return 'O';
	std::vector<char> vec;
	wm->getLegalActions(theState,vec);
	double max = -9999;
	char result = 'N';
	for(int i=0;i<vec.size();i++)
		if(max<std::max(max,getQvalue(theState,vec[i]))){
			max = std::max(max,getQvalue(theState,vec[i]));
			result = vec[i];
		}
	return result;
}
void Agent::turnOffLearning(){
	learningRate = 0;
	explorationRate =0;
}
////MDP **************************
//double Agent::calExpectedSum(state theState,char action){
//	double sum = 0;
//	std::vector<std::pair<state,float> > vec;
//	vec = wm->getProb(theState,action);
//	for(int i=0;i<vec.size();i++){
//		if(getValue(vec[i].first)!=0)
//		sum += vec[i].second*(wm->getReward(theState,action,vec[i].first) + discound*getValue(vec[i].first));
//	}
//	return sum;
//}
//
//void Agent::iteration(int n){
//	for(int i = 0;i<n;i++)
//		for(int j=0;j<10;j++)
//			for(int k=0;k<10;k++){
//
//				if(wm->getState(j,k).getType()==goal || wm->getState(j,k).getType()==obstacle)
//					continue;
//
//				state theState = wm->getState(j,k);
//
//				std::vector<char> vec;
//				wm->getLegalActions(theState,vec);
//				for(int l=0;l<vec.size();l++){
//					setQvalue(theState,vec[l],calExpectedSum(theState,vec[l]));
//				}
//			}
//}
////MDP **************************


void Agent::printValues(){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			std::cout<<getValue(wm->getState(j,i))<<",";
		}
		std::cout<<std::endl;
	}
}
void Agent::printPolicy(){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			std::cout<<getPolicy(wm->getState(j,i))<<",";
		}
		std::cout<<std::endl;
	}
}

char Agent::getRandomAction(state theState){

	std::vector<char> legalActions;
	wm->getLegalActions(theState,legalActions);
	float chance =rand() / (RAND_MAX + 1.0);
	double sum = 0;
	std::vector<double> legalActionprobs;
	for(int i = 0;i<legalActions.size();i++){
		sum += exp(getQvalue(theState,legalActions[i]));
		legalActionprobs.push_back(exp(getQvalue(theState,legalActions[i])));
	}
	for(int i = 0;i<legalActionprobs.size();i++)
		legalActionprobs[i] /= sum;



	//////////
	float base = 0;
	for(int i = 0;i<legalActionprobs.size();i++)
		if(chance - base<legalActionprobs[i])
			return legalActions[i];
		else
			base+= legalActionprobs[i];



}

void Agent::move(){

	int chance = rand()%100+1;
	std::pair<state,double> update;
	state prevState = wm->getState(wm->getAgentPos().x,wm->getAgentPos().y);

	char action;
	if(chance >= explorationRate*100)
		action = getPolicy(wm->getState(wm->getAgentPos().x,wm->getAgentPos().y));
	else
		action = getRandomAction(wm->getState(wm->getAgentPos().x,wm->getAgentPos().y));

	update = wm->agentMoved(action);
	setQvalue(prevState,action,(1-learningRate)*getQvalue(prevState,action) + learningRate*(update.second + discound*(getValue(update.first))));
}



