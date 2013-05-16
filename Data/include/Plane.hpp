#ifndef PLANE_H
#define PLANE_H
#include <glm/glm.hpp>
#include "Ray.hpp"

class Plane
{
    public:
		Plane();
        Plane(glm::vec3 inNormal, glm::vec3 inPoint);
        bool raycast(const Ray & r, float & enter)const;
        glm::vec3 normal;
        glm::vec3 point;
        virtual ~Plane();
    protected:
    private:
};

#endif // PLANE_H
