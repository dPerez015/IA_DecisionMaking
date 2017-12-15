#include "AtSaloon.h"


void AtSaloon::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro al bar\n";
}

void AtSaloon::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << "estoy en el bar\n";
}

void AtSaloon::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout << "me voy del bar"
}
