#ifndef ROBOTINQ_H
#define ROBOTINQ_H

#include "RobotComponent.hpp"

class RobotInQ
{
    public:
        RobotInQ(RobotComponent::RobotType theType, float timeToSpawn);
        virtual ~RobotInQ();

        RobotComponent::RobotType robotType;
        float queuedAt;
        float spawnTime;
        bool spawned;

    protected:
    private:
};

#endif // ROBOTINQ_H
