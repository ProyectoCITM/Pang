#include "Globals.h"
#include "Application.h"
#include "ModuleFruit.h"

ModuleFruit::ModuleFruit(Application* app) : Module(app)
{
	graphics = NULL;

	// Cherry
	cherry.x = 0;
	cherry.y = 0;
	cherry.w = 12;
	cherry.h = 12;

	// Cake
	cake.x = 14;
	cake.y = 0;
	cake.w = 16;
	cake.h = 12;

}

ModuleFruit::~ModuleFruit()
{}

// Load assets
bool ModuleFruit::Start()
{
	LOG("Loading fruit assets");
	bool ret = true;
	graphics = App->textures->Load("pang_fruit.png");
	return ret;
}

// Update: draw Fruits
update_status ModuleFruit::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 192, 30, &cherry, NULL); // cherry
	App->renderer->Blit(graphics, 192, 60, &cake, NULL); // cake
	return UPDATE_CONTINUE;
}