#include "Globals.h"
#include "Application.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground(Application* app) : Module(app)
{
	graphics = NULL;

	// Background 1
	background.x = 8;
	background.y = 8;
	background.w = 384;
	background.h = 208;

}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("pang_background.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, NULL); // Background 1
	return UPDATE_CONTINUE;
}