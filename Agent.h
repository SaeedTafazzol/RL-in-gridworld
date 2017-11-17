/*
 * Agent.h
 *
 *  Created on: Oct 12, 2017
 *      Author: potato
 */

#ifndef AGENT_H_
#define AGENT_H_

#include "elements.cpp"
#include "World.h"
#include <map>

class Agent {
public:
	Agent(World * myWorld);
	virtual ~Agent();
	double getQvalue(state theState,char action);
	double getValue(state theState);
	char getPolicy(state theState);
	void move();
	void turnOffLearning();

	////MDP **************************
//	double calExpectedSum(state theState,char action);
//	void iteration(int n);
	////MDP **************************

	void printValues();
	void printPolicy();


private:
	void setQvalue(state theState,char action,double value);
	char getRandomAction(state theState);
	std::map<std::pair<int,char>,double> Qvalues;
	World * wm;
	float discound;
	//RL
	float learningRate;
	float explorationRate;

};

#endif /* AGENT_H_ */
