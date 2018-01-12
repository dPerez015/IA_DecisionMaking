#include "Agent.h"
#include <SDL_ttf.h>

using namespace std;

Agent::Agent(ScenePlanning* s) : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
	             mass(0.1f),
	             max_force(150),
	             max_velocity(200),
	             orientation(0),
	             color({ 255,255,255,255 }),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false)
{
	steering_behavior = new SteeringBehavior;
	scene = s;
	Mining::onEnter(this, scene);
	currentOnExit = Mining::onExit;
	currentUpdate = Mining::Update;
	//printText = false;
}
Agent::Agent() : sprite_texture(0),
				position(Vector2D(100, 100)),
				target(Vector2D(1000, 100)),
				velocity(Vector2D(0, 0)),
				mass(0.1f),
				max_force(150),
				max_velocity(200),
				orientation(0),
				color({ 255,255,255,255 }),
				sprite_num_frames(0),
				sprite_w(0),
				sprite_h(0),
				draw_sprite(false) 
{
	steering_behavior = new SteeringBehavior;
	//scene = s;
	
	currentOnExit = voidUpdate;
	currentUpdate = voidUpdate;

}
void Agent::voidUpdate(Agent*, ScenePlanning*) {

}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behavior)
		delete (steering_behavior);
}

SteeringBehavior * Agent::Behavior()
{
	return steering_behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::setMass(float _mass)
{
	mass = _mass;
}

void Agent::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color = { r, g, b, a };
}

void Agent::update(Vector2D steering_force, float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		else if (event->key.keysym.scancode == SDL_SCANCODE_Z)
			changeClass<AtHome>();
		else if (event->key.keysym.scancode == SDL_SCANCODE_X)
			changeClass<AtSaloon>();
		else if (event->key.keysym.scancode == SDL_SCANCODE_V)
			changeClass<AtBank>();
		else if (event->key.keysym.scancode == SDL_SCANCODE_C)
			changeClass<Mining>();

		break;
	default:
		break;
	}


	Vector2D acceleration = steering_force / mass;
	velocity = velocity + acceleration * dtime;
	velocity = velocity.Truncate(max_velocity);

	position = position + velocity * dtime;

	currentUpdate(this,scene);
	// Update orientation
	if (velocity.Length()>0)
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);


	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::draw()
{

	//text test
	TTF_Font* Sans = TTF_OpenFont("../res/arial.ttf", 24);
	if (Sans == NULL) cout << "Arial not founs" << endl;
	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Ferran puta", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 20;  //controls the rect's x coordinate 
	Message_rect.y = 500; // controls the rect's y coordinte
	Message_rect.w = 1000; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);


	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (max_velocity)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}
