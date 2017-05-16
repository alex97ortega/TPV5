#include <string>
#include <cmath>
#include <random>

#include "GameManager.h"


GameManager::GameManager(SDLGame* game, GameObject* l, GameObject* r) :GameObject(game) {
	font_ = game_->getResources()->getFont(SDLGame::NESChimera16);

	color = { 255, 255, 255, 255 };

	startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);

	scoreT.loadFromText(getGame()->getRenderer(), score, *font_, color);

	wallHit = game->getResources()->getSoundEffect(SDLGame::Wall_Hit);
	paddleHit = game->getResources()->getSoundEffect(SDLGame::Paddle_Hit);

	palaL = l;
	palaR = r;
}

GameManager::~GameManager() {
	font_ = nullptr;

	wallHit = nullptr;
	paddleHit = nullptr;

	palaL = nullptr;
	palaR = nullptr;


	delete font_;

	delete wallHit;
	delete paddleHit;

	delete palaL;
	delete palaR;
}

void GameManager::update() {

}

void GameManager::handleInput(const SDL_Event& event) {

	if (event.key.keysym.sym == SDLK_SPACE){
		if (!jugando){
			for (int i = 0; i < nObservers; i++){
				observers[i]->onGameStart();
			}
			rightScore = 0;
			leftScore = 0;
			jugando = true;
		}
		else{
			if (!jugar)
			for (int i = 0; i < nObservers; i++){
				observers[i]->onRoundStart();
			}
			jugar = true;
		}

	}
}

void GameManager::render() {

	// just an example, should be adjusted to the requirements!
	if (!jugar)
		startMsgTexture_.render(getGame()->getRenderer(), (getGame()->getWindowWidth()-startMsgTexture_.getWidth()) / 2, getGame()->getWindowHeight()-40);


	scoreT.loadFromText(getGame()->getRenderer(), score, *font_, color);
	scoreT.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - scoreT.getWidth()) / 2, 10);

	if (!jugar && !jugando){
		winnerT.loadFromText(getGame()->getRenderer(),winner, *font_, color);
		winnerT.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - winnerT.getWidth()) / 2, getGame()->getWindowHeight() / 2);
	}
}

void GameManager::onCollision(GameObject* ball, GameObject* o) {
	last_paddle_hit_​ = o;
	paddleHit->play();
}

void GameManager::onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side) {

	if (side == TOP) 
		wallHit->play();

	else if (side == BOT) 
		wallHit->play();

	else if (side == RIGHT){
		leftScore++;
		if (leftScore == 5){
			for (int i = 0; i < nObservers; i++){
				observers[i]->onGameOver();
				winner = "Player 1 is DOMINATING";
				jugando = false;
				jugar = false;
				leftScore = 0;
				rightScore = 0;
				last_paddle_hit_​ = nullptr;
			}
		}
		else {
			for (int i = 0; i < nObservers; i++){
				observers[i]->onRoundOver();
				jugar = false;
			}
		}
	}

	else if (side == LEFT){
		rightScore++;
		if (rightScore == 5){
			for (int i = 0; i < nObservers; i++){
				observers[i]->onGameOver();
				winner = "Player 2 is DOMINATING";
				jugando = false;
				jugar = false;
				leftScore = 0;
				rightScore = 0;
				last_paddle_hit_​ = nullptr;
			}
		}
		else{
			for (int i = 0; i < nObservers; i++){
				observers[i]->onRoundOver();
				jugar = false;
			}
		}
	}

	score = std::to_string(leftScore) + "  -  " + std::to_string(rightScore);

}

void GameManager::registerGameStateObserver(GameStateObserver* o) {
	observers.push_back(o);
	nObservers++;
}


void GameManager::onObstacleCollision(GameObject* obs, GameObject* o){
	obs->update(); o->update();
}

void GameManager::onObstacleStateChange(GameObject* obs, bool state){


}