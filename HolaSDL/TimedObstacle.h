#ifndef TIMEDOBSTACLE_H_
#define TIMEDOBSTACLE_H_

#include "GameObject.h"
#include "GameStateObserver.h"
#include "TimedObstacleObserver.h"

class TimedObstacle : 
	public GameObject, public GameStateObserver {
public:
	TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball);
	virtual ~TimedObstacle();
	virtual void addObserver(TimedObstacleObserver* o);
}

#endif
