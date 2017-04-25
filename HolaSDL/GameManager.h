#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "SDLGame.h"
#include "GameObject.h"
#include "BallObserver.h"
#include "GameStateObserver.h"
#include "Font.h"
#include "Texture.h"

class GameManager: public GameObject, public BallObserver {

public:
	GameManager(SDLGame* game, GameObject* leftPaddle, GameObject* rightPaddle);
	virtual ~GameManager();

	virtual void registerGameStateObserver(GameStateObserver* o);

	// from GameObject
	virtual void handleInput(const SDL_Event& e);
	virtual void update();
	virtual void render();

	// from BallObserver
	virtual void onCollision(GameObject* ball, GameObject* o);
	virtual void onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side);

private:
	Font* font_;
	Texture startMsgTexture_;
	Texture scoreT;
	Texture winnerT;

	int leftScore = 0;
	int	rightScore = 0;

	std::string score = std::to_string(leftScore) + "  -  " + std::to_string(rightScore);
	std::string winner;

	std::vector<GameStateObserver*> observers;
	int nObservers;

	SoundEffect* wallHit;
	SoundEffect* paddleHit;

	GameObject* palaGuapa1;
	GameObject* palaGuapisima2; // victor es un vago de mierda y un borracho heliocentrista 25/04/2017

	GameObject* last_paddle_hit_​; // atributo guapisimo

	bool jugar= false;

	bool jugando = false;

	SDL_Color color;
};

#endif /* SCOREBOARD_H_ */
