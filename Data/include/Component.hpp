#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
//#include "Collider.hpp"
#include <string>
//#include "Object.hpp"
//#include "Time.hpp"
//#include "GeneralFunctions.hpp"

class Object;
class Collider;

class Component
{
	public:
		Component();
		virtual ~Component();

		virtual void update(); // updates the physics and behaviour
		Object * object;
		virtual const std::string getName() = 0;
		virtual void onConnect();
		virtual void onCollisionEnter(Collider * collider);
		virtual void onCollisionExit(Collider * collider);

	private:

		Component(const Component & other){}
		Component& operator = (const Component & other){return *this;}

};

#endif // BEHAVIOR_H
