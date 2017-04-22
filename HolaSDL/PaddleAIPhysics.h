#ifndef PADDLEAIPHYSICS_H_
#define PADDLEAIPHYSICS_H_

#include "PhysicsComponent.h"


class PaddleAIPhysics : public PhysicsComponent {
public:
	PaddleAIPhysics();
	PaddleAIPhysics(GameObject* ball);
	virtual ~PaddleAIPhysics();

	// from PhysicsComponent
	virtual void init(GameObject* paddle);
	virtual void update(GameObject* paddle);

	void goCenter(GameObject* paddle, int velocity);
	void predicDirection(GameObject* paddle, int velocity);

private:
	GameObject* ball_;
	int i = 0;
};


#endif /* PADDLEAIPHYSICS_H_ */
