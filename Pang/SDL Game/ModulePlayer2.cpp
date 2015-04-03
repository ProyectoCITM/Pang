#include "Globals.h"
#include "Application.h"
#include "ModulePlayer2.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app) : Module(app)
{
	graphics2 = NULL;

	// Player 2
	position2.x = 192;
	position2.y = 200;

	//idle right 2
	idleR2.frames.PushBack({ 204, 139, 32, 32 });

	//idle left 2
	idleL2.frames.PushBack({ 204, 174, 32, 32 });
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics2 = App->textures->Load("pang_player.png"); // arcade version
	return ret;
}

// Update: Player2
update_status ModulePlayer2::Update()
{
	Animation* current_animation2 = NULL;

	int speed = 2;

	current_animation2 = &idleR2;

	/*
	if (last_animation2 == &right2 || last_animation2 == NULL)
	{
		current_animation2 = &idleR2;
	}

	if (last_animation2 == &left2)
	{
		current_animation2 = &idleL2;
	}
	*/

	// Draw everything --------------------------------------
	SDL_Rect r2 = current_animation2->GetCurrentFrame();

	App->renderer->Blit(graphics2, position2.x, position2.y - r2.h, &r2);

	return UPDATE_CONTINUE;
}