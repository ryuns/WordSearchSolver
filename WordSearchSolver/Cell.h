#pragma once
#include<string>

class Cell
{
private:
	Cell *m_Right, *m_Left, *m_Up, *m_Down, *m_RightUp, *m_RightDown, *m_LeftUp, *m_LeftDown;
	int m_XCoord, m_YCoord;
	char m_Character;

public:
	//CONSTRUCTORS/DESTRUCTOR
	Cell();
	Cell(const Cell &pCell);
	~Cell();

	//GETTERS/SETTERS
	const char Character() const { return m_Character; }
	void SetCharacter(const char pCharacter) { m_Character = pCharacter; }

	const int XCoord() const { return m_XCoord; }
	void SetXCoord(const int pXCoord) { m_XCoord = pXCoord; }

	const int YCoord() const { return m_YCoord; }
	void SetYCoord(const int pYCoord) { m_YCoord = pYCoord; }

	Cell* Right() const { return m_Right; }
	void SetRight(Cell* const  pCell) { m_Right = pCell; }
	bool CheckRight(int& const pCellsVisited, const std::string& pWord) const;

	Cell* Left() const { return m_Left; }
	void SetLeft(Cell* const  pCell) { m_Left = pCell; }
	bool CheckLeft(int& const pCellsVisited, const std::string& pWord) const;

	Cell* Up() const { return m_Up; }
	void SetUp(Cell* const  pCell) { m_Up = pCell; }
	bool CheckUp(int& const pCellsVisited, const std::string& pWord) const;

	Cell* Down() const { return m_Down; }
	void SetDown(Cell* const  pCell) { m_Down = pCell; }
	bool CheckDown(int& const pCellsVisited, const std::string& pWord) const;

	Cell* RightUp() const { return m_RightUp; }
	void SetRightUp(Cell* const  pCell) { m_RightUp = pCell; }
	bool CheckRightUp(int& const pCellsVisited, const std::string& pWord) const;

	Cell* RightDown() const { return m_RightDown; }
	void SetRightDown(Cell* const  pCell) { m_RightDown = pCell; }
	bool CheckRightDown(int& const pCellsVisited, const std::string& pWord) const;

	Cell* LeftUp() const { return m_LeftUp; }
	void SetLeftUp(Cell* const  pCell) { m_LeftUp = pCell; }
	bool CheckLeftUp(int& const pCellsVisited, const std::string& pWord) const;

	Cell* LeftDown() const { return m_LeftDown; }
	void SetLeftDown(Cell* const  pCell) { m_LeftDown = pCell; }
	bool CheckLeftDown(int& const pCellsVisited, const std::string& pWord) const;

	//OPERATORS
	Cell &operator =(const Cell &pCell);
};