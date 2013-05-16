#include "RobotInQ.hpp"
#include "Time.hpp"

RobotInQ::RobotInQ(RobotComponent::RobotType type_, float spawnTime_):robotType(type_), spawnTime(spawnTime_), spawned(false)
{
    //ctor
    queuedAt = Time::currentTime;
}

RobotInQ::~RobotInQ()
{
    //dtor
    std::cout << "destroying robot in q after " << spawnTime - queuedAt << " seconds " << std::endl;
}
