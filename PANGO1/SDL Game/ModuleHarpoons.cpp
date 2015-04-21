#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleHarpoons.h"

ModuleHarpoons::ModuleHarpoons(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleHarpoons::~ModuleHarpoons()
{}

// Load assets
bool ModuleHarpoons::Start()
{
	LOG("Loading Harpoons");
	graphics = App->textures->Load("Sprites/harpoons_allin.png");

	// shot Harpoon
	shot.fx = App->audio->LoadFx("Sprites/harpoons_allin.png");
	shot.anim.frames.PushBack({1, 1, 17, 32});
	shot.speed.y = 3;
	shot.anim.speed = 0.05f;
	/*
	// Tail01
	shot.tail01.x = 1;
	shot.tail01.y = 33;
	shot.tail01.w = 17;
	shot.tail01.h = 4;

	// Tail02
	shot.tail02.x = 1;
	shot.tail02.y = 37;
	shot.tail02.w = 17;
	shot.tail02.h = 4;

	// Tail03
	shot.tail03.x = 1;
	shot.tail03.y = 41;
	shot.tail03.w = 17;
	shot.tail03.h = 4;

	// Tail04
	shot.tail04.x = 1;
	shot.tail04.y = 45;
	shot.tail04.w = 17;
	shot.tail04.h = 4;
	*/
	return true;
}

// Unload assets
bool ModuleHarpoons::CleanUp()
{
	LOG("Unloading Harpoons");
	App->textures->Unload(graphics);
	active.clear();
	return true;
}

// Update: draw background
update_status ModuleHarpoons::Update()
{
	p2List_item<Harpoon*>* tmp = active.getFirst();
	p2List_item<Harpoon*>* tmp_next = active.getFirst();

	

	while(tmp != NULL)
	{
		Harpoon* p = tmp->data;
		tmp_next = tmp->next;

		if(p->Update() == false)
		{
			delete p;
			active.del(tmp);
		}
		else
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	App->renderer->Blit(graphics, shot.position.x, 82, &shot.tail01, NULL);
	App->renderer->Blit(graphics, shot.position.x, 86, &shot.tail02, NULL);
	App->renderer->Blit(graphics, shot.position.x, 90, &shot.tail03, NULL);
	App->renderer->Blit(graphics, shot.position.x, 94, &shot.tail04, NULL);
	
	return UPDATE_CONTINUE;
}

// Always destroy Harpoons that collide
void ModuleHarpoons::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un shot collisini sorti una explosio
  	p2List_item<Harpoon*>* tmp = active.getFirst();

	//App->renderer->Blit(graphics, App->Harpoons->position.x, App->Harpoons->position.y, NULL);

	while(tmp != NULL)
	{
		if(tmp->data->collider == c1 )
		{	
			delete tmp->data;
			active.del(tmp);
			break;
		}

		tmp = tmp->next;
	}
}

void ModuleHarpoons::AddHarpoon(const Harpoon& harpoon, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	if (active.count() < 1)
	{
		Harpoon* p = new Harpoon(harpoon);

		p->position.x = x;
		p->position.y = y;

		if (collider_type != COLLIDER_NONE)
		{
			p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
		}

		active.add(p);
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Harpoon::Harpoon() : fx(0), counting(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Harpoon::Harpoon(const Harpoon& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
}

Harpoon::~Harpoon()
{
	if(collider)
		collider->to_delete = true;
}

bool Harpoon::Update()
{
	bool ret = true;

	position.y -= speed.y;

	counting += speed.y;

	if(collider != NULL)
	{
		//SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x + 8, position.y, 1, 32 + counting};
	}
	return ret;
}