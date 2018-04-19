#pragma once
#include <Windows.h>

class Timer
{
private:
	LARGE_INTEGER m_Start, m_End, m_Frequency;

public:
	//CONSTRUCTORS/DESTRUCTOR
	Timer() {};
	~Timer() {};

	//METHODS
	void Start() { QueryPerformanceFrequency(&m_Frequency); QueryPerformanceCounter(&m_Start); }
	double End() { QueryPerformanceCounter(&m_End); return (m_End.QuadPart - m_Start.QuadPart) / (double)m_Frequency.QuadPart; }
};