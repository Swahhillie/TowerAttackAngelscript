#include "AnimData.hpp"

AnimData::AnimData():
name("unset"),
startLookAtPos(glm::vec3(0,0,0)),
endLookAtPos(glm::vec3(0,0,0)),
timeToTake(0)
{

}

AnimData::AnimData(const std::string & name_, const std::vector<glm::vec3> & positions_, const glm::vec3 & startLookAtPos_, const glm::vec3 & endLookAtPos_, float timeToTake_):
name(name_),
positions(positions_),
 startLookAtPos(startLookAtPos_),
 endLookAtPos(endLookAtPos_),
 timeToTake(timeToTake_)
{
	//ctor
}

AnimData::~AnimData()
{
	//dtor
}
