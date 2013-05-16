#ifndef ROBOTCOMPONENT_H
#define ROBOTCOMPONENT_H

#include "RobotBehaviour.hpp"
#include "Destructable.hpp"
#include "Component.hpp"
class CellManager;
class Transform;
class Cell;


class RobotComponent : public Component, public Destructable
{
    public:

		friend class RobotBehaviour;

        enum RobotType{
            WireCutter,
            Explosive,
            LaserTurret
        };
        RobotComponent(RobotType robotType);
        virtual ~RobotComponent();
        virtual void update();
        void onConnect();
        float getMoveSpeed();
        virtual void move(glm::vec3 translation);
        void rotateTo(glm::vec3 direction);
        bool moveTo(Cell * cell);
        void followMapPath();
        float getBuildTime()const;
        RobotType getRobotType()const;
        void playAttackSound();

        virtual const std::string getName(){return "RobotComponent";}

        void setRobotBehaviour(RobotType behaveType);

        void stop();

    protected:
		virtual void onDestroy();
		virtual void initializeHealth(float mh);
    private: // stats

        //sound variables
        bool playingSound;
        float lastSound;
        float soundDuration;


		float hbOffsetY;
		float buildTime;
		std::string attackSound;

		float moveSpeed;
		float shotsPerSecond;
		float damagePerShot;
		float range;

		float lastShotTime;

		Transform * tr;
		RobotType robotType;
        RobotBehaviour behaviour;
};

#endif // ROBOTCOMPONENT_H
