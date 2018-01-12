#include "SceneGoap.h"

using namespace std;

SceneGoap::SceneGoap()
{
	draw_grid = true;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent();
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	


	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!isValidCell(rand_cell)) 
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3)) 
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	
	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;

	Aestrella::init(num_cell_x,num_cell_y);

	//Goap
	//worldStateSetup
	worldState.add(WorldStateVariables::AgentAlive, true);
	
	worldState.add(WorldStateVariables::AgentHasBomb, false);

	worldState.add(WorldStateVariables::AgentArmed, true);

	worldState.add(WorldStateVariables::EnemyAlive, true);

	//actions Setup
	setUpPossibleActions();
	
	agents[0]->addAction(&posibleActions.find("Explorar")->second);
	agents[0]->addAction(&posibleActions.find("Acercarse")->second);
	agents[0]->addAction(&posibleActions.find("Apuntar")->second);
	agents[0]->addAction(&posibleActions.find("Recargar")->second);
	agents[0]->addAction(&posibleActions.find("Disparar")->second);
	agents[0]->addAction(&posibleActions.find("Lanzar")->second);
	agents[0]->addAction(&posibleActions.find("Detonar")->second);
	agents[0]->addAction(&posibleActions.find("Alejarse")->second);
	agents[0]->addAction(&posibleActions.find("GetBomb")->second);

	bool canExplore = worldState.checkAction(&posibleActions.find("Explorar")->second);
	bool canThrowGranade = worldState.checkAction(&posibleActions.find("Lanzar")->second);
	bool canGetGranade = worldState.checkAction(&posibleActions.find("GetBomb")->second);
	worldState.applyAction(&posibleActions.find("GetBomb")->second);
	canThrowGranade = worldState.checkAction(&posibleActions.find("Lanzar")->second);
	worldState.applyAction(&posibleActions.find("Acercarse")->second);
	worldState.applyAction(&posibleActions.find("Explorar")->second);
	canThrowGranade = worldState.checkAction(&posibleActions.find("Lanzar")->second);
	/*
	worldState.applyAction(&posibleActions.find("GetBomb")->second);
	worldState.applyAction(&posibleActions.find("Disparar")->second);
	
	WorldState otherState = worldState;

	otherState.add(WorldStateVariables::EnemyAlive, 1);
	bool rawCheck = worldState.checkEquals(otherState);
	bool maskedCheck = worldState.checkEqualsMasked(otherState);
	*/
	int i = 0;
}

void SceneGoap::setUpPossibleActions() {
	//Explorar
	Action action;
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	action.cost = 3;
	action.definition = "Explorar\n";
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.reaction.add(WorldStateVariables::EnemyVisible, true);

	posibleActions.emplace("Explorar", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//Aproparse a un enemic
	action.cost = 1;
	action.definition = "Acercarse al enemigo\n";
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.preConditions.add(WorldStateVariables::EnemyVisible, true);
	action.reaction.add(WorldStateVariables::EnemyNear, true);

	posibleActions.emplace("Acercarse", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//Apuntar
	action.cost = 1;
	action.definition = "Apuntar\n";
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.preConditions.add(WorldStateVariables::AgentArmed, true);
	action.preConditions.add(WorldStateVariables::EnemyVisible, true);
	action.reaction.add(WorldStateVariables::EnemyAligned, true);
	
	posibleActions.emplace("Apuntar", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//cargarArma
	action.cost = 1;
	action.definition = "Recargar\n";
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.preConditions.add(WorldStateVariables::AgentArmed, true);
	action.preConditions.add(WorldStateVariables::EnemyNear, false);
	action.reaction.add(WorldStateVariables::WeaponCharged, true);
	action.reaction.add(WorldStateVariables::EnemyAligned, false);

	posibleActions.emplace("Recargar", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//disparar
	action.cost = 1;
	action.definition = "Disparar\n";
	action.preConditions.add(WorldStateVariables::EnemyAlive, true);
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.preConditions.add(WorldStateVariables::AgentArmed, true);
	action.preConditions.add(WorldStateVariables::EnemyVisible, true);
	action.preConditions.add(WorldStateVariables::EnemyAligned, true);
	action.reaction.add(WorldStateVariables::EnemyAlive, false);
	action.reaction.add(WorldStateVariables::WeaponCharged, false);
	
	posibleActions.emplace("Disparar", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//llançar granada
	action.cost = 2;
	action.definition = "Lanzar explosivos\n";
	action.preConditions.add(WorldStateVariables::EnemyAlive, true);
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.preConditions.add(WorldStateVariables::AgentHasBomb, true);
	action.preConditions.add(WorldStateVariables::EnemyVisible, true);
	action.preConditions.add(WorldStateVariables::EnemyNear, true);
	action.reaction.add(WorldStateVariables::BombNearEnemy, true);
	action.reaction.add(WorldStateVariables::AgentHasBomb, false);

	posibleActions.emplace("Lanzar", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//detonar granada
	action.cost = 1;
	action.definition = "Detonar explosivos\n";
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.preConditions.add(WorldStateVariables::BombNearEnemy, true);
	action.reaction.add(WorldStateVariables::EnemyAlive, true);

	posibleActions.emplace("Detonar", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//fugir d'un enemic
	action.cost = 2;
	action.definition = "Alejarse de enemigo\n";
	action.preConditions.add(WorldStateVariables::EnemyNear, true);
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.reaction.add(WorldStateVariables::EnemyNear, false);
	action.reaction.add(WorldStateVariables::EnemyAligned, false);
	action.reaction.add(WorldStateVariables::EnemyVisible, false);

	posibleActions.emplace("Alejarse", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;

	//get bombas
	action.cost = 3;
	action.definition = "Coger explosivos\n";
	action.preConditions.add(WorldStateVariables::AgentHasBomb, false);
	action.preConditions.add(WorldStateVariables::EnemyNear, false);
	action.preConditions.add(WorldStateVariables::AgentAlive, true);
	action.reaction.add(WorldStateVariables::AgentHasBomb, true);
	action.reaction.add(WorldStateVariables::EnemyAligned, false);
	action.reaction.add(WorldStateVariables::EnemyVisible, false);

	posibleActions.emplace("GetBomb", action);
	action.preConditions.bits = 0;
	action.preConditions.mask = 0;
	action.reaction.bits = 0;
	action.reaction.mask = 0;
}


SceneGoap::~SceneGoap()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneGoap::update(float dtime, SDL_Event *event)
{
	deltaTime = dtime;
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			/*Vector2D cell = pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (isValidCell(cell))
			{
				if (path.points.size() > 0)
					if (path.points[path.points.size() - 1] == cell2pix(cell))
						break;

				path.points.push_back(cell2pix(cell));
			}*/
			
		}
		break;
	default:
		break;
	}
	if ((currentTargetIndex == -1) && (path.points.size()>0))
		currentTargetIndex = 0;

	if (currentTargetIndex >= 0)
	{	
		float dist = Vector2D::Distance(agents[0]->getPosition(), path.points[currentTargetIndex]);
		if (dist < path.ARRIVAL_DISTANCE)
		{
			if (currentTargetIndex == path.points.size() - 1)
			{
				if (dist < 3)
				{
					path.points.clear();
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0,0));
					// if we have arrived to the coin, replace it ina random cell!
					if (pix2cell(agents[0]->getPosition()) == coinPosition)
					{
						coinPosition = Vector2D(-1, -1);
						while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition()))<3))
							coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
					}
				}
				else
				{
					Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], currentTarget, path.ARRIVAL_DISTANCE, dtime);
					agents[0]->update(steering_force, dtime, event);
				}
				return;
			}
			currentTargetIndex++;
		}

		currentTarget = path.points[currentTargetIndex];
		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		agents[0]->update(steering_force, dtime, event);
	} 
	else
	{
		agents[0]->update(Vector2D(0,0), dtime, event);
	}
}

void SceneGoap::draw()
{
	drawMaze();
	drawCoin();


	if (draw_grid)
	{

		//drawGraph();
		//drawGraphConexions();
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* SceneGoap::getTitle()
{
	return "SDL Steering Behaviors :: PathFinding1 Demo";
}

void SceneGoap::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
	}
}

void SceneGoap::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneGoap::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 128, 160, 1152, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);
	
	rect = { 0,32,32,736 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,736 };
	maze_rects.push_back(rect);

	rect = { 416,512,32,268 };
	maze_rects.push_back(rect);
	rect = { 832,512,32,268 };
	maze_rects.push_back(rect);
	
	rect = { 32,480,128,32 };
	maze_rects.push_back(rect);
	rect = { 288,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 704,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 1120,480,128,32 };
	maze_rects.push_back(rect);

	// Initialize the terrain matrix (for each cell a zero value indicates it's a wall)
	
	// (1st) initialize all cells to 1 by default
	for (int i = 0; i < num_cell_x; i++)
	{
		vector<int> terrain_col(num_cell_y, 1); 
		terrain.push_back(terrain_col);
	}
	// (2nd) set to zero all cells that belong to a wall
	int offset = CELL_SIZE / 2;
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			Vector2D cell_center ((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
			for (unsigned int b = 0; b < maze_rects.size(); b++)
			{
				if (Vector2DUtils::IsInsideRect(cell_center, (float)maze_rects[b].x, (float)maze_rects[b].y, (float)maze_rects[b].w, (float)maze_rects[b].h))
				{
					terrain[i][j] = 0;
				    break;
				}  
			}
			
		}
	}

}

bool SceneGoap::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	/*if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		//return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);
	*/
	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D SceneGoap::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D SceneGoap::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x/CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool SceneGoap::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()) )
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}