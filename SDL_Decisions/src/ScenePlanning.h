#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Node.h"
#include "Aestrella.h"

class ScenePlanning :
	public Scene
{
public:
	ScenePlanning();
	~ScenePlanning();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	float deltaTime;

	//atributs i metodes que necessitem publiques
	Path path;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	Node* findInGraph(Vector2D position);
	Vector2D coinPosition;
private:
	std::vector<Agent*> agents;
	
	Vector2D currentTarget;
	int currentTargetIndex;
	
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin();
	void drawSaloon();
	void drawHouse();
	void drawBank();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	void initMaze();
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector< std::vector<int> > terrain;
	

	std::vector<std::vector<Node>> graph;
	void createGraph();
	int wallsOnCollumn(int column);
	int wallsOnCollumn(int column, int row);

	//debugGraph
	void drawGraph();

	//debug busqueda
	void drawGraphConexions();

};
