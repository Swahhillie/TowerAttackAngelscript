#include <sfml/window.hpp>
#include <glm/glm.hpp>


#include "Time.hpp"
#include "GeneralFunctions.hpp"
#include "Collider.hpp"
#include "Component.hpp"
#include "Object.hpp"
#include "Sound.hpp"
#include "GeneralFunctions.hpp"


Component::Component():object(NULL)
{
	//ctor

}

Component::~Component()
{
	//dtor/d

}

void Component::update()
{
	//object->getTransform()->transformation = glm::rotate( object->getTransform()->transformation, 45*Time::deltaTime, glm::vec3( 0.1f, 1.0f, 0.3f ) );
}
void Component::onConnect(){

}
void Component::onCollisionEnter(Collider * collider){
    //this transmits the collider to all components
}
void Component::onCollisionExit(Collider * collider){

}
