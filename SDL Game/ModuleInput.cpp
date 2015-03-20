#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

ModuleInput::ModuleInput(Application* app) : Module(app)
{
	keyboard = NULL;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	//recull imputs des de l'última vegada que s'ha cridat
	SDL_PumpEvents(); 

	keyboard = SDL_GetKeyboardState(NULL);

	// TODO: que al apretar ESCAPE la aplicacio acabi

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}