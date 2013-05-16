#include "Animator.hpp"
#include "Time.hpp"
#include "Object.hpp"
#include "Transform.hpp"
#include "AnimData.hpp"

Animator::Animator():state(INACTIVE),startTime(0), endTime(0), duration(0), currentPos(0)
{
	//ctor
}

Animator::~Animator()
{
	//dtor
}
void Animator::animatePosition(const glm::vec3 & startPosition, const glm::vec3 & endPosition, const glm::vec3 & startLookAtPos, const glm::vec3 & endLookAtPos, float timeToTake){
	if(state == INACTIVE){
		this->startPos = startPosition;
		this->endPos = endPosition;
		this->startLookAtPos = startLookAtPos;
		this->endLookAtPos = endLookAtPos;
		this->startTime = Time::currentTime;
		this->duration = timeToTake;
		this->endTime = startTime + timeToTake;
		state = ANIMATING_SINGLE;
	}
}
void Animator::animatePositions(const std::vector<glm::vec3> & positions, const glm::vec3 & startLookAtPos, const glm::vec3 & endLookAtPos, float timeToTake){
	if(state == INACTIVE){
		//std::cout << "starting " << animData.name << std::endl;
		this->positions = positions;
		this->startLookAtPos = startLookAtPos;
		this->endLookAtPos = endLookAtPos;
		this->startTime = Time::currentTime;
		this->duration = timeToTake;
		this->endTime = startTime + timeToTake;
		state = ANIMATING_POSITIONS;
	}
}
void Animator::animatePositions(const AnimData & animData){
	if(state == INACTIVE){
		std::cout << "starting -------------------->" << animData.name << std::endl;
		this->positions = animData.positions;
		this->startLookAtPos = animData.startLookAtPos;
		this->endLookAtPos = animData.endLookAtPos;
		this->startTime = Time::currentTime;
		this->duration = animData.timeToTake;
		this->endTime = startTime + animData.timeToTake;
		state = ANIMATING_POSITIONS;
	}
}
void Animator::update(){
	if(state == ANIMATING_SINGLE){
		Transform * tr = object->getTransform();
		float timeRemaining = endTime - Time::currentTime;

		float progress = 1 - timeRemaining / duration;
		std::cout << progress << std::endl;
		if(progress <= 1.0f){
			glm::vec3 toTravel = endPos - startPos;
			glm::vec3 lookDifference = endLookAtPos - startLookAtPos;
			tr->setPosition(startPos + toTravel * progress);
			tr->lookAt(startLookAtPos + lookDifference * progress);
		}
		else{
			state = INACTIVE;
		}
	}

	else if(state == ANIMATING_POSITIONS && positions.size() >= 2){
		Transform * tr = object->getTransform();
		float timeRemaining = endTime - Time::currentTime;

		float totalProgress = 1 - timeRemaining / duration;

		unsigned int fromIndex = totalProgress * positions.size();
		float subProgress = totalProgress * positions.size() - fromIndex;

		if(fromIndex + 1 < positions.size()){
			startPos = positions[fromIndex];
			endPos = positions[fromIndex + 1];


			glm::vec3 toTravel = endPos - startPos;
			glm::vec3 lookDifference = endLookAtPos - startLookAtPos;
			tr->setPosition(startPos + toTravel * subProgress);
			tr->lookAt(startLookAtPos + lookDifference * totalProgress);
		}
		else{
			state = INACTIVE;
		}
	}

}
