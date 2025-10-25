#pragma once
#include "raylib.h"
#include <utility>
#include "minesweeper.h"
#include <unordered_map>
#include <string>
#include <set>
#include <tuple>

struct Cell {
	int rowIndex;
	int columnIndex;

	bool operator==(const Cell& other) const noexcept
	{
		return rowIndex == other.rowIndex && columnIndex == other.columnIndex;
	}

	bool operator<(const Cell& other) const noexcept
	{
		return std::tie(rowIndex, columnIndex) < std::tie(other.rowIndex, other.columnIndex);
	}
};

/**
* @class Sentence
* @brief Logical statement about a Minesweeper game
*/
class Sentence {
public:
	explicit Sentence(int num, const std::set<Cell>& c);
	bool operator==(const Sentence& other) const; // equality
	std::string toString() const;    // string conversion

	/**
	* Updates internal knowledge with the fact that
	* a cell is known to be a mine or safe
	*/
	void markMine(Cell cell) ;
	void markSafe(Cell cell);

	/**
	* return all cells known to be mines or safes
	*/
	std::set<Cell> knownMines();
	std::set<Cell> knownSafes();

private:
	int m_Count;
	std::set<Cell> m_Cells;
};