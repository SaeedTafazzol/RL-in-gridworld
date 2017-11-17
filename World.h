/*
 * World.h
 *
 *  Created on: Oct 12, 2017
 *      Author: potato
 */
#include "elements.cpp"
#include "Agent.h"
#include <vector>
#ifndef WORLD_H_
#define WORLD_H_


class World {
public:
	World();
	virtual ~World();
	void getLegalActions(state current,std::vector<char> & chars);
	std::pair<state,double> agentMoved(char action);
	//void agentMoved(char action);

	Vector2D getAgentPos();
	state getState(int x,int y);
	void reset(bool useRandom);
	////MDP **************************

	//	double getReward(state current,char action,state next);
	//	std::vector<std::pair<state,float> > getProb(state current,char action);
	////MDP **************************


private:

	double getReward(state current,char action,state next);
	std::vector<std::pair<state,float> > getProb(state current,char action);
	state states[10][10];
	Vector2D agentPos;


};

#endif /* WORLD_H_ */
