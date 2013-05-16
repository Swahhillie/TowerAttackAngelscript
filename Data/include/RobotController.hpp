#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include <vector>
#include <list>

#include "RobotComponent.hpp"
class Defender;
class Destructable;
class ObjectBank;
class RobotInQ;
class Turret;

class RobotController
{
	public:

		virtual ~RobotController();
		static RobotController& instance(){
			static RobotController INSTANCE;
			return INSTANCE;
		}
		virtual const std::string getName(){return "RobotController";}
		void update();
        static const unsigned int ROBOTQUEUEAMOUNT = 8;
        const std::vector<RobotInQ * > & getRobotQueue();
        void clearQueue();
        const std::vector<Defender * > & getDefenders()const;
        const std::vector<RobotComponent *> & getRobots()const;


		void addRobot(RobotComponent * robot);
		void removeRobot(RobotComponent * robot);

		void markRobotsForDestroy();

		void addDefender(Defender * target);
		void removeDefender(Defender * target);

		ObjectBank * objectBank;
		void addToQ(RobotComponent::RobotType robotType);

		RobotComponent * getNearestRobot(const glm::vec3 & fromPos);
		RobotComponent * getNearestVisibleRobot(const glm::vec3 & from, const float & range = INFINITY);
		Defender * getNearestDefender(const glm::vec3 & from, const float & range = INFINITY);

	protected:
	private:

		RobotController();
		bool warnedOutOfRobots;
		int getCost(RobotComponent::RobotType robotType);

		int robotWireCutterCost;
		int robotExplosiveCost;
		int robotLaserTurretCost;


//		ObjectBank * objectBank;
		std::vector<RobotComponent *> robots;
		std::vector<Defender *> defenders;
		std::vector<RobotInQ *> robotQueue;

		float getDistanceBetween(const Object * a ,const Object * b)const;
		float getDistanceBetween(const Component * a,const Component * b)const;

		static bool sortOnTimeRemaining(RobotInQ * a, RobotInQ * b);

		float getBuildTime(RobotComponent::RobotType type);
		RobotComponent * getNextInQ();
		void spawnRobot(RobotComponent::RobotType robotType);

};

#endif // ROBOTCONTROLLER_H
