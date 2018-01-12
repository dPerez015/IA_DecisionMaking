#include "AtHome.h"

void AtHome::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro a casa\n";
	agent->timeCounter = 0;
	agent->wealthy = 0;
	Vector2D posHome = {550, 520};
	scene->path.points = Aestrella::search(scene->findInGraph(agent->getPosition()), scene->pix2cell(posHome));
}

void AtHome::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << "Estoy en casa \n";
	agent->timeCounter += scene->deltaTime;

	if (agent->rested == agent->maxRested)
		agent->changeClass<Mining>();
	else {
		if (agent->timeCounter >= 1) {
			agent->rested++;
			agent->timeCounter = 0;
		}
	}
	
}

void AtHome::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout << "Salgo de casa\n";
}
