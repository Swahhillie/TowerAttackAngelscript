#include "Transform.hpp"
#include "GeneralFunctions.hpp"
#include <glm/glm.hpp>
Transform::Transform():transformation(glm::mat4(1.0))//, UPVECTOR(glm::vec3(0,1,0))
{
    //ctor
    //children = new std::vector<Transform*>();

    parent =NULL;
}

Transform::~Transform()
{
    //dtor
	setParent(NULL);
	parent = NULL;

    for(int i = children.size() -1; i >= 0 ; i--){
    	children[i]->object->onDestroy();
    	children[i]->setParent(NULL);
		delete children[i];
    }
    children.clear();
    //std::cout << "Destroying transform of " << object->name << this << std::endl;
    assert(object->getTransform()== this);
    delete object;
    object = NULL;
}
void Transform::update(){
	assert(object->getTransform() == this);
}
glm::vec3 Transform::getPosition()const{
    return glm::vec3(getTransformation() * glm::vec4(0,0,0,1));
}
glm::vec3 Transform::getLocalPosition()const{
    return glm::vec3(transformation[3]);
}
void Transform::translate(glm::vec3 translation){
	//std::cout << "translating through transform " <<std::endl;
	transformation = glm::translate(transformation, translation);
}
void Transform::rotate(float angle,glm::vec3 axis){
	transformation = glm::rotate(transformation, angle, axis);
}
void Transform::lookAt(const glm::vec3 & point, const glm::vec3 &  up){
	//convert world space point to local poin
	glm::vec3 localPoint = glm::vec3(getTransformation() * glm::vec4(point,1));
	transformation = glm::inverse(glm::lookAt(getLocalPosition(), localPoint, up));

}
void Transform::lookAt(const glm::vec3 & point){
	//convert world space point to local point
	//look at in local space
	transformation = glm::inverse(glm::lookAt(getLocalPosition(), point, glm::vec3(0,1,0)));

}
void Transform::scale(const glm::vec3 & scale){
	transformation = glm::scale(transformation, scale);
}
void Transform::setParent(Transform * aParent){
	//std::cout << "adding "<< this <<" transform as child of "<< aParent<< "current parent = "<< parent << std::endl;
	if(parent){
		parent -> removeChild(this);
	}
	if(aParent){

		aParent -> addChild(this);
	}

    parent = aParent;
}
void Transform::addChild(Transform * child){
    children.push_back(child);
}
void Transform::removeChild(Transform * child){
	for(unsigned int i = 0; i < children.size(); i++){
		if(children[i] == child){
			children.erase(children.begin()+i);
			return;
		}
	}
}
Transform * Transform::getParent()const{
    return parent;
}

Transform * Transform::getChild(int index){
    return children[index];
}
unsigned int Transform::getChildCount()const{
    return children.size();
}
unsigned int Transform::getChildCountTotal()const{
    unsigned int count = 1;
    for(std::vector<Transform*>::const_iterator it = children.begin(); it != children.end(); it++){
        count += (*it)->getChildCountTotal();
    }
    return count;
}
void Transform::setPosition(const glm::vec3 & pos){
    transformation[3][0] = pos.x;
    transformation[3][1] = pos.y;
    transformation[3][2] = pos.z;
}

glm::mat4 Transform::getTransformation()const{
    return parent? parent->getTransformation() * transformation : transformation;
}
void Transform::setTransformation(const glm::mat4 & transf){
	transformation = transf;
}
