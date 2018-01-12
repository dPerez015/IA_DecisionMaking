#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include "SteeringBehavior.h"
#include "Mining.h"
#include "AtHome.h"
#include "AtSaloon.h"
#include "AtBank.h"
#include "ScenePlanning.h"
#include "Action.h"

class ScenePlanning;

class Agent
{
	friend class SteeringBehavior;

private:
	SteeringBehavior *steering_behavior;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Color color;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	void(*currentUpdate)(Agent*,ScenePlanning*);
	void(*currentOnExit)(Agent*,ScenePlanning*);
	ScenePlanning* scene;
	
public:
	//variables de l'exercici 1
	int thirsty = 10;
	int minThirsty = 4;
	int gold = 0;
	int maxGold = 3;
	int wealthy = 0;
	int maxWealthy = 10;
	float rested = 0;
	float maxRested = 5000;
	float timeCounter =0;

	//GOAP
	std::vector<Action*> posibleActions;
	void addAction(Action*);

	Agent(ScenePlanning*);
	Agent();
	~Agent();
	SteeringBehavior *Behavior();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setMass(float mass);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void update(Vector2D steering_force, float dtime, SDL_Event *event);
	static void voidUpdate(Agent*, ScenePlanning*);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	
	template <class T>
	void changeClass() {
		if (currentUpdate != T::Update) {
			currentOnExit(this,scene);
			currentUpdate = T::Update;
			currentOnExit = T::onExit;
			T::onEnter(this,scene);
		}
	}

};
