#include "AtHome.h"

void AtHome::onEnter(Agent* agent, ScenePlanning* scene) {
	agent->state = 3;
	agent->timeCounter = 0;
	agent->wealthy = 0;
	Vector2D posHome = {20, 20};
	scene->path.points = Aestrella::search(scene->findInGraph(agent->getPosition()), posHome);
}

void AtHome::Update(Agent* agent, ScenePlanning* scene) {
	if (scene->path.points.size() == 0) {
		agent->timeCounter += scene->deltaTime;

		if (agent->timeCounter >= agent->restingTime)
			agent->changeClass<Mining>();
	}
	
}

void AtHome::onExit(Agent* agent, ScenePlanning* scene) {
}
