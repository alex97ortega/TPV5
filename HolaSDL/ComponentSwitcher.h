#ifndef COMPONENTSWITCHER_H_
#define COMPONENTSWITCHER_H_

#include <SDL.h>
#include <vector>

#include "GameObject.h"
#include "GameComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class ComponentSwitcher: public GameObject {
public:

	ComponentSwitcher(SDLGame* game, GameComponent* actor, SDL_Keycode ctrlKey, RenderComponent* render, GameComponent* icon);
	virtual ~ComponentSwitcher();

	virtual void switchToNext();
	virtual void setMode(int i);
	virtual void addMode(InputComponent* inputComp,
			PhysicsComponent* physicsComp, RenderComponent* renderComp,
			RenderComponent* modeRendered);

	// from GameObject
	virtual void update();
	virtual void handleInput(const SDL_Event& event);
	virtual void render();

	enum MODE {
		TECLADO, RATON, IA
	};

	int currentMode = TECLADO;

private:

	struct modos{
		InputComponent* inputCompM;
		PhysicsComponent* physicsCompM;
		RenderComponent* renderCompM;
		RenderComponent* modeRenderedM;
	};
	
	modos modo;

	std::vector <modos> inputComps;
	GameComponent* Icon;
	RenderComponent* Render;

	GameComponent* actor_;
	SDL_Keycode ctrlKey_;


	


};

#endif /* COMPONENTSWITCHER_H_ */
