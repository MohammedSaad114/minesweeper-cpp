#pragma once
#include <utility>
#include "minesweeper.h"
#include "minesweeperAI.h"

enum class State { Menu, Playing };

struct App {
	// window
	int width{}, height{};

	// board layout
	int boardWidth; int boardHeight;
	int cellSize;
	std::pair<int, int> boardOrigin;
	Font uiFont;

	// game
	State state{ State::Menu };
	Minesweeper game;
	MinesweeperAI ai;
	std::set<Cell> revealedCells;
	std::set<Cell> flaggedCells;
	bool lost { false };
	bool instructions{ true };
};

/**
* init ui and game info
*/
void initApp(App& app, int w, int h);

/**
* handles input, update of one frame
*/
void frame(App& app);

/**
* Cleans up used resources by app
*/
void cleanupApp(App& app);