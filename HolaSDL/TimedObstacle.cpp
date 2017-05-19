#include "TimedObstacle.h"
#include "RectRender.h"


TimedObstacle::TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball) : GameObject(game)
{
	ptime = pTime;
	dtime = dTime;

	estado = false;
	gaming = true;

	c = { 255, 255, 255, 255 };
	rend = new RectRender(c);

	bola = ball;
}

TimedObstacle::~TimedObstacle()
{
}

void TimedObstacle::addObserver(TimedObstacleObserver* o){
	
	observers.emplace_back(o);
	nObbservers++;
}

Uint32 ptimeFunc(Uint32 intervalo, void * param){
	static_cast<TimedObstacle*>(param)->Fptime();
	return 0;
}

Uint32 dtimeFunc (Uint32 intervalo, void * param){
	static_cast<TimedObstacle*>(param)->Fdtime();
	return 0;
}

void TimedObstacle::Fptime(){
	if (rand() % 2 == 0){
		estado = true;
		for (int i = 0; i < nObbservers; i++){
			observers[i]->onObstacleStateChange(this, estado);
		}
		SDL_AddTimer(dtime, dtimeFunc, this);
		setHeight(50);
		setWidth(50);
		setPosition(rand() % 500 + 100, rand() % 400 + 100);
	}
	else
		gaming = true;
}

void TimedObstacle::Fdtime(){
	gaming = true;
	estado = false;
	for (int i = 0; i < nObbservers; i++){
		observers[i]->onObstacleStateChange(this, estado);
	}
}

void TimedObstacle::update(){
	if (gaming){
		SDL_AddTimer(ptime, ptimeFunc, this);
		gaming = false;
	}

	

	if (bola->getPosition().getX() > getPosition().getX() && bola->getPosition().getX() < getPosition().getX() + getWidth() &&
		bola->getPosition().getY() > getPosition().getY() && bola->getPosition().getY() < getPosition().getY() + getHeight()){
		estado = false;
		for (int i = 0; i < nObbservers; i++){
			observers[i]->onObstacleCollision(this, bola);
		}
	}
}

void TimedObstacle::render(){
	if (estado){
		rend->render(this);
	}
}
