#include "Globals.h"
#include "Application.h"
#include "ModuleBalloon.h"
#include <math.h>


ModuleBalloon::ModuleBalloon(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleBalloon::~ModuleBalloon()
{}

// Load assets
bool ModuleBalloon::Start()
{
	LOG("Loading Balloon");
	graphics = App->textures->Load("Sprites/balloons_allin.png");

	//idle_ball
	red_big_ball.anim.frames.PushBack({ 1, 1, 48, 40 });
	red_big_ball.speed.x = 1;
	red_big_ball.h = 140;

	// red_big_explosion Barpoon
	red_big_explosion.fx = App->audio->LoadFx("Sprites/balloons_allin.png");
	red_big_explosion.anim.frames.PushBack({ 133, 3, 48, 40 });
	red_big_explosion.anim.frames.PushBack({ 183, 3, 48, 40 });
	red_big_explosion.anim.frames.PushBack({ 233, 3, 48, 40 });
	red_big_explosion.anim.frames.PushBack({ 283, 2, 48, 40 });
	red_big_explosion.speed.y = 0;
	red_big_explosion.anim.speed = 0.15f;
	
	return true;
}

// Unload assets
bool ModuleBalloon::CleanUp()
{
	LOG("Unloading Balloon");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleBalloon::Update()
{
	p2List_item<Balloon*>* tmp = active.getFirst();
	p2List_item<Balloon*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Balloon* b = tmp->data;
		tmp_next = tmp->next;

		if (b->Update() == false)
		{
			delete b;
			active.del(tmp);
		}
		else
		{
			App->renderer->Blit(graphics, b->position.x, b->position.y, &(b->anim.GetCurrentFrame()));
			if (b->fx_explosion == false)
			{
				b->fx_explosion = true;
				App->audio->PlayFx(b->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy Balloon that collide
void ModuleBalloon::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un shot collisini sorti una explosio
	p2List_item<Balloon*>* tmp = active.getFirst();

	//App->renderer->Blit(graphics, App->Balloon->position.x, App->Balloon->position.y, NULL);

	if (c2->type == COLLIDER_WALL_HORITZONTAL)
	{
		red_big_ball.speed.x = red_big_ball.speed.x * -1;
	}
	/*
	if (c2->type == COLLIDER_WALL_VERTICAL && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) //TODO: s'hauria de parar :S
	{
		b->position.x = position.x - 2;
	}
	*/
	while (tmp != NULL)
	{
		if (tmp->data->collider == c1)
		{
			delete tmp->data;
			active.del(tmp);
			break;
		}

		tmp = tmp->next;
	}

	if (active.getFirst() == NULL)
		App->fade->FadeToBlack(App->scene_fuji, App->scene_intro, 0.0f);
}

void ModuleBalloon::AddBalloon(const Balloon& balloon, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Balloon* b = new Balloon(balloon);
	
	b->position.x = x;
	b->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		b->collider = App->collision->AddCollider({ b->position.x, b->position.y, 0, 0 }, collider_type, this);
	}

	active.add(b);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Balloon::Balloon() : fx(0), fx_explosion(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Balloon::Balloon(const Balloon& p) : anim(p.anim), position(p.position), speed(p.speed), fx_explosion(false), collider(p.collider)
{
	fx = p.fx;
}

Balloon::~Balloon()
{
	if (collider)
		collider->to_delete = true;
}

bool Balloon::Update()
{
	bool ret = true;

	if (180 <= alpha <= 360)
	{
		if (alpha == 360)
		{
			alpha = 180;
		}
		alpha += 0.025;
	}
	
	position.x += speed.x;
	//position.y = (165 + (abs(h * sin(alpha)) * -1));     Crec que el problema està en el valors!
	

	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}