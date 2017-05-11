

#include "GameObject.h"
#include "GameStateObserver.h"
#include "TimedObstacleObserver.h"

class TimedObstacle : public GameObject, public GameStateObserver {

public:

	TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball);
	virtual ~TimedObstacle();
	virtual void addObserver(TimedObstacleObserver* o);
	void update(GameObject* o);
	
	void Fptime();
	void Fdtime();
	
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