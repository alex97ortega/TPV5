#include "ComponentSwitcher.h"

ComponentSwitcher::ComponentSwitcher(SDLGame* game, GameComponent* actor,
	SDL_Keycode ctrlKey, RenderComponent* render, GameComponent* icon) :
		GameObject(game), actor_(actor), ctrlKey_(ctrlKey), Render(render), Icon(icon) {
}

ComponentSwitcher::~ComponentSwitcher() {
}

void ComponentSwitcher::update() {
}

void ComponentSwitcher::handleInput(const SDL_Event& event) {
	if (event.type == SDL_KEYUP)
		if (event.key.keysym.sym == ctrlKey_) 
			switchToNext();

}

void ComponentSwitcher::addMode(InputComponent* inputComp, PhysicsComponent* physicsComp, RenderComponent* renderComp, RenderComponent* modeRendered) {
	
	modo.inputCompM = inputComp; 
	modo.physicsCompM = physicsComp; 
	modo.renderCompM = renderComp; 
	modo.modeRenderedM = modeRendered;

	inputComps.push_back(modo);
}

void ComponentSwitcher::setMode(int mode) {

	actor_->setInputComponent(inputComps[mode].inputCompM);
	actor_->setPhysicsComponent(inputComps[mode].physicsCompM);
	actor_->setRenderComponent(inputComps[mode].renderCompM);
	Render = inputComps[mode].modeRenderedM;
}

void ComponentSwitcher::switchToNext() {
	if (currentMode == IA){
		currentMode = TECLADO;
		setMode(currentMode);
	}
	else{
		currentMode += 1;
		setMode(currentMode);
	}
}

void ComponentSwitcher::render() {
	Render->render(Icon);
}
