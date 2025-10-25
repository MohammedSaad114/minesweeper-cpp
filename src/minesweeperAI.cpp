#include "minesweeperAI.h"
#include <random>
#include "sentence.h"

MinesweeperAI::MinesweeperAI(int h, int w) : m_Height(h), m_Width(w) {}

void MinesweeperAI::markMine(Cell cell)
{
	m_Mines.insert(cell);
	for (Sentence& s : m_Knowledge)
		s.markMine(cell);
}

void MinesweeperAI::markSafe(Cell cell)
{
	m_Safes.insert(cell);
	for (Sentence& s : m_Knowledge)
		s.markSafe(cell);
}

void MinesweeperAI::addKnowledge(Cell cell, int count)
{
	m_MadeMoves.insert(cell);
	markSafe(cell);
}

std::optional<Cell> MinesweeperAI::makeSafeMove()
{
	// safe cells are all known safes and deduced ones
	auto safeCells = m_Safes;

	for (Sentence& s : m_Knowledge)
	{
		auto newSafes = s.knownSafes(); 
		safeCells.insert(newSafes.begin(), newSafes.end());
	}

	for (Cell c : m_MadeMoves)
	{
		safeCells.erase(c);
	}

	if (safeCells.empty())
		return std::nullopt;

	// pick one randomly
	std::vector<Cell> candidates(safeCells.begin(), safeCells.end());
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, (int)candidates.size() - 1);
	return candidates[dist(gen)];

}

std::optional<Cell> MinesweeperAI::makeRandomMove()
{
	// all cells on board that haven't played and aren't mines
	std::set<Cell> allCells;
	
	// all board cells
	for (int i = 0; i < m_Height; ++i)
		for (int j = 0; j < m_Width; ++j)
			allCells.insert({ i, j });

	// all known mines from knowledge
	std::set<Cell> mines = m_Mines;
	for (Sentence& s : m_Knowledge)
	{
		auto knownMines = s.knownMines();
		mines.insert(knownMines.begin(), knownMines.end());
	}

	std::set<Cell> possibleCells;
	for (const auto& c : allCells)
		if (!m_MadeMoves.count(c) && !mines.count(c))
			possibleCells.insert(c);

	if (possibleCells.empty())
		return std::nullopt;

	// pick one randomly
	std::vector<Cell> candidates(possibleCells.begin(), possibleCells.end());
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, (int)candidates.size() - 1);
	return candidates[dist(gen)];
}
