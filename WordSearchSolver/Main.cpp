#include "WordSearch.h"
#include "Timer.h"

int main(int, char **) {

	Timer timer;
	WordSearch search;

	timer.Start();
	search.ReadDictionary();
	search.ReadPuzzle();
	const double PuzzleLoadTime = timer.End();

	timer.Start();
	search.SolvePuzzle();
	const double PuzzleSolveTime = timer.End();

	search.WriteResults(PuzzleLoadTime, PuzzleSolveTime);

	return 0;
}