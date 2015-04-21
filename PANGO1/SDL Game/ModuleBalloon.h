#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Balloon
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	float alpha = 270; // No sé ben bé quin posar
	int h = 140;
	bool fx_explosion;
	Collider* collider;

	Balloon();
	Balloon(const Balloon& b);
	~Balloon();
	bool Update();
};

class ModuleBalloon : public Module
{
public:
	ModuleBalloon(Application* app, bool start_enabled = true);
	~ModuleBalloon();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	void AddBalloon(const Balloon& balloon, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics;
	p2List<Balloon*> active;

public:

	Balloon red_big_ball;
	Balloon red_big_explosion;

};