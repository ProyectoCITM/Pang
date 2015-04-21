#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

public:
	
	SDL_Texture* graphics;
	Collider* collider;
	Animation* last_animation = &right;
	Animation* current_animation;
	Animation idleR;
	Animation idleL;
	Animation right;
	Animation left;
	Animation stairs;
	Animation shootR;
	Animation shootL;
	p2Point<int> position;
	int speed = 2;
};