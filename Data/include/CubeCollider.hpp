#ifndef CUBECOLLIDER_HPP
#define CUBECOLLIDER_HPP

#include "Collider.hpp"
#include <vector>

class CubeCollider : public Collider
{
    public:
        CubeCollider();
        virtual ~CubeCollider();
        virtual bool collideWith(Collider* collider);
        virtual bool raycast(const Ray & ray, RaycastHit & hitInfo);
        virtual bool raycastALT(const Ray & ray, RaycastHit & hitInfo);
        glm::vec3 center;
        glm::vec3 size;
		virtual const std::string getName(){return "CubeCollider";}
        virtual void onConnect();
    protected:
    private:
		static std::vector<glm::vec3> normals;
		std::vector<glm::vec3> transformedNormals;
		void transformNormals();

};

#endif // CUBECOLLIDER_HPP
