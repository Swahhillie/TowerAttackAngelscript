#include "Ray.hpp"
#include <assert.h>
#include <cmath>

Ray::Ray(glm::vec3 origin_, glm::vec3 direction_):origin(origin_), direction(direction_)
{
    //ctor
    direction = glm::normalize(direction);
    //assert( abs(glm::length(direction) - glm::length(glm::normalize(direction)) < .05f));
}

Ray::~Ray()
{
    //dtor
}
glm::vec3 Ray::getPoint(float distance) const{
    glm::vec3 out = origin + direction * distance;
    return out;
}
