#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModuleBalloons : public Module
{
public:
	ModuleBalloons(Application* app);
	~ModuleBalloons();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* graphics;
	Animation red_explosion_big;
	Animation red_explosion_mid;
	Animation red_explosion_tiny;
	Animation red_explosion_end;
	Animation idle_ball;
	p2Point<int> position_ball;
	float alpha = 270;
	int speed = 1;
};