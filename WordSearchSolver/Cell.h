#pragma once
#include<string>

class Cell
{
private:
	Cell *m_Right;
	Cell *m_Left;
	Cell *m_Up;
	Cell *m_Down;
	Cell *m_RightUp;
	Cell *m_RightDown;
	Cell *m_LeftUp;
	Cell *m_LeftDown;
	int m_PuzzleSize;
	int m_XCoord;
	int m_YCoord;
	char m_Character;

	//PRIVATE METHODS
	bool CheckRight(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckLeft(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckUp(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckDown(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckRightUp(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckRightDown(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckLeftUp(int& const pCellsVisited, const std::string& pWord) const;
	bool CheckLeftDown(int& const pCellsVisited, const std::string& pWord) const;

public:
	//CONSTRUCTORS/DESTRUCTOR
	Cell();
	Cell(const Cell &pCell);
	~Cell();

	//GETTERS/SETTERS
	void SetCharacter(const char pCharacter) { m_Character = pCharacter; }

	void SetPuzzleSize(const int pPuzzleSize) { m_PuzzleSize = pPuzzleSize; }

	const int XCoord() const { return m_XCoord; }
	void SetXCoord(const int pXCoord) { m_XCoord = pXCoord; }

	const int YCoord() const { return m_YCoord; }
	void SetYCoord(const int pYCoord) { m_YCoord = pYCoord; }

	void SetRight(Cell* const  pCell) { m_Right = pCell; }

	void SetLeft(Cell* const  pCell) { m_Left = pCell; }

	void SetUp(Cell* const  pCell) { m_Up = pCell; }

	void SetDown(Cell* const  pCell) { m_Down = pCell; }

	void SetRightUp(Cell* const  pCell) { m_RightUp = pCell; }

	void SetRightDown(Cell* const  pCell) { m_RightDown = pCell; }

	void SetLeftUp(Cell* const  pCell) { m_LeftUp = pCell; }

	void SetLeftDown(Cell* const  pCell) { m_LeftDown = pCell; }

	bool FindWord(int& const pCellsVisited, const std::string& pWord) const;

	//OPERATORS
	Cell &operator =(const Cell &pCell);
};