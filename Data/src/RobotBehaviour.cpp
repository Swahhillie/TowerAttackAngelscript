#include "RobotBehaviour.hpp"
#include "RobotComponent.hpp"
#include "RobotController.hpp"
#include <glm/glm.hpp>
#include "Transform.hpp"
#include "Time.hpp"
#include "Cell.hpp"
#include "CellManager.hpp"
#include "Destructable.hpp"
#include "Defender.hpp"
#include "Ray.hpp"
#include "Stage.hpp"
#include "RaycastHit.hpp"
#include "GeneralFunctions.hpp"

RobotBehaviour::RobotBehaviour():manager(CellManager::instance()),behaviourState(Idle)
{
    current = NULL;
    target = NULL;
    destination = NULL;
    tr = NULL;
    attackTarget = NULL;

}

RobotBehaviour::~RobotBehaviour()
{
    //dtoraa
    if(current)current->occupy(false);
}
RobotBehaviour::RobotBehaviour(const RobotBehaviour & other):manager(CellManager::instance()){
	this->current = other.current;
	this->target = other.target;
	this->destination = other.destination;
	this->tr = other.tr;
	this->attackTarget = other.attackTarget;
	this->behaviourState = other.behaviourState;
}
RobotBehaviour & RobotBehaviour::operator = (const RobotBehaviour & other){
	if(this == &other)return *this;

	this->current = other.current;
	this->target = other.target;
	this->destination = other.destination;
	this->tr = other.tr;
	this->attackTarget = other.attackTarget;
	this->behaviourState = other.behaviourState;
	delete &other;
	return *this;
}
void RobotBehaviour::update(RobotComponent & robot){
	//move or attack based on the current state of this robot
	tr = robot.object->getTransform();
	getCurrent(tr);
	assert(tr != NULL);
	if(current == NULL) return; // map hasn't loaded yet

	if(behaviourState == MovingDirect){

		assert(target != NULL && destination != NULL); // if target or destination is null the robot should not be in this state.
		moveToTarget(robot, tr);
	}
	if(behaviourState == Idle){
		if(current != current->lowestNeighbour()){
			followMap();
		}
	}

	if(behaviourState == Attacking){
		if(checkForAdjacentEnemies(tr, robot)){
			attack(tr, robot);
		}
		else{
			behaviourState = MovingAlongMap;
		}
	}
	else if(behaviourState == MovingAlongMap){
		if(target == NULL){
			onReachTarget();
		}
		moveToTarget(robot, tr);
		if(checkForAdjacentEnemies(tr, robot)){
			behaviourState = Attacking;
		}
	}

}
void RobotBehaviour::getCurrent(Transform * tr){

	Ray ray(tr->getPosition()+glm::vec3(0,1,0), glm::vec3(0,-1,0));
    Cell * cell = manager.getCell(ray);
    if(cell){
        if(cell != current){
            //when the robot passes over to a new cell
            if(current != NULL){
                //current->changeColor(glm::vec4(1,1,1,1));
                current->occupy(false);
            }
        }
        //cell->changeColor(glm::vec4(0,1,0,1));
        cell->occupy(true);
        current = cell;
    }
    else{
		current = NULL;
    }
}
void RobotBehaviour::moveToTarget(RobotComponent & robot, Transform * tr){
    assert(target != NULL); //can't move to the target if we dont have it

	glm::vec3 direction = target->getPosition() - tr->getPosition();
	float distanceToTravel = Time::deltaTime * robot.getMoveSpeed();

	if(glm::length2(direction) < distanceToTravel * distanceToTravel || target->getOccupied()){
		//reached the target position;
		onReachTarget();
		return;
	}
	direction = glm::normalize(direction) * distanceToTravel;

    /*
	Ray ray(tr->getPosition(), glm::normalize(direction));
	RaycastHit hitInfo;
	if(Stage::getInstance()->raycast(ray, hitInfo)){
		if(hitInfo.distance < distanceToTravel){
			//distance to obstacle is less than the next move. dont move to prevent intersection

			//!!!!!! currently gets robots stuck when they drive into eachother-
			//return;
		}
	}
	*/
	robot.move(direction);
	robot.rotateTo(direction);
}
void RobotBehaviour::onReachTarget(){
	//target is reached. if there are waypoints go after the next target. Else reached destination. for now only 1 target
	if(behaviourState == MovingAlongMap){
		Cell * lowestNeighbour = current->lowestNeighbour();
		if(current == lowestNeighbour){
			behaviourState = Idle;
			target = NULL;
		}
		else{
			target = lowestNeighbour;
		}
	}
	if(behaviourState == MovingAlongMap) assert(target != NULL);



}
bool RobotBehaviour::checkForAdjacentEnemies(Transform * tr, RobotComponent & robot){
	attackTarget = NULL;
	attackTarget = RobotController::instance().getNearestDefender(tr->getPosition(), robot.range);
	if(attackTarget) return true;
	else return false;
//	for(unsigned int i =0 ; i < current->neighbours.size(); i++){
//		Cell * neighbour = current->neighbours[i];
//		if(neighbour->getDestructable()){
//			attackTarget = neighbour->getDestructable();
//			return true;
//		}
//	}
//	return false;
}
void RobotBehaviour::attack(Transform * tr, RobotComponent & robot){
	float shotInterval = 1.0f / robot.shotsPerSecond;
	if(robot.lastShotTime + shotInterval < Time::currentTime){
		robot.lastShotTime = Time::currentTime;
		attackTarget->changeHealth(-robot.damagePerShot);
		robot.playAttackSound();
		if(robot.getRobotType()== RobotComponent::Explosive)robot.onDestroy();
	}
}
bool RobotBehaviour::setDestination(Cell * cell){
	assert(cell != 0);
	destination = cell;
	target = destination; //for now move directly to the target
	behaviourState = MovingDirect;
	return true; // if there is no path. return false here. for later
}
void RobotBehaviour::followMap(){

	behaviourState = MovingAlongMap;
}
