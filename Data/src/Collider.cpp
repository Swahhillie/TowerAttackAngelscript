

#include "Collider.hpp"
#include "Object.hpp"
#include "Stage.hpp"
#include "RaycastHit.hpp"
#include "Ray.hpp"

Collider::Collider()
{
    //ctor
    isTrigger = true;
    radius = .5;
    //new collider created, update the list of colliders

    colliderOffset = glm::vec3(0,0,0);
    colliderType = Sphere;


}

Collider::~Collider()
{
    //dtor
    //std::cout << "collider destroyed " << std::endl;
}
void Collider::onConnect(){
	Stage::getInstance()->addColliderToCheck(this);
}
void Collider::update(){

}
bool Collider::raycast(const Ray & ray, RaycastHit & hitInfo){
	return false;
}
bool Collider::collideWith(Collider * collider){
    return false;
}

void Collider::EnterCollision(Collider * collider){
    if(!colliding){
        colliding = true;
        object->onCollisionEnter(collider);
    }
}

void Collider::ExitCollision(Collider * collider){
    if(colliding){
        colliding = false;
        object->onCollisionExit(collider);
    }
}
