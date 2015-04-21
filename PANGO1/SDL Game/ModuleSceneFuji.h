#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneFuji : public Module
{
public:
	ModuleSceneFuji(Application* app, bool start_enabled = true);
	~ModuleSceneFuji();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Rect background;
	SDL_Texture* graphics;

};