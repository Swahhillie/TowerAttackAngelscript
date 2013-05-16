#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.hpp"
class RaycastHit;
class SphereCollider : public Collider
{
	public:
		SphereCollider();
		virtual ~SphereCollider();
		bool collideWith(Collider * collider);
		bool raycast(const Ray & ray, RaycastHit & hitInfo);
		virtual const std::string getName(){return "SphereCollider";}

	protected:
	private:
};

#endif // SPHERECOLLIDER_H
