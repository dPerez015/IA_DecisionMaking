#include "AtBank.h"

void AtBank::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro al banco\n";
}

void AtBank::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << " Estoy en el banco \n";
}

void AtBank::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout << "salgo del banco";
}
