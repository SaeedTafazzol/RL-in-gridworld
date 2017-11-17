/*
 * DrwaWorld.h
 *
 *  Created on: Oct 14, 2017
 *      Author: potato
 */

#ifndef DRWAWORLD_H_
#define DRWAWORLD_H_
#include "elements.cpp"
#include "World.h"
#include "Agent.h"
class DrwaWorld {
public:
	DrwaWorld(World * w,Agent * agent,int d);
	virtual ~DrwaWorld();
	void execute();

private:

	World * wm;
	Agent * ag;
	int delay;


};

#endif /* DRWAWORLD_H_ */
