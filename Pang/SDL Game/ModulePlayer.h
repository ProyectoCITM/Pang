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

	// Player 2
	Animation* last_animation2 = NULL;
	Animation idleR2;
	Animation idleL2;
	Animation right2;
	Animation left2;
	Animation stairs2;
	Animation shootR2;
	Animation shootL2;
	p2Point<int> position2;
};