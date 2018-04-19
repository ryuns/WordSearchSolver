#pragma once

class WordSearch {
private:
	const char* m_PuzzleName = "WordsearchPuzzle.txt";
	const char* m_DictionaryName = "Dictionary.txt";
	const char* m_OutputFileName = "SolvedWordsearch.txt";

public:
	//CONSTRUCTORS/DESTRUCTOR
	WordSearch();
	WordSearch(const WordSearch &pWordSearch);
	~WordSearch();

	//METHODS
	void ReadDictionary() const;
	void ReadPuzzle() const;
	void SolvePuzzle() const;
	void WriteResults(const double pPuzzleLoadTime, const double pPuzzleSolveTime) const;

	//OPERATORS
	WordSearch &operator =(const WordSearch &pWordSearch);
};