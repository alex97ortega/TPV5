

#include "GameObject.h"
#include "GameStateObserver.h"
#include "TimedObstacleObserver.h"
#include "RenderComponent.h"

class TimedObstacle : public GameObject, public GameStateObserver {

public:

	TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball);
	virtual ~TimedObstacle();
	virtual void addObserver(TimedObstacleObserver* o);

	void handleInput(const SDL_Event& event){}
	void update();
	void render(){}
	void Fptime();
	void Fdtime();
	

	void onGameStart(){}
	 void onGameOver(){}
	 void onRoundStart(){}
	 void onRoundOver(){}
private:

	int ptime;
	int dtime;
	bool estado;
	bool gaming;

	GameObject* bola;

	RenderComponent* rend;
	std::vector<TimedObstacleObserver*> observers;
	int nObbservers = 0;

};