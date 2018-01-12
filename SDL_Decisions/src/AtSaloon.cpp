#include "AtSaloon.h"


void AtSaloon::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro al bar\n";
	agent->timeCounter = 0;
	Vector2D posSaloon = {100, 520};
	scene->path.points = Aestrella::search(scene->findInGraph(agent->getPosition()), scene->pix2cell(posSaloon));
}

void AtSaloon::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << "estoy en el bar\n";
	agent->timeCounter += scene->deltaTime;

	if (agent->thirsty >= 10) { //10 es max thirsty
		agent->changeClass<Mining>();
	}
	else {
		if (agent->timeCounter >= 1) {
			agent->thirsty++;
			agent->timeCounter = 0;
		}
	}
}

void AtSaloon::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout << "me voy del bar";
}
