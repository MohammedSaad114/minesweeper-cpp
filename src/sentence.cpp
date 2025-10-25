#include <string>
#include <sstream>
#include <functional>

#include "sentence.h"

namespace std {
    template<>
    struct hash<Cell> {
        std::size_t operator()(const Cell& c) const noexcept {
            // Combine both integers into one hash
            // (a simple but effective method)
            return (std::hash<int>()(c.rowIndex) << 1) ^ std::hash<int>()(c.columnIndex);
        }
    };
}

Sentence::Sentence(int num, const std::set<Cell>& c)
	: m_Count(num), m_Cells(c) {}

bool Sentence::operator==(const Sentence& other) const
{
	return m_Cells == other.m_Cells && m_Count == other.m_Count;
}

std::string Sentence::toString() const
{
	std::ostringstream out;
	out << "{";
	bool first = true;
	for (const Cell& cell : m_Cells)
	{
		if (!first) out << ", ";
		out << "(" << cell.rowIndex << "," << cell.columnIndex << ")";
		first = false;
	}
	out << "} = " << m_Count;
	return out.str();
}

void Sentence::markMine(Cell cell)
{
	if (m_Cells.find(cell) != m_Cells.end())
		m_Cells.erase(cell); m_Count--;
}

void Sentence::markSafe(Cell cell)
{
	if (m_Cells.find(cell) != m_Cells.end())
		m_Cells.erase(cell);
}

std::set<Cell> Sentence::knownMines()
{
	if (m_Count == m_Cells.size() && m_Cells.size() > 0)
		return m_Cells;
	return {};
}

std::set<Cell> Sentence::knownSafes()
{
	if (m_Count == 0 && m_Cells.size() > 0)
		return m_Cells;
	return {};
}
