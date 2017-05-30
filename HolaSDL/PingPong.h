#ifndef PINGPONG_H_
#define PINGPONG_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "SDLGame.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameManager.h"
#include "ComponentSwitcher.h"
#include "PingPongPhysics.h"
#include "TimedObstacle.h"


class PingPong: public SDLGame {

public:
	PingPong();
	virtual ~PingPong();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput();
	void update();
	void render();

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

	GameComponent* ball_;
	GameComponent* left_paddle_;
	GameComponent* right_paddle_;
	GameComponent* leftIcon;
	GameComponent* rightIcon;

	RenderComponent* leftIconIMG;
	RenderComponent* rightIconIMG;

	GameManager* gameManager_;

	RenderComponent* rectangleRenderer_;
	RenderComponent* imageRenderer_;


	PhysicsComponent* bounceOnBorderPhysics_;
	PhysicsComponent* stopOnBorderPhysics_;
	PhysicsComponent* paddleAI;
	PingPongPhysics* pingpong;


	InputComponent* inputKeyCompLeft_;
	InputComponent* inputKeyCompRight_;
	InputComponent* inputMouseComp_;

	ComponentSwitcher* player1;
	ComponentSwitcher* player2;

	TimedObstacle* obstaculo;
	

	std::vector<GameObject*> actors_;

	bool exit_;

	InputComponent* paddleInput1 =  new PaddleKeyboardInputComp(SDLK_a, SDLK_z, SDLK_s, 10);
	InputComponent* paddleInput2 = new PaddleKeyboardInputComp(SDLK_UP, SDLK_DOWN, SDLK_SPACE, 10);
	PhysicsComponent* stopPhysics = new StopOnBordersPhysics(false, false, true, true);
	InputComponent* mouseInput = new PaddleMouseInputComp();

	PhysicsComponent* playerBall = new PaddleAIPhysics(ball_);

	RenderComponent* keyboardIcon =	new ImageRendered(getResources()->getTexture(SDLGame::KeyBoardIcon));
	RenderComponent* mouseIcon = new ImageRendered(getResources()->getTexture(SDLGame::MouseIcon));
	RenderComponent*  AIicon = new ImageRendered(getResources()->getTexture(SDLGame::AIIcon));

	

};

#endif /* PINGPONG_H_ */
