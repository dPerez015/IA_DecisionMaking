#include "Mining.h"

void Mining::onEnter(Agent* agent, ScenePlanning* scene) {
	//std::cout << "Entro en la mina\n";
	agent->state = 0;
	agent->timeCounter = 0;
	//CREA MONEDA
	scene->coinPosition = Vector2D((float)(rand() % ((SRC_WIDTH / CELL_SIZE) - 5)) + 4, (float)(rand() % 4) + 1);
	while (((Vector2D::Distance(scene->coinPosition, scene->pix2cell(agent->getPosition()))<3)))
		scene->coinPosition = Vector2D((float)(rand() % ((SRC_WIDTH / CELL_SIZE) - 5)) + 4, (float)(rand() % 4) + 1);
}

void Mining::Update(Agent* agent, ScenePlanning* scene) {
	
	agent->timeCounter += scene->deltaTime;

	if (agent->thirsty <= agent->minThirsty) {
		agent->changeClass<AtSaloon>();
	}
	else if (agent->gold >= agent->maxGold) {
		agent->changeClass<AtBank>();
	}
	else {
		//PATHFINDING CAP A LA MONEDA
		if (scene->path.points.size() == 0) {
			scene->path.points = Aestrella::search(scene->findInGraph(agent->getPosition()),scene->coinPosition);
		}
		
		if (agent->timeCounter >= 5) { //5 segons
			agent->thirsty -= 1;
			agent->timeCounter = 0;
		}
	}

	
}

void Mining::onExit(Agent* agent, ScenePlanning* scene) {
	//std::cout<<"Salgo de la mina\n";
	//ELIMINAR EL PATH
	scene->path.points.clear();
	scene->currentTargetIndex = -1;
	agent->setVelocity(Vector2D(0, 0));
	//eliminar moneda
	scene->coinPosition = Vector2D(-1, -1);
}
