#include "Globals.h"
#include "Application.h"
#include "ModuleBalloons.h"

ModuleBalloons::ModuleBalloons(Application* app) : Module(app)
{
	// Balloons Sprites -------------------------------------
	graphics = NULL;

	position_ball.x = 10;
	position_ball.y = 50;

	//idle_ball right
	idle_ball.frames.PushBack({ 1, 1, 48, 40 });

}

ModuleBalloons::~ModuleBalloons()
{}

// Load assets
bool ModuleBalloons::Start()
{
	LOG("Loading balloons textures");
	bool ret = true;
	graphics = App->textures->Load("Balloons_Allin.png"); // arcade version
	return ret;
}

// Update: Balloons
update_status ModuleBalloons::Update()
{
	Animation* current_animation_ball = NULL;

	int speed = 2;

	current_animation_ball = &idle_ball;

	// Draw everything --------------------------------------
	SDL_Rect rb = current_animation_ball->GetCurrentFrame();

	App->renderer->Blit(graphics, position_ball.x, position_ball.y - rb.h, &rb);

	return UPDATE_CONTINUE;
}