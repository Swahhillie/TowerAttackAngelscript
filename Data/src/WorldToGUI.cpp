#include "WorldToGUI.hpp"
#include "WorldToGUIMessage.hpp"
#include "CellManager.hpp"
#include "RobotController.hpp"
#include "Defender.hpp"
#include "Turret.hpp"
#include "Powernode.hpp"
#include "RobotComponent.hpp"
#include "Object.hpp"
#include <sstream>
#include <iomanip>
#include <sfml/graphics.hpp>
#include "Camera.hpp"
#include "Stage.hpp"
#include "Ray.hpp"
#include "RaycastHit.hpp"
#include "Controller.hpp"

WorldToGUI::WorldToGUI():offset(glm::vec3(0,2,0)),robotController(RobotController::instance())
{
	//ctor
}

WorldToGUI::~WorldToGUI()
{
	//dtor
}
void WorldToGUI::update(){
	toDraw.clear();
	pointAtTooltip();
    levelSpecific();
	const std::vector<Defender*> defenders = robotController.getDefenders();
	for(unsigned i = 0 ; i < defenders.size(); i++){
		const Defender * def = defenders[i];
		std::stringstream sstream;
		if(def->getDefenderType() == Defender::Lasergrid) continue; // don't make a message for lasergrids
		//if(def->getDefenderType() == Defender::Powernode)
			//addPowernodeMessage(def);


		sstream << def->getHealthRepresentation();

		glm::vec3 pos = def->object->getTransform()->getPosition();
		pos += offset;
		toDraw.push_back(WorldToGUIMessage(sstream.str(), pos, sf::Color::Red));

	}

	const std::vector<RobotComponent*> robots = robotController.getRobots();
	for(unsigned i = 0 ; i < robots.size(); i++){
		const RobotComponent * robot = robots[i];
		std::stringstream sstream;
		sstream << robot->getHealthRepresentation();

		glm::vec3 pos = robot->object->getTransform()->getPosition();

		pos += offset;
		toDraw.push_back(WorldToGUIMessage(sstream.str(),pos, sf::Color::Green));
	}
}
const std::vector<WorldToGUIMessage> & WorldToGUI::getStringsToDraw()const{
	return toDraw;
}
void WorldToGUI::addPowernodeMessage(const Defender * def){
	std::stringstream ss;
	Powernode * pn = (Powernode*) def;
	if(pn->powernodeType == Powernode::Main){
		ss << "Destroy this powernode to advance to the next level ";
	}
	else if(pn->powernodeType == Powernode::Laser)
		ss << "Destroy this to disable the laser";
	else if(pn->powernodeType == Powernode::Turret)
		ss << "Destroy this to disable the turrets";

	glm::vec3 pos = def->object->getTransform()->getPosition();
	pos += offset + offset;
	toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow, 20));
}
void WorldToGUI::pointAtTooltip(){
	Ray ray = Camera::main->ScreenPointToRay(Controller::mousePosition);
	RaycastHit hitInfo;
	if(Stage::getInstance()->raycast(ray, hitInfo)){
		std::stringstream ss("");
		bool foundSomething = false;
		if(hitInfo.object->getComponent("Powernode")){
			Powernode * pn = (Powernode *)(hitInfo.object->getComponent("Powernode"));
			switch(pn->powernodeType){
				case Powernode::Turret: ss << "Turrer Powernode"; break;
				case Powernode::Main: ss << "Main Powernode"; break;
				case Powernode::Laser: ss << "Lasergrid Powernode"; break;
			}
			foundSomething =true;
		}
		else if(hitInfo.object->getComponent("Turret")){
		    Turret * tur = (Turret*) (hitInfo.object->getComponent("Turret"));
		    switch(tur->getTurretType()){
                case Turret::Heavy: ss << "Heavy Turret"; break;
                case Turret::Medium: ss << "Medium Turret"; break;
                case Turret::Light: ss << "Light Turret"; break;
		    }
			foundSomething =true;
		}
		else if(hitInfo.object->getComponent("Lasergrid")){
			ss<<"Lasergrid";
			foundSomething =true;
		}
		else if(hitInfo.object->getComponent("RobotComponent")){
			RobotComponent * robot = (RobotComponent *)(hitInfo.object->getComponent("RobotComponent"));
			switch(robot->getRobotType()){
				case RobotComponent::WireCutter: ss << "Wirecutter Robot"; break;
				case RobotComponent::Explosive: ss << "Explosive Robot"; break;
				case RobotComponent::LaserTurret: ss << "Laser Turret Robot"; break;
			}
			foundSomething =true;
		}

		if(foundSomething)toDraw.push_back(WorldToGUIMessage(ss.str(), hitInfo.point, sf::Color::Yellow, 20));

	}
}
void WorldToGUI::levelSpecific(){
    int currentLevel = CellManager::instance().getCurrentLevel()->levelNumber;
    std::stringstream ss;
    glm::vec3 pos;
    switch(currentLevel){
        case 0:
            ss << "Destroy this main powernode\nso to go to the next level";
            pos =glm::vec3(7,0,7);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

        case 1:
            ss << "Destroy the laser powernode\nto pass this laser";
            pos =glm::vec3(10,0,4);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

        case 2:
            ss << "Destroy the turret first!";
            pos =glm::vec3(11,0,11);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

        case 3:
            ss << "Destroy the turret powernode\nto cut power from the turrets";
            pos =glm::vec3(10,0,6);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

        case 4:
            ss << "Destoy the turret power to get to the lasergrid power";
            pos =glm::vec3(8,0,8);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

        case 5:
            ss << "This turret does more damage per shot, but shoots slower";
            pos = glm::vec3(8,0,8);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

        case 6:
            //challenge level, no hints

        case 7:


        case 8:
            //challenge level, no hints
            ss << "This turret does a LOT damage per shot, but shoots really slowly";
            pos = glm::vec3(13,0,3);
            toDraw.push_back(WorldToGUIMessage(ss.str(), pos, sf::Color::Yellow));
            break;

            break;
        case 9:
            //optional
            break;
    }
}
