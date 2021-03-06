#include "AtSaloon.h"


void AtSaloon::onEnter(Agent* agent, ScenePlanning* scene) {
	//std::cout << "Entro al bar\n";
	agent->state = 1;
	agent->timeCounter = 0;
	Vector2D posSaloon = { 5, 20 }; //in cells
	scene->path.points = Aestrella::search(scene->findInGraph(agent->getPosition()), posSaloon);

}

void AtSaloon::Update(Agent* agent, ScenePlanning* scene) {
	//std::cout << "estoy en el bar\n";
	if (scene->path.points.size() == 0) {
	
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
}

void AtSaloon::onExit(Agent* agent, ScenePlanning* scene) {
	//std::cout << "me voy del bar";
}
