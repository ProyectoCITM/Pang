#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app);
	~ModulePlayer2();

	bool Start();
	update_status Update();

public:

	Animation* last_animation2 = NULL;
	SDL_Texture* graphics2;
	Animation idleR2;
	Animation idleL2;
	Animation right2;
	Animation left2;
	Animation stairs2;
	Animation shootR2;
	Animation shootL2;
	p2Point<int> position2;
};