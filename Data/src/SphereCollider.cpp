#include "SphereCollider.hpp"
#include "Object.hpp"
#include "GeneralFunctions.hpp"
#include "RaycastHit.hpp"
#include <math.h>

SphereCollider::SphereCollider()
{
	radius = 0.6f;
	colliderOffset = glm::vec3(0,.5f,0);
	colliderType = Sphere;
}

SphereCollider::~SphereCollider()
{
	//dtor
}

bool SphereCollider::raycast(const Ray & ray, RaycastHit & hitInfo){
//Compute A, B and C coefficients

	//adapted from http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection

	assert(object != NULL);

	glm::vec3 position = object->getTransform()->getPosition();
	glm::vec3 directionToSphere = ray.origin - position - colliderOffset;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot( directionToSphere, ray.direction);
    float c = glm::dot(directionToSphere, directionToSphere) - (radius * radius);

    //Find discriminant
    float disc = b * b - 4 * a * c;

    // if discriminant is negative there are no real roots, so return
    // false as ray misses sphere
    if (disc < 0)
        return false;

    // compute q as described above
    float distSqrt = sqrtf(disc);
    float q;
    if (b < 0)
        q = (-b - distSqrt)/2.0;
    else
        q = (-b + distSqrt)/2.0;

    // compute t0 and t1
    float t0 = q / a;
    float t1 = c / q;

    // make sure t0 is smaller than t1
    if (t0 > t1)
    {
        // if t0 is bigger than t1 swap them around
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative direction
    // and consequently the ray misses the sphere
    if (t1 < 0)
        return false;

    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0)
    {
    	//hit from the inside out, return false to make more sense;
    	return false;
        hitInfo.distance = t1;
        hitInfo.point = ray.getPoint(t1);
        hitInfo.normal = (hitInfo.point - position) / radius;
        hitInfo.object = object;
        return true;
    }
    // else the intersection point is at t0
    else
    {
        hitInfo.distance = t0;
        hitInfo.point = ray.getPoint(t0);
        hitInfo.normal = (hitInfo.point - position) / radius;
        hitInfo.object = object;
        return true;
    }
}
bool SphereCollider::collideWith(Collider * collider){
	if(collider->colliderType == Sphere){
		SphereCollider * sCollider = reinterpret_cast<SphereCollider*>(collider);
		Transform * colliderTransform = sCollider -> object -> getTransform();
		glm::vec3 sPos = colliderTransform -> getPosition();
		glm::vec3 thisPos = object -> getTransform() -> getPosition();

		glm::vec3 dir = sPos - thisPos;
        float distance = glm::length(dir);
        float sumRadius = sCollider->radius + radius;
		if(distance < sumRadius){
			if(!isTrigger){
				float overlap = sumRadius - distance;
				glm::normalize(dir);
				dir *= overlap;
				colliderTransform->setPosition(colliderTransform->getPosition() + dir);
			}

            EnterCollision(collider);
            return true;
		}
		else{
            ExitCollision(collider);
		}
	}
	return false;
}
