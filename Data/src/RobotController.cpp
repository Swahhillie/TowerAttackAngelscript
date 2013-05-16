#include "RobotController.hpp"
#include "RobotComponent.hpp"
#include <algorithm>
#include "RobotInQ.hpp"
#include "Time.hpp"
#include "ObjectBank.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "Config.hpp"
#include "Turret.hpp"
#include "Powernode.hpp"
#include "Defender.hpp"
#include "RaycastHit.hpp"
#include "Stage.hpp"
#include <time.h>
#include <algorithm>
#include "BudgetManager.hpp"
#include "Config.hpp"

RobotController::RobotController():warnedOutOfRobots(false), robotWireCutterCost(0), robotExplosiveCost(0), robotLaserTurretCost(0)
{
	//ctor
	robots.clear();
	Config & config = Config::instance();
	robotWireCutterCost = config.getSetting("robotWireCutterCost");
	robotExplosiveCost = config.getSetting("robotExplosiveCost");
	robotLaserTurretCost = config.getSetting("robotLaserTurretCost");


}

RobotController::~RobotController()
{
	//dtor
}

void RobotController::addRobot(RobotComponent * robot){
	//std::vector<RobotComponent*>::iterator it = std::find(robots.begin(), robots.end(), robot);
	assert(std::find(robots.begin(), robots.end(), robot) == robots.end());//adding robot double

	robots.push_back(robot);
	warnedOutOfRobots = false;
}
void RobotController::removeRobot(RobotComponent * robot){
	//std::vector<RobotComponent*>::iterator it = std::find(robots.begin(), robots.end(), robot);
	assert(std::find(robots.begin(), robots.end(), robot) != robots.end());//removing non existant robot
	robots.erase(std::find(robots.begin(), robots.end(), robot));
	//delete robot;
}
void RobotController::markRobotsForDestroy(){
	for(unsigned int i = 0; i < robots.size(); i ++){
		robots[i]->object->onDestroy();
		robots[i]->stop();
	}
}
void RobotController::addToQ(RobotComponent::RobotType robotType){
	if(robotQueue.size() > ROBOTQUEUEAMOUNT)return;// queu is full
	if(BudgetManager::instance().useMoney(getCost(robotType))){
        robotQueue.push_back(new RobotInQ(robotType, Time::currentTime + getBuildTime(robotType)));
	}

}
int RobotController::getCost(RobotComponent::RobotType robotType){
    int cost = 0;
    switch(robotType){
        case RobotComponent::Explosive: cost = robotExplosiveCost; break;
        case RobotComponent::WireCutter: cost = robotWireCutterCost; break;
        case RobotComponent::LaserTurret: cost = robotLaserTurretCost; break;
    }
    return cost;
}
const std::vector<RobotInQ * > & RobotController::getRobotQueue(){
	return robotQueue;
}

bool RobotController::sortOnTimeRemaining(RobotInQ * a, RobotInQ * b){
	return a->spawnTime < b->spawnTime;
}
void RobotController::update(){
	std::sort(robotQueue.begin(), robotQueue.end(), sortOnTimeRemaining);

//    std::vector<RobotInQ *>::iterator it = robotQueue.begin();
//    for( ; it != robotQueue.end();){
//        RobotInQ * r = *it;
//        if(!r->spawned && r->spawnTime < Time::currentTime){
//            //time has passed, spawn the robot and then clean it
//
//            spawnRobot(r->robotType);
//            r->spawned = true;
//            delete *it;
//            it = robotQueue.erase(it);
//        }
//        else{
//			it ++;
//        }
//    }
    for(int i = robotQueue.size() -1; i >= 0; i --){
        RobotInQ * r = robotQueue[i];
        if(!r->spawned && r->spawnTime < Time::currentTime){
            //time has passed, spawn the robot and then clean it

            spawnRobot(r->robotType);
            r->spawned = true;
            delete r;
            r = NULL;
            robotQueue.erase(robotQueue.begin() + i);
        }
    }

    for(unsigned int i = 0 ; i <  defenders.size(); i ++){
		for(unsigned int j = 0; j < defenders.size(); j++){
			if(defenders[i] == defenders[j])continue;

			Defender * def1 =  defenders[i];
			Defender * def2 =  defenders[j];
			if(def1->getDefenderType() == Defender::Powernode){
				Powernode * powernode = dynamic_cast<Powernode *>(def1);
				switch(powernode->powernodeType){
					case Powernode::Turret:
						if(def2->getDefenderType() == Defender::Turret){
							if(getDistanceBetween(def1, def2) < powernode->getPowerRange()){
								def2->powered = true;
							}
						}
						break;
					case Powernode::Laser:
						if(def2->getDefenderType() == Defender::Lasergrid){
							if(getDistanceBetween(def1, def2) < powernode->getPowerRange()){
								def2->powered = true;
							}
						}
						break;
                    default:
                        break;

				}
			}
		}
    }

}

float RobotController::getDistanceBetween(const Object * a,const Object * b)const{
    glm::vec3 aPos = a->getTransform()->getPosition();
    glm::vec3 bPos = b->getTransform()->getPosition();
    return glm::length(bPos - aPos);
}
float RobotController::getDistanceBetween(const Component * a,const Component * b)const{
    glm::vec3 aPos = a->object->getTransform()->getPosition();
    glm::vec3 bPos = b->object->getTransform()->getPosition();
    return glm::length(bPos - aPos);
}
float RobotController::getBuildTime(RobotComponent::RobotType robotType){
	float buildTime = 0;
    switch(robotType){
		case RobotComponent::WireCutter:
			Config::instance().getSetting("robotWireCutterSpawnTime", buildTime);
			break;
		case RobotComponent::Explosive:
			Config::instance().getSetting("robotExplosiveSpawnTime", buildTime);
			break;
		case RobotComponent::LaserTurret:
			Config::instance().getSetting("robotLaserTurretSpawnTime", buildTime);
			break;
    }
    return buildTime;
}
void RobotController::spawnRobot(RobotComponent::RobotType robotType){
    Object * robot = 0;
    switch(robotType){
        case RobotComponent::WireCutter:
            robot = objectBank->getRobot_wireCutter();
            std::cout << "created a robot wire cutter " <<std::endl;
            robot->getTransform()->setPosition(glm::vec3(0,0,0));
            break;
		case RobotComponent::LaserTurret:
			robot = objectBank->getRobot_laserTurret();
            std::cout << "created laser turret robot " <<std::endl;
            robot->getTransform()->setPosition(glm::vec3(0,0,0));

			break;
		case RobotComponent::Explosive:
			robot = objectBank->getRobot_explosive();
            std::cout << "created an Explosive robot " <<std::endl;
            robot->getTransform()->setPosition(glm::vec3(0,0,0));
			break;

		default: std::cout << "type not in yet "<< std::endl; break;
    }
}
void RobotController::addDefender(Defender * defender){
	assert(std::find(defenders.begin(), defenders.end(), defender) == defenders.end());

	//std::cout << "added " << defender->object->name << "to defenders " << std::endl;
	defenders.push_back(defender);
}
void RobotController::removeDefender(Defender * defender){
	assert(std::find(defenders.begin(), defenders.end(), defender) != defenders.end());
	//std::cout << "erased " << defender->object->name << "from defenders " << std::endl;
	defenders.erase(std::find(defenders.begin(), defenders.end(), defender));
}
RobotComponent * RobotController::getNearestRobot(const glm::vec3 & fromPos){
	float nearestDist = INFINITY;
	RobotComponent * nearestRobot = 0;
	for(unsigned int i = 0; i < robots.size(); i++){
		RobotComponent * r = robots[i];
		float distToR = glm::length2(fromPos - r->object->getTransform()->getPosition());
		if(distToR < nearestDist){
			nearestRobot = r;
			nearestDist = distToR;
		}
	}
	if(nearestRobot == 0 && !warnedOutOfRobots){
		std::cout<<"no robots on the map, getNearestRobot returning 0" <<std::endl;
		warnedOutOfRobots = true;
	}
	return nearestRobot;
}
RobotComponent * RobotController::getNearestVisibleRobot(const glm::vec3 & fromPos, const float & range){
	float nearestDist = INFINITY;
	RobotComponent * nearestRobot = 0;

	for(unsigned int i = 0; i< robots.size(); i++){
		RobotComponent * r = robots[i];
		glm::vec3 toPos = r->object->getTransform()->getPosition() + r->object->getCollider()->colliderOffset;
		float distToR = glm::length2(fromPos - toPos);
		if(distToR < range * range && distToR < nearestDist){
			RaycastHit hitInfo;
			Ray ray(fromPos, glm::normalize(toPos - fromPos));
			if(Stage::getInstance()->raycast(ray, hitInfo)){
				//hit something
				if(hitInfo.object == r->object){
					nearestRobot = r;
					nearestDist = distToR;
				}
			}
			else{
				// hit nothing
			}
		}
	}
	return nearestRobot;
}
Defender * RobotController::getNearestDefender(const glm::vec3 & fromPos, const float & range){
	float nearestDist = INFINITY;
	Defender * nearestDefender = 0;
	for(unsigned int i = 0; i< defenders.size(); i++){
		Defender * def = defenders[i];

		if(def->attackable == false) continue;

		assert(def->object->getCollider() != NULL);
		glm::vec3 toPos = def->object->getTransform()->getPosition() + def->object->getCollider()->colliderOffset;
		float distToR = glm::length2(fromPos - toPos);
		if(distToR < range * range && distToR < nearestDist){
			RaycastHit hitInfo;
			Ray ray(fromPos, glm::normalize(toPos - fromPos));
			if(Stage::getInstance()->raycast(ray, hitInfo, Object::DEFENDERLAYER)){
				//hit something
				if(hitInfo.object == def->object){
					nearestDefender = def;
					nearestDist = distToR;
				}
			}
			else{
				// hit nothing
			}
		}
	}
	return nearestDefender;
}

const std::vector<Defender * > & RobotController::getDefenders()const{
	return defenders;
}
const std::vector<RobotComponent *> & RobotController::getRobots()const{
	return robots;
}

void RobotController::clearQueue(){
	for(int i = robotQueue.size() -1 ; i >= 0; i--){
		delete robotQueue[i];
		robotQueue[i] = NULL;
	}
	robotQueue.clear();
}
