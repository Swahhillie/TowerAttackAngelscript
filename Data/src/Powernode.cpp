#include "Powernode.hpp"
#include "Config.hpp"
#include "Object.hpp"
#include "CellManager.hpp"
#include "RobotController.hpp"
Powernode::Powernode(PowernodeType type):powerRange(50.0f)
{
	//ctornsd
	requirePower = false;
    powernodeType = type;

	std::string typeString = "";
	switch(type){
		case Powernode::Turret: typeString = "powernodeTurret"; break;
		case Powernode::Laser: typeString = "powernodeLaser"; break;
		case Powernode::Main: typeString = "powernodeMain"; break;
    }
	float health;
	Config::instance().getSetting(typeString + "Range", powerRange);
	Config::instance().getSetting(typeString + "Health", health);
	initializeHealth(health);



}

Powernode::~Powernode()
{
	//dtor
	//std::cout << object->name << "Destroyed " << std::endl;

}

Defender::DefenderType Powernode::getDefenderType()const{
    return Defender::Powernode;
}
void Powernode::onDestroy(){
    object->onDestroy();
    //power down the turrets for one frame. if other powernodes are powering them they will still work since they set powering to true every frame.
	if(powernodeType == Main){
	    std::cout << "DESTROYED POWERNODE MAIN" << std::endl;
		CellManager::instance().onPowernodeMainDestroy();
	}
	//Object * emitter  = ObjectBank::instance().getParticleEmitter();
	//emitter->getTransform()->setPosition(object->getTransform()->getPosition());


}
