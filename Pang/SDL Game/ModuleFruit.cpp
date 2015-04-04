#include "Globals.h"
#include "Application.h"
#include "ModuleFruit.h"

ModuleFruit::ModuleFruit(Application* app) : Module(app)
{
	graphics = NULL;

	position_fruit.x = 182;
	position_fruit.y = 30;

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
	//SDL_Rect current_rect = NULL;

	if (position_fruit.y < 188)
	{
		position_fruit.y += 1;
	}

	App->renderer->Blit(graphics, position_fruit.x, position_fruit.y, &cherry, NULL);

	return UPDATE_CONTINUE;
}