#include "StopOnBordersPhysics.h"

StopOnBordersPhysics::StopOnBordersPhysics(bool left, bool right, bool top,
		bool bottom) :
		left_(left), right_(right), top_(top), bottom_(bottom) {
}

StopOnBordersPhysics::~StopOnBordersPhysics() {

}

void StopOnBordersPhysics::init(GameObject* o) {
}


void StopOnBordersPhysics::update(GameObject* o) {
	
	if (o->getPosition().getX() + o->getDirection().getX < 0 && left_){
		o->setDirectionX(0);
		o->setPositionX(o->getPosition().getX);
	}
	if (o->getPosition().getX() + o->getDirection().getX > 480 && right_){

	}
	if (o->getPosition().getY() + o->getDirection().getY() < 0 && top_){

	}
	if (o->getPosition().getY() + o->getDirection().getY() > 640 && bottom_){

	}
}
