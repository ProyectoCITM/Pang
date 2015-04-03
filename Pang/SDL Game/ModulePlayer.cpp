#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app) : Module(app)
{
	graphics = NULL;

	position.x = 160;
	position.y = 200;

	//idle right
	idleR.frames.PushBack({ 11, 139, 32, 32 });

	//idle left
	idleL.frames.PushBack({ 45, 174, 32, 32 });

	// walk to the right animation (arcade sprite sheet)
	right.frames.PushBack({ 11, 2, 32, 32 });
	right.frames.PushBack({ 45, 2, 32, 32 });
	right.frames.PushBack({ 79, 2, 32, 32 });
	right.frames.PushBack({ 113, 2, 32, 32 });
	right.frames.PushBack({ 147, 2, 32, 32 });
	right.speed = 0.3f;

	// walk to the left animation (arcade sprite sheet)
	left.frames.PushBack({ 6, 35, 32, 32 });
	left.frames.PushBack({ 40, 35, 32, 32 });
	left.frames.PushBack({ 74, 35, 32, 32 });
	left.frames.PushBack({ 108, 35, 32, 32 });
	left.frames.PushBack({ 142, 35, 32, 32 });
	left.speed = 0.3f;

	//going up/down stairs
	stairs.frames.PushBack({ 78, 69, 32, 32 });
	stairs.frames.PushBack({ 45, 103, 32, 32 });
	stairs.frames.PushBack({ 112, 69, 32, 32 });
	stairs.frames.PushBack({ 45, 103, 32, 32 });
	stairs.speed = 0.3f;

	//shooting right
	shootR.frames.PushBack({ 45, 139, 32, 32 });

	//shooting left
	shootL.frames.PushBack({ 11, 173, 32, 32 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("pang_player.png"); // arcade version
	return ret;
}

// Update: Player1
update_status ModulePlayer::Update()
{
	Animation* current_animation = NULL;
	
	int speed = 1;

	if (last_animation == &right || last_animation == NULL)
	{
		current_animation = &idleR;
	}

	if (last_animation == &left)
	{
		current_animation = &idleL;
	}
	
	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &right;
		position.x += speed;

		last_animation = &right;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &left;
		position.x -= speed;

		last_animation = &left;
	}

	if (App->input->keyboard[SDL_SCANCODE_B] == 1)
	{
		if (last_animation == &right)
		{
			current_animation = &shootR;
		}

		if (last_animation == &left)
		{
			current_animation = &shootL;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &stairs;
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &stairs;
		position.y += speed;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}