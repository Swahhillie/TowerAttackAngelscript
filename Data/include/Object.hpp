#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include "Collider.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include <map>
#include "Sound.hpp"
#include "RobotComponent.hpp"
//#include "RenderMaterial.hpp"

//class Sound;
class RenderMaterial;
class ShaderProgram;
class Body;
class Component;
class CellManager;
//class Collider;

class Object
{
	public:
		Object();
		virtual ~Object();
		void onDestroy();
		static const int SCENERYLAYER = 1;
		static const int ROBOTLAYER = 2;
		static const int DEFENDERLAYER = 3;

		std::string name;

		void setBody( Body * aBody ); // sets the objects single body
		void setComponent( Component * aComponent ); // sets the objects single behavior
		void update(); // update the object : physics, control...
		void draw(); // draw the objects body


        bool addComponent(Component * behavior);
        Component * getComponent(std::string behaveName);
        Body* getBody()const;
        Collider* getCollider()const;
        Transform* getTransform()const;
        Camera* getCamera()const;

        void addCollider();
        RobotComponent * addRobotComponent(RobotComponent::RobotType roboType);
        RobotComponent * getRobotComponent();
        Camera* addCamera(Camera * cam);
        bool hasCollider;
        friend std::ostream & operator << (std::ostream & out, Object & object);

        void onCollisionEnter(Collider * collider);
        void onCollisionExit(Collider * collider);

        void addSound(Sound * sound);
        void addRenderMaterial();
        RenderMaterial * getRenderMaterial();

        Sound * getSound();
        bool markForDelete;

        void cleanup();

        unsigned int layer;



	private:
		Object& operator = (const Object & other){ /* do nothing */ return *this;}
		Object(const Object & object){ /*do nothing */}
		Body * body; // its body
        Sound * audioSource;
		Collider* collider;
		Transform* transform;
		RobotComponent* robotComponent;
		RenderMaterial * renderMaterial;
		Camera* camera;
		std::map<const std::string, Component*> componentsMap;
		std::vector<Component*> components;



};

#endif // OBJECT_H
