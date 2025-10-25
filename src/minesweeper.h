#pragma once
#include "raylib.h"
#include <set>
#include <vector>

struct Cell;

enum Field { SAFE = 0, MINE = 1};

/**
* @class Minesweeper
* @brief Represents the Minesweeper game
*/
class Minesweeper {
public:
	explicit Minesweeper(int h, int w, int m);
	/**
	* Prints where mines are located
	*/
	void printMines();
	Field isMine(Cell cell);
	/**
	* Returns the number of mines that are
      within one row and column of a given cell,
      not including the cell itself.
	*/
	int minesInRadius(Cell cell);
	bool won();
private:
	int m_Height;
	int m_Width;
	std::set<Cell> m_Mines;
	std::vector<std::vector<Field>> m_Board;
	std::set<Cell> m_MinesFound;
};
