#include "RobotComponent.hpp"
#include <glm/glm.hpp>
#include "Time.hpp"
#include "Cell.hpp"
#include "GeneralFunctions.hpp"
#include "CellManager.hpp"
#include "RobotController.hpp"
#include "RenderMaterial.hpp"
#include "Config.hpp"
#include "Camera.hpp"

RobotComponent::RobotComponent(RobotType robotType): buildTime(5.0f), moveSpeed(3.0f), lastShotTime(0.0f)
{
    //ctor
    this->robotType = robotType;
    std::string robotTypeString = "";
    switch(robotType){
		case WireCutter:	robotTypeString = "robotWireCutter"; break;
		case LaserTurret:	robotTypeString = "robotLaserTurret";break;
		case Explosive: 	robotTypeString = "robotExplosive";break;
    }

	float mh;
	std::string varName = robotTypeString + "Health";
	Config::instance().getSetting(varName, mh);
	initializeHealth(mh);

	varName = robotTypeString + "Speed";
	Config::instance().getSetting(varName, moveSpeed);

	 varName = robotTypeString + "ShotsPerSecond";
	Config::instance().getSetting(varName, shotsPerSecond);

	varName = robotTypeString + "Damage";
	Config::instance().getSetting(varName, damagePerShot);

	varName = robotTypeString + "Range";
	Config::instance().getSetting(varName, range);

	attackSound = robotTypeString + "AttackSound";
	varName = robotTypeString + "SoundDuration";
	Config::instance().getSetting(varName,  soundDuration);



	//initializeHealth(mh);

}

RobotComponent::~RobotComponent()
{
	//delete behaviour;
	//behaviour = NULL;
    RobotController::instance().removeRobot(this);
}

void RobotComponent::onConnect(){
	tr = object->getTransform();
	RobotController::instance().addRobot(this);
}
void RobotComponent::move(glm::vec3 translation){
	tr->setPosition(tr->getPosition()+translation);
}
void RobotComponent::rotateTo(glm::vec3 direction){
	glm::mat4 rotationMatrix = glm::lookAt(tr->getPosition(), tr->getPosition() + direction, glm::vec3(0,1,0));
	tr->setTransformation(glm::inverse(rotationMatrix));
}
void RobotComponent::followMapPath(){
	behaviour.followMap();
}
bool RobotComponent::moveTo(Cell * cell){
	return(behaviour.setDestination(cell));

}
void RobotComponent::update(){
    behaviour.update(*this);
}
void RobotComponent::stop(){
    std::cout << "ROBOT WILL GET DESTROYED!"<< std::endl;
}
void RobotComponent::setRobotBehaviour(RobotType behaviourType){
    /*
    switch(behaviourType){
        case WireCutter:
            behaviour = new RobotBehaviour();
            break;
        case LaserTurret:
            behaviour = RobotBehaviour();
            break;
		case Explosive:
			behaviour = RobotBehaviour();
            break;
    }
    */
}

float RobotComponent::getMoveSpeed(){
    return moveSpeed;
}
void RobotComponent::onDestroy(){
	object->onDestroy();
}
void RobotComponent::initializeHealth(float mh){

	setMaxHealth(mh);
	setCurrentHealth(mh);
}
void RobotComponent::playAttackSound(){
    if(lastSound + soundDuration < Time::currentTime){
        std::cout << " should play a sound --------------------"  << std::endl;
        if(object->getSound()){
            object->getSound()->playOnce(attackSound);
            playingSound = true;
            lastSound = Time::currentTime;
        }
    }
}
float RobotComponent::getBuildTime()const{
    return buildTime;
}
RobotComponent::RobotType RobotComponent::getRobotType()const{
	return robotType;
}
