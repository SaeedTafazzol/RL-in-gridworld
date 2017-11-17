/*
 * DrwaWorld.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: potato
 */

#include "DrwaWorld.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <boost/lexical_cast.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
using namespace cv;
DrwaWorld::DrwaWorld(World * w,Agent * agent,int d) {
	// TODO Auto-generated constructor stub
	wm = w;
	ag = agent;
	delay = d;




}

DrwaWorld::~DrwaWorld() {
	// TODO Auto-generated destructor stub
}

double round(int a,double j){
	j = j * (pow(10,a));
	j = rint(j);
	j = j / (pow(10,a));
	return j;
}

void DrwaWorld::execute(){
	while(wm->getState(wm->getAgentPos().x,wm->getAgentPos().y).getType()!=goal && wm->getState(wm->getAgentPos().x,wm->getAgentPos().y).getType()!=obstacle){

		Mat myMat(1000,1000,CV_8UC3,Scalar(0));

		for(int i = 0;i<10;i++)
			for(int j = 0;j<10;j++){
				std::ostringstream strs;
				strs << round(4,ag->getValue(wm->getState(i,j)));
				std::string a = strs.str();

				std::ostringstream strz;
				strz << ag->getPolicy(wm->getState(i,j));
				std::string b = strz.str();
				if(ag->getValue(wm->getState(i,j))>0)
					rectangle(myMat,Point(i*100,j*100),Point((i+1)*100,(j+1)*100),Scalar(0,255*ag->getValue(wm->getState(i,j)),0),-1,CV_AA);
				else
					rectangle(myMat,Point(i*100,j*100),Point((i+1)*100,(j+1)*100),Scalar(0,0,-255*ag->getValue(wm->getState(i,j))),-1,CV_AA);

				putText(myMat,a,Point(i*100 +20,j*100 + 50),0,0.5,Scalar(255,255,255),1,0,false);
				putText(myMat,b,Point(i*100 +20,j*100 + 70),0,0.5,Scalar(255,255,255),1,0,false);



			}
		circle(myMat,Point(wm->getAgentPos().x*100 + 50,wm->getAgentPos().y*100 + 50),10,Scalar(255,0,0),+20,0);
		imshow("mymat",myMat);

		ag->move();
		cvWaitKey(delay);
	}

}
