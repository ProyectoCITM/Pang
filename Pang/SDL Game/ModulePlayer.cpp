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
	shootL.frames.PushBack({ 11, 174, 32, 32 });


	// Player 2 Sprites -------------------------------------
	position2.x = 192;
	position2.y = 200;

	//idle right 2
	idleR2.frames.PushBack({ 204, 139, 32, 32 });

	//idle left 2
	idleL2.frames.PushBack({ 238, 174, 32, 32 });

	// walk to the right 2 animation (arcade sprite sheet)
	right2.frames.PushBack({ 206, 2, 32, 32 });
	right2.frames.PushBack({ 240, 2, 32, 32 });
	right2.frames.PushBack({ 274, 2, 32, 32 });
	right2.frames.PushBack({ 308, 2, 32, 32 });
	right2.frames.PushBack({ 342, 2, 32, 32 });
	right2.speed = 0.3f;

	// walk to the left 2 animation (arcade sprite sheet)
	left2.frames.PushBack({ 203, 35, 32, 32 });
	left2.frames.PushBack({ 237, 35, 32, 32 });
	left2.frames.PushBack({ 271, 35, 32, 32 });
	left2.frames.PushBack({ 305, 35, 32, 32 });
	left2.frames.PushBack({ 339, 35, 32, 32 });
	left2.speed = 0.3f;

	//going up/down stairs 2
	stairs2.frames.PushBack({ 275, 69, 32, 32 });
	stairs2.frames.PushBack({ 242, 103, 32, 32 });
	stairs2.frames.PushBack({ 309, 69, 32, 32 });
	stairs2.frames.PushBack({ 242, 103, 32, 32 });
	stairs2.speed = 0.3f;

	//shooting right 2
	shootR2.frames.PushBack({ 238, 139, 32, 32 });

	//shooting left 2
	shootL2.frames.PushBack({ 204, 174, 32, 32 });
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

// Update: Player1 and Player2
update_status ModulePlayer::Update()
{
	Animation* current_animation = NULL;

	int speed = 2;

	if (last_animation == &right || last_animation == NULL)
	{
		current_animation = &idleR;
	}

	if (last_animation == &left)
	{
		current_animation = &idleL;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &right;
		// limits right
		if (position.x >= 346)
		{
			position.x = 346;
		}
		else
		{
			position.x += speed;
		}
		last_animation = &right;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &left;
		// limits left
		if (position.x <= 6)
		{
			position.x = 6;
		}
		else
		{
			position.x -= speed;
		}
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
		// limits up
		if (position.y <= 40)
		{
			position.y = 40;
		}
		else
		{
			position.y -= speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &stairs;
		// limits down
		if (position.y >= 200)
		{
			position.y = 200;
		}
		else
		{
			position.y += speed;
		}
	}


	// Player 2 Controls ------------------------------------
	Animation* current_animation2 = NULL;

	if (last_animation2 == &right2 || last_animation2 == NULL)
	{
		current_animation2 = &idleR2;
	}

	if (last_animation2 == &left2)
	{
		current_animation2 = &idleL2;
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
	{
		current_animation2 = &right2;
		// limits right
		if (position2.x >= 346)
		{
			position2.x = 346;
		}
		else
		{
			position2.x += speed;
		}
		last_animation2 = &right2;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
	{
		current_animation2 = &left2;
		// limits left
		if (position2.x <= 6)
		{
			position2.x = 6;
		}
		else
		{
			position2.x -= speed;
		}
		last_animation2 = &left2;
	}

	if (App->input->keyboard[SDL_SCANCODE_L] == 1)
	{
		if (last_animation2 == &right2 || last_animation2 == &idleR2)
		{
			current_animation2 = &shootR2;
		}

		if (last_animation2 == &left2 || last_animation2 == &idleL2)
		{
			current_animation2 = &shootL2;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == 1)
	{
		current_animation2 = &stairs2;
		// limits up
		if (position2.y <= 40)
		{
			position2.y = 40;
		}
		else
		{
			position2.y -= speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	{
		current_animation2 = &stairs2;
		// limits down
		if (position2.y >= 200)
		{
			position2.y = 200;
		}
		else
		{
			position2.y += speed;
		}
	}


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);

	// Draw everything 2 ------------------------------------
	SDL_Rect r2 = current_animation2->GetCurrentFrame();

	App->renderer->Blit(graphics, position2.x, position2.y - r2.h, &r2);

	return UPDATE_CONTINUE;
}