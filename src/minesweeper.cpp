
#include <vector>
#include <random>
#include "sentence.h"
#include "minesweeper.h"

Minesweeper::Minesweeper(int h, int w, int m) : m_Height(h), m_Width(w), m_Board(h, std::vector<Field>(w, SAFE))
{
	// placing mines randomly
	std::random_device rd; std::mt19937 gen(rd());
	std::uniform_int_distribution<int> r(0, m_Height - 1);
	std::uniform_int_distribution<int> c(0, m_Width - 1);

	int placed = 0;
	while (placed < m)
	{
		int i = r(gen);
		int j = c(gen);
		if (m_Board[i][j] != MINE)
			m_Board[i][j] = MINE;
		m_Mines.insert({ i,j });
		placed++;
	}
}

void Minesweeper::printMines()
{
}

Field Minesweeper::isMine(Cell cell)
{
	int i = cell.rowIndex;
	int j = cell.columnIndex;
	return m_Board[i][j];
}

int Minesweeper::minesInRadius(Cell cell)
{
	int count = 0;

	// Cells within one radius
	for (int i = cell.rowIndex - 1; i <= cell.rowIndex + 1; ++i)
	{
		for (int j = cell.columnIndex - 1; j <= cell.columnIndex + 1; ++j)
		{
			if (i < 0 || j < 0 || i >= m_Height || j >= m_Width)
				continue;

			if (i == cell.rowIndex && j == cell.columnIndex)
				continue;

			if (m_Board[i][j] == MINE)
				count++;
		}
	}
	return count;
}

bool Minesweeper::won()
{
	return m_MinesFound == m_Mines;
}
