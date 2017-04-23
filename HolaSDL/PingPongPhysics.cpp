#include <cmath>
#include <random>
#include "PingPongPhysics.h"

PingPongPhysics::PingPongPhysics(GameObject* left_paddle,
		GameObject* right_paddle, GameObject* ball) :
		left_paddle_(left_paddle), right_paddle_(right_paddle), ball_(ball), hits_(
				0), speed_(0) {
}

PingPongPhysics::~PingPongPhysics() {
	left_paddle_ = nullptr;
	right_paddle_ = nullptr;

	ball_ = nullptr;

	delete left_paddle_;
	delete right_paddle_;

	delete ball_;
}

void PingPongPhysics::init(GameObject* o) {
}

void PingPongPhysics::update(GameObject* o) {

	o->setPosition(o->getPosition().getX() + o->getDirection().getX(), o->getPosition().getY() + o->getDirection().getY());

	if (o->getPosition().getX() < 0){
		for (int i = 0; i < nObservers; i++)
			observer[i]->onBorderExit(o, BallObserver::LEFT);
	}

	else if (o->getPosition().getX() > o->getGame()->getWindowWidth()){
		for (int i = 0; i < nObservers; i++)
			observer[i]->onBorderExit(o, BallObserver::RIGHT);
	}

	else if (o->getPosition().getY() < 0){
		for (int i = 0; i < nObservers; i++)
			observer[i]->onBorderExit(o, BallObserver::TOP);
		o->setDirectionY(-1 * o->getDirection().getY());
	}

	else if (o->getPosition().getY() > o->getGame()->getWindowHeight()){
		for (int i = 0; i < nObservers; i++)
			observer[i]->onBorderExit(o, BallObserver::BOT);
		o->setDirectionY(-1 * o->getDirection().getY());
	}



	if ((o->getPosition().getX() >= left_paddle_->getPosition().getX() && o->getPosition().getX() <= left_paddle_->getPosition().getX() + left_paddle_->getWidth())
		&& (o->getPosition().getY() >= left_paddle_->getPosition().getY() && o->getPosition().getY() <= left_paddle_->getPosition().getY() + left_paddle_->getHeight())){
		//ver si esta en lo que abarca la raqueta

		for (int i = 0; i < nObservers; i++){
			observer[i]->onCollision(o, left_paddle_);
		}

		hits_++;

		if (hits_ == 5){
			hits_ = 0;
			speed_++;
		}

		int sign = o->getDirection().getX() < 0 ? 1 : -1;
		int rel_y = (o->getPosition().getY() - left_paddle_->getPosition().getY() + o->getHeight());
		float angle = (2.14f * rel_y - 75.0f);
		int dx = sign * speed_ * std::cos(angle * M_PI / 180.0f);
		int dy = speed_ * std::sin(angle * M_PI / 180.0f);

		o->setDirection(dx, dy);
	}

	//lo mismo para la otra


	if ((o->getPosition().getX() >= right_paddle_->getPosition().getX() && o->getPosition().getX() <= right_paddle_->getPosition().getX() + left_paddle_->getWidth())
		&& (o->getPosition().getY() >= right_paddle_->getPosition().getY() && o->getPosition().getY() <= right_paddle_->getPosition().getY() + left_paddle_->getHeight())){
		//ver si esta en lo que abarca la raqueta

		for (int i = 0; i < nObservers; i++){
			observer[i]->onCollision(o, right_paddle_);
		}

		hits_++;

		if (hits_ == 5){
			hits_ = 0;
			speed_++;
		}

		int sign = o->getDirection().getX() < 0 ? 1 : -1;
		int rel_y = (o->getPosition().getY() - right_paddle_->getPosition().getY() + o->getHeight());
		float angle = (2.14f * rel_y - 75.0f);
		int dx = sign * speed_ * std::cos(angle * M_PI / 180.0f);
		int dy = speed_ * std::sin(angle * M_PI / 180.0f);

		o->setDirection(dx, dy);
	}




	
}


void PingPongPhysics::resgisterBallObserver(BallObserver* o) {
	observer.push_back(o);
	nObservers++;
}


void PingPongPhysics::onGameStart() {
	ball_->setDirection((rand() % 5) + 3, (rand() % 5) + 3);
}

void PingPongPhysics::onGameOver() {
	ball_->setPosition(ball_->getGame()->getWindowWidth() / 2, ball_->getGame()->getWindowHeight() / 2);
	ball_->setDirection(0, 0);
}

void PingPongPhysics::onRoundStart() {
	hits_ = 0; 
	speed_ = 8;
	int direction = 1 - 2 * (rand() % 2);
	int angle = 60 - (rand() % 121);
	int dx = direction * speed_ * std::cos(angle * M_PI / 180.0f);
	int dy = speed_ * std::sin(angle * M_PI / 180.0f);
	ball_->setDirection(dx, dy);
}

void PingPongPhysics::onRoundOver() {
	ball_->setPosition(ball_->getGame()->getWindowWidth() / 2, ball_->getGame()->getWindowHeight() / 2);
	ball_->setDirection(0, 0);
}

