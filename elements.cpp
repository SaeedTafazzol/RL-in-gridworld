/*
 * elements.cpp


 *
 *  Created on: Oct 12, 2017
 *      Author: potato
 */
#ifndef ELEMENTS_CPP
#define ELEMENTS_CPP
enum state_type{
	normal,
	goal,
	obstacle
};
class Vector2D{
public:
	int x;
	int y;
	Vector2D(int xx,int yy)
	:x(xx),y(yy)
	{}

	Vector2D()
	:x(0),y(0){

	}

private:
};
class state {
private:
	state_type type;
public:
	Vector2D position;

	state(state_type t,Vector2D pos):type(t),position(pos){

	}
	state():type(normal),position(Vector2D(-1000,-1000)){

	}
	void setType(state_type t){
		type = t;
	}
	state_type getType(){
		return type;
	}
	void setPos(Vector2D pos){
		position = pos;
	}
    Vector2D getPos(){
    	return position;
    }

    bool isInvalid(){
    	if(position.x==-1000 && position.y==-1000)
    		return true;
    	return false;
    }

};



#endif



