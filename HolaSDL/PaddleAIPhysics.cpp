#include "PaddleAIPhysics.h"

PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
ball_(ball) {
}

PaddleAIPhysics::~PaddleAIPhysics() {
	delete ball_;
}

void PaddleAIPhysics::init(GameObject* paddle) {
	 if (i < 2){
		paddle->setPositionY(paddle->getGame()->getWindowHeight() / 2);
		i++;
	}
}

void PaddleAIPhysics::update(GameObject* paddle) {

	if (ball_->getPosition().getX() - paddle->getPosition().getX() > 0){

		if (ball_->getDirection().getX() > 0){

			if (paddle->getPosition().getY() > paddle->getGame()->getWindowHeight() / 2){
				paddle->setDirectionY(-1);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());
			}
			else if (paddle->getPosition().getY() < paddle->getGame()->getWindowHeight() / 2){
				paddle->setDirectionY(1);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());
			}
		}
		/*****la bola va hacia un lado u otro********/
		else{
			if (ball_->getPosition().getY() < paddle->getPosition().getY()){
				paddle->setDirectionY(-5);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());

				if (paddle->getPosition().getY() + paddle->getDirection().getY() <= 0){
					paddle->setPositionY(0);
					paddle->setDirection(paddle->getDirection().getX(), 0);
				}
			}
			/********parte de arriba o de abajo***********/
			else if (ball_->getPosition().getY() > paddle->getPosition().getY()){
				paddle->setDirectionY(5);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());

				if (((paddle->getPosition().getY() + paddle->getHeight()) + paddle->getDirection().getY()) >= paddle->getGame()->getWindowHeight()){
					paddle->setPositionY(paddle->getGame()->getWindowHeight() - paddle->getHeight());
					paddle->setDirection(paddle->getDirection().getX(), 0);
				}
			}
		}
	}

	/*********una u otra pala*******/

	else if (ball_->getPosition().getX() - paddle->getPosition().getX() < 0){

		if (ball_->getDirection().getX() < 0){

			if (paddle->getPosition().getY() > paddle->getGame()->getWindowHeight() / 2){
				paddle->setDirectionY(-2);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());
			}
			else if (paddle->getPosition().getY() < paddle->getGame()->getWindowHeight() / 2){
				paddle->setDirectionY(2);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());
			}
		}
		/*****la bola va hacia un lado u otro********/
		else{
			if (ball_->getPosition().getY() < paddle->getPosition().getY()){
				paddle->setDirectionY(-5);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());

				if (paddle->getPosition().getY() + paddle->getDirection().getY() <= 0){
					paddle->setPositionY(0);
					paddle->setDirection(paddle->getDirection().getX(), 0);
				}
			}
			/********parte de arriba o de abajo***********/
			else if (ball_->getPosition().getY() > paddle->getPosition().getY()){
				paddle->setDirectionY(5);
				paddle->setPositionY(paddle->getPosition().getY() + paddle->getDirection().getY());

				if (((paddle->getPosition().getY() + paddle->getHeight()) + paddle->getDirection().getY()) >= paddle->getGame()->getWindowHeight()){
					paddle->setPositionY(paddle->getGame()->getWindowHeight() - paddle->getHeight());
					paddle->setDirection(paddle->getDirection().getX(), 0);
				}
			}
		}
	}
}