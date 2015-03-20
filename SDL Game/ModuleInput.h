#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleInput : public Module
{
public:
	
	ModuleInput(Application* app);
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

	const Uint8 *keyboard;
};