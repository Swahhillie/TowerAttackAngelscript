#include "SkyboxRotation.hpp"
#include "Object.hpp"

SkyboxRotation::SkyboxRotation(Transform * tr_):tr(tr_)
{
	//ctor
}

SkyboxRotation::~SkyboxRotation()
{
	//dtor
}
void SkyboxRotation::update(){
	//brin the cube to the camera
	object->getTransform()->setPosition(tr->getPosition());
//	tr -> rotate(90.0f * Time::deltaTime, glm::vec3(0.0f,1.0f,0.0f));
}
