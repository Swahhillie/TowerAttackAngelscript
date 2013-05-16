#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{
    public:
        Ray(glm::vec3 origin, glm::vec3 direction);
        virtual ~Ray();

        glm::vec3 origin;
        glm::vec3 direction;
        glm::vec3 getPoint(float distance) const;

    protected:
    private:
};

#endif // RAY_H
