

#include "GameObject.h"
#include "GameStateObserver.h"
#include "TimedObstacleObserver.h"
#include "RectRender.h"

class TimedObstacle : public GameObject, public GameStateObserver {

public:

	TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball);
	virtual ~TimedObstacle();
	virtual void addObserver(TimedObstacleObserver* o);
	virtual void update();
	virtual void handleInput(const SDL_Event& event){};
	virtual void render();
	virtual void onGameStart(){};
	virtual void onGameOver(){};
	virtual void onRoundStart(){};
	virtual void onRoundOver(){};



	void Fptime();
	void Fdtime();
	
private:

	int ptime;
	int dtime;
	bool estado;
	bool gaming;

	GameObject* bola;

	SDL_Color c;
	RectRender* rend;
	std::vector<TimedObstacleObserver*> observers;
	int nObbservers = 0;

};