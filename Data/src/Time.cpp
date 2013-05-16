#include "Time.hpp"

Time::Time()
{
	//ctor
}

Time::~Time()
{
	//dtor
}
void Time::update()
{
	float newTime = Time::clock.getElapsedTime().asSeconds();
	Time::deltaTime = newTime - Time::currentTime;
	Time::currentTime = newTime;
}

float Time::now()
{
	return Time::clock.getElapsedTime().asSeconds();
}

float Time::step()
{
	return deltaTime;
}


sf::Clock Time::clock;
float Time::currentTime;
float Time::deltaTime;

