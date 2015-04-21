#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	collider = NULL;
	current_animation = NULL;
	graphics = NULL;

	//idle right
	idleR.frames.PushBack({ 11, 135, 32, 32 });

	//idle left
	idleL.frames.PushBack({ 45, 168, 32, 32 });

	// walk to the right animation (arcade sprite sheet)
	right.frames.PushBack({ 11, 2, 32, 32 });
	right.frames.PushBack({ 45, 2, 32, 32 });
	right.frames.PushBack({ 79, 2, 32, 32 });
	right.frames.PushBack({ 113, 2, 32, 32 });
	right.frames.PushBack({ 147, 2, 32, 32 });
	right.speed = 0.3f;

	// walk to the left animation (arcade sprite sheet)
	left.frames.PushBack({ 11, 35, 32, 32 });
	left.frames.PushBack({ 45, 35, 32, 32 });
	left.frames.PushBack({ 79, 35, 32, 32 });
	left.frames.PushBack({ 113, 35, 32, 32 });
	left.frames.PushBack({ 147, 35, 32, 32 });
	left.speed = 0.3f;

	//going up/down stairs
	stairs.frames.PushBack({ 79, 68, 32, 32 });
	stairs.frames.PushBack({ 45, 102, 32, 32 });
	stairs.frames.PushBack({ 113, 68, 32, 32 });
	stairs.frames.PushBack({ 45, 102, 32, 32 });
	stairs.speed = 0.3f;

	//shooting right
	shootR.frames.PushBack({ 45, 135, 32, 32 });

	//shooting left
	shootL.frames.PushBack({ 11, 168, 32, 32 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Sprites/pang_player.png");

	position.x = 152;
	position.y = 168;

	// TODO 2: Afegir collider al jugador
	collider = App->collision->AddCollider({ position.x, position.y, 32, 32 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	current_animation = NULL;

	if (last_animation == &right || last_animation == NULL)
	{
		current_animation = &idleR;
	}

	if (last_animation == &left)
	{
		current_animation = &idleL;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = &right;

		position.x += speed;
		
		last_animation = &right;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &left;
		
		position.x -= speed;
		
		last_animation = &left;
	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		if (last_animation == &right)
		{
			current_animation = &shootR;
			App->harpoons->AddHarpoon(App->harpoons->shot, position.x + 10, position.y, COLLIDER_PLAYER_SHOT);
		}

		if (last_animation == &left)
		{
			current_animation = &shootL;
			App->harpoons->AddHarpoon(App->harpoons->shot, position.x + 7, position.y, COLLIDER_PLAYER_SHOT);
		}
	}

	// TODO 3: Actualitzar la posicio del collider del jugador perque el segueixi
	collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 4: Detectar colisio del jugador y retornar a la pantalla de inici

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_BALLOON)
	{
		App->fade->FadeToBlack(App->scene_fuji, App->scene_intro, 0.0f);
	}

	if (c2->type == COLLIDER_WALL_HORITZONTAL && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y = position.y;
	}

	if (c2->type == COLLIDER_WALL_HORITZONTAL && App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y = position.y;
	}

	if (c2->type == COLLIDER_WALL_VERTICAL && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) //TODO: s'hauria de parar :S
	{
		position.x = position.x - 2;
	}

	if (c2->type == COLLIDER_WALL_VERTICAL && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) //TODO: s'hauria de parar :S
	{
		position.x = position.x + 2;
	}

	if (c2->type == COLLIDER_LADDER && App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)  //TODO: que faci l'animacio de forma correcta
	{
		current_animation = &stairs;
		position.y -= speed;
	}

	if (c2->type == COLLIDER_LADDER && App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) //TODO: que faci l'animacio de forma correcta
	{
		current_animation = &stairs;
		position.y += speed;
	}
}