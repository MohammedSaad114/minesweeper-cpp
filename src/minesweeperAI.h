#pragma once
#include "raylib.h"
#include <optional>
#include <set>
#include <vector>

struct Cell;
class Sentence;

/**
* @class MinesweeperAI
* @brief Minesweeper game AI player
*/
class MinesweeperAI {
public:
	explicit MinesweeperAI(int h, int w);
	/**
	* Updates internal knowledge with the fact that
	* a cell is known to be a mine or safe
	*/
	void markMine(Cell cell);
	void markSafe(Cell cell);

	/**
	* Adds new information to internal knowledge
	* This new information is directly known from the board or,
	* it is inferred from all of the prior knowlede
	*/
	void addKnowledge(Cell cell, int count);

	/**
	* Returns a cell that is known to be safe
	*/
	std::optional<Cell> makeSafeMove();

	/**
	* Returns an available cell that is not a mine
	*/
	std::optional<Cell> makeRandomMove();
private:
	int m_Height;
	int m_Width;
	std::set<Cell> m_Mines;
	std::set<Cell> m_Safes;
	std::set<Cell> m_MadeMoves;
	std::vector<Sentence> m_Knowledge;
};