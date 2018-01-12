#include "Mining.h"

void Mining::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro en la mina\n";
	agent->timeCounter = 0;
	//CREA MONEDA??
}

void Mining::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << "Minando\n";
	agent->timeCounter += scene->deltaTime;

	if (agent->thirsty <= agent->minThirsty) {
		agent->changeClass<AtSaloon>();
	}
	else if (agent->gold >= agent->maxGold) {
		agent->changeClass<AtBank>();
	}
	else {
		//PATHFINDING CAP A LA MONEDA
		//if(scene->path->points)

		if (agent->timeCounter >= 5) { //5 segons
			agent->thirsty -= 1;
			agent->timeCounter = 0;
		}
	}

	
}

void Mining::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout<<"Salgo de la mina\n";
	//ELIMINAR EL PATH
}
