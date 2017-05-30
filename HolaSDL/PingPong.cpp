#include "PingPong.h"
#include "BounceOnBorders.h"
#include "RectRender.h"
#include "ImageRendered.h"
#include "PaddleKeyboardInputComp.h"
#include "PaddleMouseInputComp.h"
#include "StopOnBordersPhysics.h"
#include "PaddleAIPhysics.h"
#include "PingPongPhysics.h"

PingPong::PingPong() :
		SDLGame("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

PingPong::~PingPong() {
	closeGame();
}

void PingPong::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	SDL_Color color = { 255, 255, 255, 255 };

	rectangleRenderer_ = new RectRender(color);
	imageRenderer_ = new ImageRendered( getResources()->getTexture(SDLGame::TennisBall) );
	leftIconIMG = new ImageRendered(getResources()->getTexture(SDLGame::KeyBoardIcon));
	rightIconIMG = new ImageRendered(getResources()->getTexture(SDLGame::KeyBoardIcon));


	
	bounceOnBorderPhysics_ = new BounceOnBorders(true, true, true, true);
	stopOnBorderPhysics_ = new StopOnBordersPhysics(false, false, true, true);
	paddleAI = new PaddleAIPhysics(ball_);
	

	inputKeyCompLeft_ = new PaddleKeyboardInputComp(SDLK_UP, SDLK_DOWN, SDLK_SPACE, 10);
	inputKeyCompRight_ = new PaddleKeyboardInputComp(SDLK_a, SDLK_z, SDLK_s, 10);
	inputMouseComp_ = new PaddleMouseInputComp();

	
	// ball
	ball_ = new GameComponent(this);
	ball_->setWidth(10);
	ball_->setHeight(10);
	ball_->setDirection( 0,0); // change to  (0,0) at the end
	ball_->setPosition(
			ball_->getGame()->getWindowWidth() / 2 - ball_->getWidth() / 2,
			ball_->getGame()->getWindowHeight() / 2 - ball_->getHeight() / 2);
	//ball_->setPhysicsComponent(bounceOnBorderPhysics_);
	//ball_->setRenderComponent(rectangleRenderer_);
	// use the following for an image of a tennis ball
	 ball_->setRenderComponent(imageRenderer_);


	// left paddle
	left_paddle_ = new GameComponent(this);
	left_paddle_->setWidth(10);
	left_paddle_->setHeight(60);
	left_paddle_->setPosition(30,
			(getWindowHeight() - left_paddle_->getHeight()) / 2);
	left_paddle_->setDirection(0, 0);
	//left_paddle_->setRenderComponent(rectangleRenderer_);
	//left_paddle_->setPhysicsComponent(stopOnBorderPhysics_);
	//left_paddle_->setInputComponent(inputMouseComp_);
	


	// right paddle
	right_paddle_ = new GameComponent(this);
	right_paddle_->setWidth(10);
	right_paddle_->setHeight(60);
	right_paddle_->setPosition(getWindowWidth() - 40,
			(getWindowHeight() - right_paddle_->getHeight()) / 2);
	right_paddle_->setDirection(0, 0);
	//right_paddle_->setRenderComponent(rectangleRenderer_);
	//right_paddle_->setPhysicsComponent(stopOnBorderPhysics_);
	//right_paddle_->setInputComponent(inputMouseComp_);

	pingpong = new PingPongPhysics(left_paddle_, right_paddle_, ball_);


	leftIcon = new GameComponent(this);
	leftIcon->setHeight(50);
	leftIcon->setWidth(50);
	leftIcon->setPosition(25, 25);
	player1 = new ComponentSwitcher(this, left_paddle_, SDLK_1, leftIconIMG, leftIcon);
	player1->addMode(paddleInput1, stopPhysics, rectangleRenderer_, keyboardIcon);
	player1->addMode(mouseInput, stopPhysics, rectangleRenderer_, mouseIcon);
	player1->addMode(NULL, playerBall, rectangleRenderer_, AIicon);
	player1->setMode(player1->currentMode);


	rightIcon = new GameComponent(this);
	rightIcon->setWidth(50);
	rightIcon->setHeight(50);
	rightIcon->setPosition(getWindowWidth() - rightIcon->getWidth() - 25, 25);
	player2 = new ComponentSwitcher(this, right_paddle_, SDLK_2, rightIconIMG, rightIcon);
	player2->addMode(paddleInput2, stopPhysics, rectangleRenderer_, keyboardIcon);
	player2->addMode(mouseInput, stopPhysics, rectangleRenderer_, mouseIcon);
	player2->addMode(NULL, playerBall, rectangleRenderer_, AIicon);
	player2->setMode(player2->currentMode);

	// game manager
	gameManager_ = new GameManager(this, left_paddle_, right_paddle_);

	pingpong->resgisterBallObserver(gameManager_);
	gameManager_->registerGameStateObserver(pingpong);
	ball_->setPhysicsComponent(pingpong);

	obstaculo = new TimedObstacle(this, 1000, 10000, ball_);
	obstaculo->addObserver(gameManager_);

	actors_.push_back(left_paddle_);
	actors_.push_back(right_paddle_);
	actors_.push_back(ball_);
	actors_.push_back(gameManager_);
	actors_.push_back(player1);
	actors_.push_back(player2);
	actors_.push_back(obstaculo);

}

void PingPong::closeGame() {
	right_paddle_ = nullptr;
	left_paddle_ = nullptr;
	ball_ = nullptr;
	leftIcon = nullptr;
	rightIcon = nullptr;

	gameManager_ = nullptr;

	rectangleRenderer_ = nullptr;
	imageRenderer_ = nullptr;

	bounceOnBorderPhysics_ = nullptr;
	stopOnBorderPhysics_ = nullptr;
	paddleAI = nullptr;
	pingpong = nullptr;


	inputKeyCompLeft_ = nullptr;
	inputKeyCompRight_ = nullptr;
	inputMouseComp_ = nullptr;

	player1 = nullptr;
	player2 = nullptr;
	obstaculo = nullptr;

	paddleInput1 = nullptr;
	paddleInput2 = nullptr;
	stopPhysics = nullptr;
	mouseInput = nullptr;
	playerBall = nullptr;
	keyboardIcon = nullptr;
	mouseIcon = nullptr;
	AIicon = nullptr;

	delete right_paddle_;
	delete left_paddle_;
	delete ball_;
	delete leftIcon;
	delete rightIcon;

	delete gameManager_;

	delete rectangleRenderer_;
	delete imageRenderer_;

	delete bounceOnBorderPhysics_;
	delete stopOnBorderPhysics_;
	delete paddleAI;
	delete pingpong;


	delete inputKeyCompLeft_;
	delete inputKeyCompRight_;
	delete inputMouseComp_;

	delete player1;
	delete player2;
	delete obstaculo;

	delete paddleInput1;
	delete paddleInput2;
	delete stopPhysics;
	delete mouseInput;
	delete playerBall;
	delete keyboardIcon;
	delete mouseIcon;
	delete AIicon;

}

void PingPong::start() {
	exit_ = false;
	while (!exit_) {
		handleInput();
		update();
		render();
		SDL_Delay(10);
		
	}
}

void PingPong::stop() {
	exit_ = true;
}

void PingPong::update() {
	for (unsigned int i = 0; i < actors_.size(); i++) {
		actors_[i]->update();
	}
}

void PingPong::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

	
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:


				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		
		for (unsigned int i = 0; i < actors_.size(); i++) {
			actors_[i]->handleInput(event);
		}

	}
}

void PingPong::render() {
	SDL_SetRenderDrawColor(getRenderer(), 0, 100, 100, 255);  // Dark grey.
	SDL_RenderClear(getRenderer());

	for (unsigned int i = 0; i < actors_.size(); i++) {
		actors_[i]->render();
	}

	SDL_RenderPresent(getRenderer());
}

