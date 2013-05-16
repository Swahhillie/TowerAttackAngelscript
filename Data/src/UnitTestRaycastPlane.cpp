#include "UnitTestRaycastPlane.hpp"
#include "GeneralFunctions.hpp"
#include "Object.hpp"
#include "Transform.hpp"
#include "RaycastHit.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "CellManager.hpp"
#include "Plane.hpp"
#include "ObjectBank.hpp"
#include "Stage.hpp"

UnitTestRaycastPlane::UnitTestRaycastPlane(Camera * cam_, Plane * plane_, ObjectBank * bank_, Stage & stage_):cam(cam_), plane(plane_),bank(bank_),stage(stage_)
{
    //ctor
    debugSphere = bank->getSphere();
    debugCube = bank->getCube();
}

UnitTestRaycastPlane::~UnitTestRaycastPlane()
{
    //dtor
}

void UnitTestRaycastPlane::execute(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            glm::vec2 screenPoint  = glm::vec2(800/5 * i, 600/5 * j);
            Ray r = cam->ScreenPointToRay(screenPoint);
            float enter = 0;
            if(plane->raycast(r, enter)){
                std::cout << "hit the plane @ " << r.getPoint(enter)<<std::endl;
                Object * c = bank->getCube();
                c->getTransform()->setPosition(r.getPoint(enter));

            }
            std::cout << r << std::endl;

        }
    }

}

void UnitTestRaycastPlane::placeCubeOnGrid(glm::vec2 mousePos){
	Ray r = cam->ScreenPointToRay(mousePos);
	float enter = 0;
	if(plane->raycast(r, enter)){
		glm::vec3 hitpoint = r.getPoint(enter);
		//if(hitpoint.x > 0 && hitpoint.x < 9 && hitpoint.z > 0 && hitpoint.z < 9) //limiting range of cube
			debugSphere->getTransform()->setPosition(hitpoint);
	}
}

void UnitTestRaycastPlane::intersectMouseWithSphere(glm::vec2 mousePos){
	Ray ray = cam->ScreenPointToRay(mousePos);
	RaycastHit raycastHit;
	Collider * collider = debugSphere->getCollider();

	if(collider->raycast(ray, raycastHit)){
		std::cout << "hit raycast against shpere" << std::endl;
		debugCube->getTransform()->setPosition(raycastHit.point);
	}
}
void UnitTestRaycastPlane::detectWalls(glm::vec2 mousePos){
	Ray ray = cam->ScreenPointToRay(mousePos);
	RaycastHit raycastHit;
	if(stage.raycast(ray, raycastHit)){
		debugCube->getTransform()->setPosition(raycastHit.point);
	}
}
