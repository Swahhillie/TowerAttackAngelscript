#include <iostream>

#include "FPS.hpp"
#include "Time.hpp"

float FPS::startTime;
int FPS::count;

void FPS::update()
{
	float time = Time::now();
	FPS::count++;
	if ( time - startTime >= 6.0f ) {
		std::cout << "FPS " << count / 6.0f<< std::endl;
		count = 0;
		startTime = time;
	}
}
