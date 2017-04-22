#ifndef PINGPONGPHYSICS_H_
#define PINGPONGPHYSICS_H_

#include "PhysicsComponent.h"
#include "BallObserver.h"
#include "GameStateObserver.h"

class PingPongPhysics: public PhysicsComponent, public GameStateObserver {
public:
	PingPongPhysics(GameObject* left_paddle, GameObject* right_paddle);
	virtual ~PingPongPhysics();

	virtual void resgisterBallObserver(BallObserver* o);

	// from GameStateObserver
	virtual void onGameStart();
	virtual void onGameOver();
	virtual void onRoundStart();
	virtual void onRoundOver();

	// from PhysicsComponent
	virtual void init(GameObject* o);
	virtual void update(GameObject* o);

	void bounceOnPaddle(GameObject* o, GameObject* paddle);

private:
	GameObject* left_paddle_;
	GameObject* right_paddle_;

	GameObject* ball_;

	int hits_;
	int speed_;

	std::vector<BallObserver*> observer;
	
};

#endif /* PINGPONGPHYSICS_H_ */
