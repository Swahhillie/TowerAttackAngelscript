#include "CubeCollider.hpp"
#include "Object.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "RaycastHit.hpp"
#include "GeneralFunctions.hpp"

CubeCollider::CubeCollider()
{
    colliderType = Cube;

	normals.push_back(glm::vec3(1,0,0)); //right
	normals.push_back(glm::vec3(-1,0,0)); //left
	normals.push_back(glm::vec3(0,1,0));//up
	normals.push_back(glm::vec3(0,-1,0)); //down
	normals.push_back(glm::vec3(0,0,1)); //back
	normals.push_back(glm::vec3(0,0,-1)); //forward


	center = glm::vec3(0,size.y/2,0);
	size = glm::vec3(1,1,1);


	transformedNormals.push_back( glm::vec3(0,0,0));
	transformedNormals.push_back( glm::vec3(0,0,0));
	transformedNormals.push_back( glm::vec3(0,0,0));
	transformedNormals.push_back( glm::vec3(0,0,0));
	transformedNormals.push_back( glm::vec3(0,0,0));
	transformedNormals.push_back( glm::vec3(0,0,0));


}



CubeCollider::~CubeCollider()
{
    //dtor
}
void CubeCollider::onConnect(){
	transformNormals();
}

bool CubeCollider::collideWith(Collider * collider){
    if(collider->colliderType == Cube){
       // CubeCollider * cCollider = reinterpret_cast<CubeCollider*>(collider);

    }
    else if(collider->colliderType == Sphere){

    }
    return false;

}
bool CubeCollider::raycast(const Ray & ray, RaycastHit & hitInfo){
	glm::vec3 minPos = object->getTransform()->getPosition();
	minPos.x -= size.x /2;
	minPos.z -= size.z /2;
	return false;
}
bool CubeCollider::raycastALT(const Ray & ray, RaycastHit & hitInfo){

	glm::vec3 position = object->getTransform()->getPosition();
	glm::vec3 dirToCenter = ray.origin - position;
	if(glm::dot(ray.direction, dirToCenter) >= 0){
		//std::cout << "ray is going in a different direction" << std::endl;
		return false;
	}

	transformNormals();

	Plane planes[6];
	for(int i = 0; i < 6; i ++){
		planes[i] = Plane(transformedNormals[i],position + center + (transformedNormals[i] * size * .5f) );
	}

	for(int i = 0; i < 6; i ++){
		bool viable = true;
		Plane plane = planes[i];
		float enter;
		if(plane.raycast(ray, enter)){
			glm::vec3 point = ray.getPoint(enter);
			for(int j = 0; j < 6; j++){
				if(i == j) continue;

				if(glm::dot(planes[i].normal, point - planes[i].point ) >= 0){
					//point is behind plane
				}
				else{
					//point is in front of plane
					viable = false;
					break;
				}
			}
			if(viable){
				hitInfo.point = point;
				hitInfo.distance = enter;
				hitInfo.normal = transformedNormals[i];
				hitInfo.object = object;
				return true;
			}
		}
		else{
			// a ray missed one of the faces
			return false;
		}


	}
	return false;
}
void CubeCollider::transformNormals(){

	glm::mat4 rotationMatrix = object->getTransform()->getTransformation();

	for(int i = 0; i < 6; i ++){
		transformedNormals[i] = glm::vec3(rotationMatrix * glm::vec4(normals[i], 0.f));
    }
}
std::vector<glm::vec3> CubeCollider::normals;
//    corners = {
//		glm::vec3(0, 0, 0),
//		glm::vec3(1, 0, 0),
//		glm::vec3(0, 0, 1),
//		glm::vec3(1, 0, 1),
//		glm::vec3(0, 1, 0),
//		glm::vec3(1, 1, 0),
//		glm::vec3(0, 1, 1),
//		glm::vec3(1, 1, 1)
//    }
//    for(int i = 0; i < 8; i++){
//		corners[i] *= size; //scale to size;
//		conrers[i] += glm::vec3(.5f,.5f,.5f);
//    }
//    normals = {
//		glm::cross(corners[1], corners[2]), //bottem
//    }
