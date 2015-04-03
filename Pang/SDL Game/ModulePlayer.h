#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app);
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	Animation* last_animation = NULL;
	SDL_Texture* graphics;
	Animation idleR;
	Animation idleL;
	Animation right;
	Animation left;
	Animation stairs;
	Animation shootR;
	Animation shootL;
	p2Point<int> position;

};