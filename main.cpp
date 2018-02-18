//============================================================================
// Name        : f.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "World.h"
#include "DrwaWorld.h"

#include <time.h>
#include <stdlib.h>     /* srand, rand */


using namespace std;

int main() {
	World w ;
	Agent agent(&w);
	srand(time(NULL));
	for(int i = 0;i<=100000;){
		cout<<i<<endl;
		//agent.move();
		DrwaWorld monitor(&w,&agent,1);
		monitor.execute();
		if(w.getState(w.getAgentPos().x,w.getAgentPos().y).getType()==goal||w.getState(w.getAgentPos().x,w.getAgentPos().y).getType()==obstacle){
			w.reset(true);
			i++;
		}
	}
	w.reset(false);
	agent.turnOffLearning();
	DrwaWorld monitor(&w,&agent,200);
	monitor.execute();

	/*
	 agent

	 */




	

	return 0;
}
