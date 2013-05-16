#include "Defender.hpp"
#include "Object.hpp"
#include "RobotController.hpp"
#include "RenderMaterial.hpp"
#include "ObjectBank.hpp"

Defender::Defender():powered(false), requirePower(false)
{
	//ctor

}

Defender::~Defender()
{
	//dtor
	RobotController::instance().removeDefender(this);


	std::cout << "remove defender called for " << this->object->name << std::endl;;
}
void Defender::onDestroy(){
	object->onDestroy();
	//std::cout << "player destroyed a defender object " << std::endl;
	//std::cout << "Spawning emitter on dead object" << std::endl;
	//Object * emitter  = ObjectBank::instance().getParticleEmitter();
	//emitter->getTransform()->setPosition(object->getTransform()->getPosition());
}
void Defender::onConnect(){
	RobotController::instance().addDefender(this);
}

void Defender::initializeHealth(float mh){
	setMaxHealth(mh);
	setCurrentHealth(mh);
}
