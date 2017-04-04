#include "StopOnBordersPhysics.h"

StopOnBordersPhysics::StopOnBordersPhysics(bool left, bool right, bool top,
		bool bottom) :
		left_(left), right_(right), top_(top), bottom_(bottom) {
}

StopOnBordersPhysics::~StopOnBordersPhysics() {

}

void StopOnBordersPhysics::init(GameObject* o) {
	//sonidico
}


void StopOnBordersPhysics::update(GameObject* o) {
	if (top_ &&o->getPosition().getY() + o->getDirection().getY() <= 0) {
		o->setPositionY(o->getPosition().getY());
		o->setDirectionY(0);
	}

	else if (bottom_	&& o->getPosition().getY() + o->getDirection().getY() <=
		o->getGame()->getWindowHeight() - o->getHeight()) {
		o->setPositionY(o->getGame()->getWindowHeight() - o->getHeight());
		o->setDirectionY(0);
	}
	if (left_ &&o->getPosition().getX() + o->getDirection().getX() <= 0) {
		o->setPositionX(o->getPosition().getX());
		o->setDirectionX(0);
	}

	else if (right_	&& o->getPosition().getX() + o->getDirection().getX() <=
		o->getGame()->getWindowWidth() - o->getWidth()) {
		o->setPositionX(o->getGame()->getWindowWidth() - o->getWidth());
		o->setDirectionX(0);
	}
}
