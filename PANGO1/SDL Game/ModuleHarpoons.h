#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Harpoon
{
	Animation anim;
	unsigned int fx;
	int counting = 0;
	p2Point<int> position;
	p2Point<int> speed;
	bool fx_played;
	Collider* collider;

	SDL_Rect tail01;
	SDL_Rect tail02;
	SDL_Rect tail03;
	SDL_Rect tail04;

	Harpoon();
	Harpoon(const Harpoon& p);
	~Harpoon();
	bool Update();
};

class ModuleHarpoons : public Module
{
public:
	ModuleHarpoons(Application* app, bool start_enabled = true);
	~ModuleHarpoons();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	void AddHarpoon(const Harpoon& Harpoon, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics;
	p2List<Harpoon*> active;

public:

	Harpoon shot;

};