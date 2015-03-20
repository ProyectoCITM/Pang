#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleRender : public Module
{
public:
	ModuleRender(Application* app);
	~ModuleRender();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);

public:
	SDL_Renderer* renderer;
};