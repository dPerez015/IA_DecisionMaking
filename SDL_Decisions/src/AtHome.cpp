#include "AtHome.h"

void AtHome::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro a casa\n";
}

void AtHome::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << "Estoy en casa \n";
	
}

void AtHome::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout << "Salgo de casa\n";
}
