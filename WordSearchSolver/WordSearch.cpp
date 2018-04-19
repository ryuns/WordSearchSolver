#include "WordSearch.h"
#include "Cell.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct FoundWord {
	std::string m_Word;
	int m_XCoord;
	int m_YCoord;
};

Cell **puzzleGrid;
Cell *puzzle;
int puzzleSize;
std::vector<std::string> dictionary;
std::vector<FoundWord> foundWords;
std::vector<std::string> unfoundWords;
int cellsVisited;
int dictionaryEntriesVisited;

WordSearch::WordSearch(){
}

WordSearch::WordSearch(const WordSearch & pWordSearch) : m_PuzzleName(pWordSearch.m_PuzzleName), m_DictionaryName(pWordSearch.m_DictionaryName), m_OutputFileName(pWordSearch.m_OutputFileName)
{
}

WordSearch::~WordSearch() {
	delete[] puzzle;
	delete[] puzzleGrid;
	foundWords.clear();
	unfoundWords.clear();
	cellsVisited = 0;
	dictionaryEntriesVisited = 0;
	puzzleSize = 0;
}

void WordSearch::ReadDictionary() const {
	std::ifstream fileIn((std::string(m_DictionaryName)));

	if (fileIn.is_open())
	{
		std::string stringInput;

		while (fileIn >> stringInput)
		{
			dictionary.push_back(stringInput);
		}
	}
}

void WordSearch::ReadPuzzle() const {
	std::ifstream fileIn((std::string(m_PuzzleName)));

	if (fileIn.is_open())
	{
		fileIn >> puzzleSize;

		puzzleGrid = new Cell* [puzzleSize];
		puzzle = new Cell[puzzleSize * puzzleSize];
		int counter = 0;
		char character;

		for (int cY = 0; cY < puzzleSize; ++cY)
		{
			//Allows the ability to search the advanced puzzle using a 2D grid search in the format
			//puzzleGrid[Y][X].
			puzzleGrid[cY] = &puzzle[cY * puzzleSize];
			for (int cX = 0; cX < puzzleSize; ++cX)
			{
				//Reads the next character into a char;
				fileIn >> character;

				//Sets the basic information of a cell.  Char, XCoord, YCoord.
				puzzle[counter].SetCharacter(character);
				puzzle[counter].SetXCoord(cX);
				puzzle[counter].SetYCoord(cY);

				if (cX == 0)
				{
					//If x is 0 right is always possible.
					puzzle[counter].SetRight(&puzzle[counter + 1]);
					if (cY == 0)
					{
						//If x and y are 0 down and right down are always possible.
						puzzle[counter].SetDown(&puzzle[counter + puzzleSize]);
						puzzle[counter].SetRightDown(&puzzle[counter + (puzzleSize + 1)]);
					}
					else if (cY == puzzleSize - 1)
					{
						//If x is 0 and y is 1 less than puzzlesize then up and right up are alwyas possible.
						puzzle[counter].SetUp(&puzzle[counter - puzzleSize]);
						puzzle[counter].SetRightUp(&puzzle[counter - (puzzleSize - 1)]);
					}
					else
					{
						//If x is 0 and y is any other value than 0 or 1 less than puzzlesize then all directions above are possible.
						puzzle[counter].SetUp(&puzzle[counter - puzzleSize]);
						puzzle[counter].SetRightUp(&puzzle[counter - (puzzleSize - 1)]);
						puzzle[counter].SetDown(&puzzle[counter + puzzleSize]);
						puzzle[counter].SetRightDown(&puzzle[counter + (puzzleSize + 1)]);
					}
				}
				else if (cX == puzzleSize - 1)
				{
					//If x is 1 less than puzzle size then left is always possible.
					puzzle[counter].SetLeft(&puzzle[counter - 1]);
					if (cY == 0)
					{
						//If x is 1 less than puzzlesize and y is 0 then down and downright are possible.
						puzzle[counter].SetDown(&puzzle[counter + puzzleSize]);
						puzzle[counter].SetLeftDown(&puzzle[counter + (puzzleSize - 1)]);
					}
					else if (cY == puzzleSize - 1)
					{
						//If x is 1 less than puzzlesize and y is 1 less than puzzle size then up and leftup are possible.
						puzzle[counter].SetUp(&puzzle[counter - puzzleSize]);
						puzzle[counter].SetLeftUp(&puzzle[counter - (puzzleSize + 1)]);
					}
					else
					{
						//If x is 1 less than puzzlesize and y is any thing other than 0 or 1 less than puzzlesize then all directions above are possible.
						puzzle[counter].SetDown(&puzzle[counter + puzzleSize]);
						puzzle[counter].SetLeftDown(&puzzle[counter + (puzzleSize - 1)]);
						puzzle[counter].SetUp(&puzzle[counter - puzzleSize]);
						puzzle[counter].SetLeftUp(&puzzle[counter - (puzzleSize + 1)]);
					}
				}
				else
				{
					//If x is any thing other than 0 or 1 less than puzzlesize then right and left are possible.
					puzzle[counter].SetRight(&puzzle[counter + 1]);
					puzzle[counter].SetLeft(&puzzle[counter - 1]);
					if (cY == 0)
					{
						//If x is any thing other than 0 or 1 less than puzzlesize and y is 0 then down, rightdown and left down are possible.
						puzzle[counter].SetDown(&puzzle[counter + puzzleSize]);
						puzzle[counter].SetRightDown(&puzzle[counter + (puzzleSize + 1)]);
						puzzle[counter].SetLeftDown(&puzzle[counter + (puzzleSize - 1)]);
					}
					else if (cY == puzzleSize - 1)
					{
						//If x is any thing other than 0 or 1 less than puzzlesize and y is 1 less than puzzlesize then up, rightup and leftup are possible.
						puzzle[counter].SetUp(&puzzle[counter - puzzleSize]);
						puzzle[counter].SetRightUp(&puzzle[counter - (puzzleSize - 1)]);
						puzzle[counter].SetLeftUp(&puzzle[counter - (puzzleSize + 1)]);
					}
					else
					{
						//If x is any thing other than 0 or 1 less than puzzlesize and y is any thing other than 0 or 1 less than puzzle size
						//then any direction is possible.
						puzzle[counter].SetUp(&puzzle[counter - puzzleSize]);
						puzzle[counter].SetRightUp(&puzzle[counter - (puzzleSize - 1)]);
						puzzle[counter].SetLeftUp(&puzzle[counter - (puzzleSize + 1)]);
						puzzle[counter].SetDown(&puzzle[counter + puzzleSize]);
						puzzle[counter].SetRightDown(&puzzle[counter + (puzzleSize + 1)]);
						puzzle[counter].SetLeftDown(&puzzle[counter + (puzzleSize - 1)]);
					}
				}

				++counter;
			}
		}
	}
}

void WordSearch::SolvePuzzle() const {
	for(int i = 0; i < dictionary.size(); ++i)
	{
		++dictionaryEntriesVisited;
		bool wordMatched = false;

		for (int j = 0; j < puzzleSize * puzzleSize; ++j)
		{
			++cellsVisited;
			Cell* current = &puzzle[j];

			if (current->Character() == dictionary[i][0])
			{
				/*bool right = current->XCoord() + ((int)dictionary[i].length() - 1) < puzzleSize ? true : false;
				bool left = current->XCoord() - ((int)dictionary[i].length() - 1) > -1 ? true : false;
				bool up = current->YCoord() - ((int)dictionary[i].length() - 1) > -1 ? true : false;
				bool down = current->YCoord() + ((int)dictionary[i].length() - 1) < puzzleSize ? true : false;

				if (right)
				{
					if (current->CheckRight(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
					if (up)
					{
						if (current->CheckRightUp(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
					if (down)
					{
						if (current->CheckRightDown(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
				}
				if (left)
				{
					if (current->CheckLeft(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
					if (up)
					{
						if (current->CheckLeftUp(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
					if (down)
					{
						if (current->CheckLeftDown(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
				}
				if (up)
				{
					if (current->CheckUp(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
				}
				if (down)
				{
					if (current->CheckDown(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
				}*/



				if (current->XCoord() + ((int)dictionary[i].length() - 1) < puzzleSize)
				{
					if (current->CheckRight(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
					if (current->YCoord() - ((int)dictionary[i].length() - 1) > -1)
					{
						if (current->CheckRightUp(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
					if(current->YCoord() + ((int)dictionary[i].length() - 1) < puzzleSize)
					{
						if (current->CheckRightDown(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
				}
				if(current->XCoord() - ((int)dictionary[i].length() - 1) > -1)
				{
					if (current->CheckLeft(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
					if (current->YCoord() - ((int)dictionary[i].length() - 1) > -1)
					{
						if (current->CheckLeftUp(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
					if(current->YCoord() + ((int)dictionary[i].length() - 1) < puzzleSize)
					{
						if (current->CheckLeftDown(cellsVisited, dictionary[i]))
						{
							foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
							wordMatched = true;
							break;
						}
					}
				}
				if (current->YCoord() - ((int)dictionary[i].length() - 1) > -1)
				{
					if (current->CheckUp(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
				}
				if (current->YCoord() + ((int)dictionary[i].length() - 1) < puzzleSize)
				{
					if (current->CheckDown(cellsVisited, dictionary[i]))
					{
						foundWords.push_back(FoundWord{ dictionary[i], current->XCoord(), current->YCoord() });
						wordMatched = true;
						break;
					}
				}
			}
		}
		if (!wordMatched)
		{
			unfoundWords.push_back(dictionary[i]);
		}
	}
}

void WordSearch::WriteResults(const double pPuzzleLoadTime, const double pPuzzleSolveTime) const {
	std::ofstream outStream((std::string(m_OutputFileName)));

	outStream << "Number Of Words Matched: " << foundWords.size() << std::endl << std::endl <<
		"Words Matched With X and Y Coordinates:" << std::endl;
	for (int i = 0; i < foundWords.size(); ++i)
	{
		outStream << foundWords[i].m_XCoord << " " << foundWords[i].m_YCoord << " " << foundWords[i].m_Word << std::endl;
	}
	outStream << std::endl <<
		"Words Unmatched:" << std::endl;
	for (int i = 0; i < unfoundWords.size(); ++i)
	{
			outStream << unfoundWords[i] << std::endl;
	}
	outStream << std::endl <<
		"Number Of Grid Cells Visited: " << cellsVisited << std::endl << std::endl <<
		"Number Of Dictionary Entries Visited: " << dictionaryEntriesVisited << std::endl << std::endl <<
		"Time Taken To Populate The Grid Structure: " << pPuzzleLoadTime << std::endl << std::endl <<
		"Time Taken To Solve The puzzle: " << pPuzzleSolveTime << std::endl << std::endl;
}

WordSearch & WordSearch::operator=(const WordSearch & pWordSearch)
{
	if (this != &pWordSearch)
	{
		m_PuzzleName = pWordSearch.m_PuzzleName;
		m_DictionaryName = pWordSearch.m_DictionaryName;
		m_OutputFileName = pWordSearch.m_OutputFileName;
	}

	return *this;
}