#include "Cell.h"



Cell::Cell() : m_Right(nullptr), m_Left(nullptr), m_Up(nullptr), m_Down(nullptr), m_RightUp(nullptr), m_RightDown(nullptr), m_LeftUp(nullptr), m_LeftDown(nullptr), m_XCoord(0), m_YCoord(0), m_Character(' ')
{
}

Cell::Cell(const Cell & pCell) : m_Right(pCell.m_Right), m_Left(pCell.m_Left), m_Up(pCell.m_Up), m_Down(pCell.m_Down), m_RightUp(pCell.m_RightUp), m_RightDown(pCell.m_RightDown), m_LeftUp(pCell.m_LeftUp), m_LeftDown(pCell.m_LeftDown), m_XCoord(pCell.m_XCoord), m_YCoord(pCell.m_YCoord), m_Character(pCell.m_Character)
{
}

Cell::~Cell()
{
}

bool Cell::CheckRight(int& const pCellsVisited, const std::string& pWord) const
{
	Cell* Next = m_Right;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->Right();
	}

	return true;
}

bool Cell::CheckLeft(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_Left;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->Left();
	}

	return true;
}

bool Cell::CheckUp(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_Up;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->Up();
	}

	return true;
}

bool Cell::CheckDown(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_Down;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->Down();
	}

	return true;
}

bool Cell::CheckRightUp(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_RightUp;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->RightUp();
	}

	return true;
}

bool Cell::CheckRightDown(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_RightDown;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->RightDown();
	}

	return true;
}

bool Cell::CheckLeftUp(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_LeftUp;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->LeftUp();
	}

	return true;
}

bool Cell::CheckLeftDown(int & const pCellsVisited, const std::string & pWord) const
{
	Cell* Next = m_LeftDown;
	for (int pCounter = 1; pCounter < pWord.length(); ++pCounter)
	{
		++pCellsVisited;
		if (Next->Character() != pWord[pCounter])
		{
			return false;
		}

		Next = Next->LeftDown();
	}

	return true;
}

Cell & Cell::operator=(const Cell & pCell)
{
	if (this != &pCell)
	{
		m_Right = pCell.m_Right;
		m_Left = pCell.m_Left;
		m_Up = pCell.m_Up;
		m_Down = pCell.m_Down;
		m_RightUp = pCell.m_RightUp;
		m_RightDown = pCell.m_RightDown;
		m_LeftUp = pCell.m_LeftUp;
		m_LeftDown = pCell.m_LeftDown;
		m_Character = pCell.m_Character;
		m_XCoord = pCell.m_XCoord;
		m_YCoord = pCell.m_YCoord;
	}

	return *this;
}
