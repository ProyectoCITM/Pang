#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModuleFruit : public Module
{
public:
	ModuleFruit(Application* app);
	~ModuleFruit();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics;
	SDL_Rect cherry;
	SDL_Rect cake;
	p2Point<int> position_fruit;
};