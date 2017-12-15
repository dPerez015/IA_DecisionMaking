#include "Mining.h"

void Mining::onEnter(Agent* agent, ScenePlanning* scene) {
	std::cout << "Entro en la mina\n";
}

void Mining::Update(Agent* agent, ScenePlanning* scene) {
	std::cout << "Minando\n";
}

void Mining::onExit(Agent* agent, ScenePlanning* scene) {
	std::cout<<"Salgo de la mina\n";
}
