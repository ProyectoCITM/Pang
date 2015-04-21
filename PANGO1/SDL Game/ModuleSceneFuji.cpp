#include "Globals.h"
#include "Application.h"
#include "ModuleSceneFuji.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneFuji::ModuleSceneFuji(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// SceneFuji 1
	background.x = 8;
	background.y = 8;
	background.w = 384;
	background.h = 208;

}

ModuleSceneFuji::~ModuleSceneFuji()
{}

// Load assets
bool ModuleSceneFuji::Start()
{
	LOG("Loading SceneFuji assets");

	graphics = App->textures->Load("Sprites/pang_background.png");

	App->collision->Enable(); // enable before player
	App->audio->Enable();
	App->balloon->Enable();
	App->player->Enable();

	App->audio->PlayMusic("Music/01a - Mt. Fuji (Arcade).wav", 0.0f);
	
	App->balloon->AddBalloon(App->balloon->red_big_ball, 200, 26, COLLIDER_BALLOON);
	//App->balloon->AddBalloon(App->balloon->red_big_ball, 26, 26, COLLIDER_BALLOON);

	App->collision->AddCollider({ 0, 0, 384, 8 }, COLLIDER_WALL_HORITZONTAL);
	App->collision->AddCollider({ 0, 8, 8, 192 }, COLLIDER_WALL_VERTICAL);
	App->collision->AddCollider({ 0, 200, 384, 8 }, COLLIDER_WALL_HORITZONTAL);
	App->collision->AddCollider({ 376, 8, 8, 192 }, COLLIDER_WALL_VERTICAL);

	return true;
}

bool ModuleSceneFuji::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->balloon->Disable();
	App->collision->Disable();
	
	return true;
}

// Update: draw SceneFuji
update_status ModuleSceneFuji::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, NULL); // SceneFuji
	return UPDATE_CONTINUE;
}