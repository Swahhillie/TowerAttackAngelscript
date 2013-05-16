#include "Plane.hpp"
#include <assert.h>

Plane::Plane():normal(glm::vec3(0,1,0)), point(glm::vec3(0,0,0))
{

}

Plane::Plane(glm::vec3 inNormal_, glm::vec3 inPoint_):normal(inNormal_), point(inPoint_)
{
    //ctor
    assert(glm::length(normal) < 1.05 && glm::length(normal) > .95);
}

Plane::~Plane()
{
    //dtor
}

bool Plane::raycast(const Ray & ray, float & enter)const{
	float perpendicularDistance = glm::dot(normal,(ray.origin-point));
    enter = -(perpendicularDistance / glm::dot(normal, ray.direction));
    return true;
}
