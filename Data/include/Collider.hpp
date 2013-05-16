#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.hpp"
class RaycastHit;
class Ray;

class Collider : public Component
{
    public:
		enum ColliderType{
			Sphere,
			Cube
		};
        Collider();
        virtual ~Collider();
        virtual void update();
        virtual bool collideWith(Collider * collider);
        bool colliding;
        void onConnect();
        bool isTrigger;
        float radius;
        ColliderType colliderType;
        glm::vec3 colliderOffset;
        virtual bool raycast(const Ray & ray, RaycastHit & hitInfo);
        virtual const std::string getName(){return "Collider";}
    protected:
        void EnterCollision(Collider * collider);
        void ExitCollision(Collider * collider);
    private:
};

#endif // COLLIDER_H
