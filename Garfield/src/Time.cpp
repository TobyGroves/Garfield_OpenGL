#include "Time.h"
#include <ctime>

Time::Time()
{

	time = std::clock() / 1000.0f;
}

void Time::gameStart()
{
	startTime= std::clock();
	time = std::clock() / 1000.0f;

}

void Time::timeUpdate()
{
	oldTime = newTime;
	newTime = std::clock();

	deltaTime = (newTime - oldTime) / 1000.0f;
	time = std::clock() / 1000.0f;
}