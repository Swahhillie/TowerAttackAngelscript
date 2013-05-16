#include "Turret.hpp"
#include "RobotController.hpp"
#include "RobotComponent.hpp"
#include "Config.hpp"
#include "Object.hpp"
#include "Time.hpp"
#include "RaycastHit.hpp"
#include "Ray.hpp"
#include "GeneralFunctions.hpp"
#include "RenderMaterial.hpp"
#include "Stage.hpp"

Turret::Turret(TurretType type):typeString("")
{
	//ctor
	controller = &RobotController::instance();
	requirePower = true;
	powered = false;
	turretType = type;

	Config * config = &Config::instance();
	config->getSetting("turretMediumShotsPerSecond", shotsPerSecond);
	config->getSetting("turretMediumDamagePerShot", damagePerShot);
	config->getSetting("turretMediumRange", range);
	lastShotTime = 0;

	switch(type){
        case Heavy: typeString = "Heavy"; break;
        case Medium: typeString = "Medium"; break;
        case Light: typeString = "Light"; break;
	}

	std::string sps = "turret" + typeString + "ShotsPerSecond";
	std::string dps = "turret" + typeString + "DamagePerShot";
	std::string rng = "turret" + typeString + "Range";
	std::string hp = "turret" + typeString + "MaxHealth";
	shotSound = "laserPulse" + typeString + "Wav";

    float mh;
	config->getSetting(sps, shotsPerSecond);
	config->getSetting(dps, damagePerShot);
	config->getSetting(rng, range);
	config->getSetting(hp, mh);

	initializeHealth(mh);
}
Turret::~Turret()
{
	//dtor

	//delete debugCube->getTransform();//->onDestroy();
}
void Turret::onDestroy(){
    Defender::onDestroy();
}

void Turret::update(){
	//target = controller->getNearestRobot(object->getTransform()->getPosition());
	if(requirePower && !powered)return;


	target = controller->getNearestVisibleRobot(object->getTransform()->getPosition(), range);
	if(target){
		glm::vec3 targetPosition = target->object->getTransform()->getPosition();
		glm::vec3 thisPosition = object->getTransform()->getPosition();
		glm::vec3 dirToTarget =  targetPosition - thisPosition;
		dirToTarget.y = 0;
		if(glm::length2(dirToTarget) < range * range){
			prepareShotAtTarget(dirToTarget);
			rotateToDirection(dirToTarget);
		}
	}
	powered = false;

}
void Turret::rotateToDirection(const glm::vec3 & direction){
	glm::vec3 pos = object->getTransform()->getPosition();
	object->getTransform()->lookAt(pos - direction);
	//glm::mat4 newMatrix = glm::translate(glm::mat4(1.0f), pos);
//	newMatrix[0] = glm::vec4(0.0f,0.0f,1.0f,0.0f);//glm::vec4(glm::normalize(direction), 0.0f);
//	newMatrix[1] = glm::vec4(1.0f,0.0f,0.0f,0.0f);
//	newMatrix[2] = glm::vec4(0.0f,1.0f,0.0f,0.0f);//glm::vec4(glm::normalize(glm::cross(direction, glm::vec3(0,1,0))), .0f);


	//Ray ray(object->getTransform()->getPosition(), glm::normalize(direction));
}
void Turret::prepareShotAtTarget(const glm::vec3 & dirToTarget){
	float timeSinceLastShot = Time::currentTime - lastShotTime;
	float shotInterval = 1.0f  / shotsPerSecond;
	if(timeSinceLastShot > shotInterval){
		shootAtTarget(dirToTarget);
	}
}
void Turret::shootAtTarget(const glm::vec3 & dirToTarget){
	object->getSound()->playOnce(shotSound);
	lastShotTime = Time::currentTime;
	Ray ray(object->getTransform()->getPosition(), glm::normalize(dirToTarget));

	RaycastHit hitInfo;
	if(Stage::getInstance()->raycast(ray, hitInfo)){
		RobotComponent * robo = hitInfo.object->getRobotComponent();
		if(robo){
			robo->changeHealth(-damagePerShot);

		}
	}
	std::cout << "-pew-";
}
Defender::DefenderType Turret::getDefenderType()const{
    return Defender::Turret;
}
Turret::TurretType Turret::getTurretType()const{
    return turretType;
}
