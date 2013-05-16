#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Collider.hpp"
#include "Transform.hpp"

class ShaderProgram;
class Camera;
class Object;
class RaycastHit;

class Stage
{
	public:


		virtual ~Stage();

		void set( Camera * aCamera );
		void add( Object * anObject);
		void update();
		void cleanup();
		void draw();
		void addColliderToCheck(Collider * collider);
		void removeCollider(Object * fromObject);
		void checkCollisions();
		const std::vector<Object*> getObjects()const{return objects;}
		static bool refreshColliders;

		//raycasting


		bool raycast(Ray & ray, std::vector<RaycastHit> & raycastHits,int layerMask = 0); // get all the hits
		bool raycast(Ray & ray, RaycastHit & raycastHit,int layerMask = 0); //get the first hit

	private:
		Stage();
		static Stage * instance;

        static bool sortOnDistance(const RaycastHit & a,const RaycastHit & b);

		std::vector<Collider*> colliders;

		Camera * camera;
		std::vector<Object *> objects; // simple object list, could be octree
		bool solveCollisions;
		glm::mat4 projectionMatrix; // should be in stage-camera
		glm::mat4 viewMatrix; // should be in stage-camera
		glm::vec3 lightDirection; // should be in stage-light
		void findCollidersInChildren(Transform* tr);

	public:

		static Stage * getInstance(){
			if(instance == 0){
				instance = new Stage();
			}
			return instance;
		}
};

#endif // STAGE_H
