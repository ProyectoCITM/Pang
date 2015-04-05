#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePlayer.h"

class ModuleHarpoons : public Module
{
public:
	ModuleHarpoons(Application* app);
	~ModuleHarpoons();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics;
	Animation regular_harpoon;
	Animation grab_harpoon;
	Animation fix_grab_harpoon;
	Animation gun;
	p2Point<int> position_harpoon;
	int speed = 1;
};