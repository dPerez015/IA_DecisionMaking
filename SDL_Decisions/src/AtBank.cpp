#include "AtBank.h"

void AtBank::onEnter(Agent* agent, ScenePlanning* scene) {
	agent->state = 2;
	agent->timeCounter = 0;
	Vector2D posBank = { 32, 20 };	
	scene->path.points = Aestrella::search(scene->findInGraph(agent->getPosition()), posBank);
}

void AtBank::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << agent->wealthy << std::endl;
	if (scene->path.points.size() == 0) {
		agent->timeCounter += scene->deltaTime;

		if (agent->gold == 0) {
			if (agent->wealthy < agent->maxWealthy)
				agent->changeClass<Mining>();
			else
				agent->changeClass<AtHome>();

		}
		else {
			if (agent->timeCounter >= 1) {
				agent->gold--;
				agent->wealthy ++;
				agent->timeCounter = 0;
			}
		}
	}
}

void AtBank::onExit(Agent* agent, ScenePlanning* scene) {
}
