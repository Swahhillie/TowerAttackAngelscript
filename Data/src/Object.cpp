#include "ShaderProgram.hpp"
#include "Object.hpp"
#include "Body.hpp"
#include "Collider.hpp"
#include "Component.hpp"
#include "GeneralFunctions.hpp"
#include "Time.hpp"
#include "SphereCollider.hpp"
#include "Transform.hpp"
#include "RobotComponent.hpp"
#include "CellManager.hpp"
#include "Stage.hpp"
#include "CubeCollider.hpp"
#include <typeinfo>

Object::Object() {
    body = NULL;
    name = "GameObject";
    collider = NULL;
    camera = NULL;
    transform = NULL;
    transform = new Transform();
    addComponent(transform);
    hasCollider = false;
    audioSource = NULL;
    renderMaterial = NULL;
    robotComponent = NULL;
    markForDelete = false;
    layer = 1;
}

Object::~Object() {
    //dtor
    if(markForDelete == false){
		std::cout << name << " was deleted without mark for delete -------------------------------" << std::endl;
    }
    assert(markForDelete == true);
    //std::cout <<"DESTROYING OBJECT " << name << std::endl;
    for(unsigned int i = 0 ; i < components.size(); i++){
		Component * component = components[i];
		assert(component != NULL);
		std::string compName = component->getName();

		if(compName == "Body"){
			//std::cout << "Not ";
			body = NULL;
		}
		else if(compName == "Transform"){
			//std::cout<< "Not ";
			transform->object = NULL;
			transform = NULL;
			//transform deletes itself
		}
		else if(compName == "Collider" || compName == "SphereCollider"){
			Stage::getInstance()->removeCollider(this);
			//std::cout << "removing from stage and ";
			delete collider;
			collider = NULL;
		}
		else if(compName == "Cell"){

		}
		else{
			if(compName != "RenderMaterial")std::cout << "	DEL:"<<compName << std::endl;
			delete component;
			component = NULL;
		}
		//std::cout << "destroying "<< compName << " component" << std::endl;
    }
    components.clear();
    componentsMap.clear();
    //extra debug, shouldn't do anything if all is fine

    //std::cout <<"FINISHED DESTRUCTION OF OBJECT " << name << std::endl;
}
void Object::onDestroy(){
	//std::cout << "object marked for deletion "<< std::endl;
	markForDelete = true;
}
void Object::setBody( Body * aBody ) {
    body = aBody;
    //addComponent(body);
}

void Object::update() {
	assert(transform != NULL);
    for(unsigned int i = 0; i < components.size(); ++i) {
        Component * component = components[i];
        assert(component != NULL);
        //std::cout << i  << " behavior update "<< behavior -> behaveName << std::endl;
        //std::cout << "behaviour " << behavior<< std::endl;

        component->update();
    }
    //if(markForDelete)return;
    for(int i = 0; i < transform->getChildCount(); ++i) {
        Transform * child = transform->getChild(i);
        child->object->update();
    }

}
void Object::cleanup(){
    for (int i= transform->getChildCount()-1; i>=0; i--) {
        Object * childObject = transform->getChild(i)->object;
        if(this->markForDelete){
            childObject->markForDelete = true;
        }
        childObject->cleanup();
    }
    if(this->markForDelete){
       // std::cout << "  something"  << std::endl;
       delete this->transform;
    }
//    this->markForDelete = false;
    return;

/*
	bool cleanedSomething = false;
	int cCount = transform->getChildCount();
	for(int i = 0; i < cCount; i++){
		assert(cCount == transform->getChildCount());
		Object * childObject = transform->getChild(i)->object;
		bool toDelete = childObject->markForDelete;
		if(toDelete){
			//std::cout << i << std::endl << "deleting a "<< childObject->name << " from " << name << std::endl;
			delete transform->getChild(i);//this will change the child count
			cCount = transform->getChildCount();
			cleanedSomething = true;
		}
		else{
			childObject->cleanup();
		}
	}
	if(cleanedSomething) std::cout << "cleaned a child(ren) from " << name << std::endl;
	*/
}

void Object::draw() {
    for(int i = transform->getChildCount() - 1; i >= 0 ; --i) {
        Object * child = transform->getChild(i)->object;
        child->draw();
    }

    if ( renderMaterial ) {
//        if(transform->getParent()) {
//            ShaderProgram::setModelMatrix(transform->getParent()->getTransformation() * transform->getTransformation());
//            renderMaterial->draw();
//        } else {
            ShaderProgram::setModelMatrix( transform->getTransformation()); // glUniform....
            renderMaterial->draw();
//        }


    }

}


bool Object::addComponent(Component * behavior) {

    for(unsigned int i = 0; i < components.size(); ++i) {
        if(components[i] == behavior) {
            return false; // already a component of this type on the object
        }
    }
    //no components of this type on the object. add it to the components and return succesful
    componentsMap.insert(std::pair<const std::string, Component*>(behavior->getName(), behavior));
    components.push_back(behavior);
    behavior->object = this;
    behavior->onConnect();
    return true;
}
Component * Object::getComponent(std::string behaveName) {
    std::map<const std::string, Component*>::const_iterator it;
    it = componentsMap.find(behaveName);
    if(it == componentsMap.end()) {
        return NULL;
    }
    else{
		return it->second;
    }

}
Body * Object::getBody()const {
    return body;
}
Collider * Object::getCollider()const {
    return collider;
}
RenderMaterial * Object::getRenderMaterial(){
	return renderMaterial;
}
void Object::addRenderMaterial(){
	renderMaterial = new RenderMaterial();
	addComponent(renderMaterial);
}
void Object::addCollider() {
    assert(collider == NULL);
    collider = new SphereCollider();
    addComponent(collider);
    hasCollider = true;
    Stage::refreshColliders = true;
}
Camera * Object::addCamera(Camera * cam) {
    this -> camera = cam;
    addComponent(camera);
    return camera;
}
Camera* Object::getCamera()const {
    return camera;
}
Transform * Object::getTransform()const{
    return transform;
}

std::ostream & operator << (std::ostream & out,const Object & object) {
    out << "object " << object.name;
    return out;
}
void Object::onCollisionEnter(Collider * collider) {
	std::cout << "collision entered by " << name << "against " << collider->object->name << std::endl;
    for(unsigned int i = 0; i < components.size(); i++)components[i]->onCollisionEnter(collider);
}
void Object::onCollisionExit(Collider * collider) {
    for(unsigned int i = 0; i < components.size(); i++){
    	assert(components[i] != NULL);
    	components[i]->onCollisionExit(collider);
    }
}

void Object::addSound(Sound * sound)
{
    this->audioSource = sound;
    addComponent(sound);
}

Sound * Object::getSound()
{
    return audioSource;
}
RobotComponent * Object::addRobotComponent(RobotComponent::RobotType type){
	assert(robotComponent == 0); //can't add multiple components of the same type
	robotComponent = new RobotComponent(type);
	addComponent(robotComponent);
	return robotComponent;
}
RobotComponent * Object::getRobotComponent(){
	return robotComponent;
}
