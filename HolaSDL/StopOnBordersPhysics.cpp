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

	Vector2D<int> nextPos = o->getPosition() + o->getDirection();

	if (top_ && nextPos.getY() <= 0) {
		nextPos.setY(0);
		o->setPosition(nextPos);
		o->setDirectionY(0);
	}

	if (bottom_ && nextPos.getY() >= o->getGame()->getWindowHeight() - o->getHeight()) {
		nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
		o->setDirectionY(0);
	}


	o->setPosition(nextPos);
}
