#include "Stage.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "RaycastHit.hpp"
#include <algorithm>
#include <assert.h>

Stage::Stage()
{
	colliders.clear();
	solveCollisions = true;
	refreshColliders = false;
	lightDirection		= glm::normalize( glm::vec3( 1.0, 2.0, 2.0 ) );
}

Stage::~Stage()
{
	//dtor
}

void Stage::set( Camera * aCamera )
{
	camera = aCamera;
}

void Stage::add( Object * anObject)
{

	objects.push_back( anObject );
}

void Stage::update()
{

	for ( unsigned int i = 0; i < objects.size(); i++ ) {
		Object * object = objects[i];
		object->update();

	}
	checkCollisions();

}
void Stage::cleanup(){
	for ( unsigned int i = 0; i < objects.size(); i++ ) {
		objects[i]->cleanup();
	}
}

void Stage::removeCollider(Object * obj){
    std::vector<Collider *>::iterator it = std::find(colliders.begin(), colliders.end(), obj->getCollider());


    if(it != colliders.end()){

        colliders.erase(it);
    }

}
void Stage::draw()
{
	camera->draw();
	ShaderProgram::setLightDirection( lightDirection ); // should be in camera
	for ( unsigned int i = 0; i < objects.size(); i++ ) {
		objects[i]->draw();
	}
	camera->postDraw();
}
void Stage::addColliderToCheck(Collider * collider){
	//std::cout << collider->object->name << " collider added  to colliders " << std::endl;
	colliders.push_back(collider);
}
void Stage::checkCollisions(){
	return;
	for(unsigned int i = 0; i < colliders.size(); i++){
		Collider * collider1 = colliders[i];
		for(unsigned int j = i + 1; j < colliders.size(); j++){
			Collider * collider2 = colliders[j];
			collider1->collideWith(collider2);

		}
	}
}
bool Stage::raycast(Ray & ray, std::vector<RaycastHit> & raycastHits, int layerMask){
	//returns all hits made by the ray;
	bool hitFlag = false;
	std::vector<Collider *>::iterator it;
	for(it = colliders.begin(); it != colliders.end(); ++it){
		RaycastHit hitInfo;
		Collider * collider = *it;
		int colliderLayer = collider->object->layer;
		if(colliderLayer != layerMask && layerMask != 0 && layerMask != Object::SCENERYLAYER)continue;
		if(collider->raycast(ray, hitInfo)){
			raycastHits.push_back(hitInfo);
			hitFlag = true;
		}
	}

	if(hitFlag)std::sort(raycastHits.begin(), raycastHits.end(), sortOnDistance);
	return hitFlag;
}
bool Stage::sortOnDistance(const RaycastHit & a, const RaycastHit & b){
	return a.distance < b.distance;
}
bool Stage::raycast(Ray & ray, RaycastHit & raycastHit, int layerMask){
	//returns the nearest hit.
	std::vector<RaycastHit> hits;
	if(raycast(ray, hits)){
		raycastHit = hits[0];//nearest hit
		return true;
	}
	return false;
}
Stage * Stage::instance;
bool Stage::refreshColliders;
