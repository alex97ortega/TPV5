#include "PaddleMouseInputComp.h"

PaddleMouseInputComp::PaddleMouseInputComp() {
}

PaddleMouseInputComp::~PaddleMouseInputComp() {

}

void PaddleMouseInputComp::init(GameObject* paddle) {

	paddle->setPosition(paddle->getPosition().getX(), 0);
}

void PaddleMouseInputComp::handleInput(SDL_Event event, GameObject* paddle) {
	if (event.motion.type == SDL_MOUSEMOTION)
		paddle->setPositionY(event.motion.y);
}
