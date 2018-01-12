#include "AtBank.h"

void AtBank::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro al banco\n";
	agent->timeCounter = 0;
}

void AtBank::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << " Estoy en el banco \n";
	agent->timeCounter += scene->deltaTime;

	if (agent->gold == 0) {
		if (agent->wealthy < agent->maxWealthy)
			agent->changeClass<Mining>();
		else 
			agent->changeClass<AtHome>();
		
	}
	else{
		if (agent->timeCounter >= 1) {
			agent->gold--;
			agent->wealthy += agent->gold;
			agent->timeCounter = 0;
		}
	}
}

void AtBank::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout << "salgo del banco";
}
