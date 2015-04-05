#include "Globals.h"
#include "Application.h"
#include "ModuleHarpoons.h"
#include <math.h>

ModuleHarpoons::ModuleHarpoons(Application* app) : Module(app)
{
	// Balloons Sprites -------------------------------------
	graphics = NULL;

	position_harpoon.x = 134;
	position_harpoon.y = 200;

	//Regular_harpoon
	regular_harpoon.frames.PushBack({ 3, 0, 16, 200 });
	regular_harpoon.frames.PushBack({ 21, 0, 16, 200 });
	regular_harpoon.speed = 0.1f;
}

ModuleHarpoons::~ModuleHarpoons()
{}

// Load assets
bool ModuleHarpoons::Start()
{
	LOG("Loading balloons textures");
	bool ret = true;
	graphics = App->textures->Load("harpoons_allin.png"); // arcade version
	return ret;
}

// Update: Balloons
update_status ModuleHarpoons::Update()
{
	Animation* current_animation_harpoon = &regular_harpoon;

	// Draw everything --------------------------------------
	SDL_Rect rb = current_animation_harpoon->GetCurrentFrame();

	App->renderer->Blit(graphics, position_harpoon.x, position_harpoon.y - rb.h, &rb);

	return UPDATE_CONTINUE;
}