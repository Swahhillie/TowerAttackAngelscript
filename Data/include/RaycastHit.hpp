#ifndef RAYCASTHIT_H
#define RAYCASTHIT_H

#include <glm/glm.hpp>
class Object;

class RaycastHit
{
	public:
		RaycastHit();
		virtual ~RaycastHit();

		glm::vec3 point;
		glm::vec3 normal;
		float distance;
		Object * object;

	protected:
	private:
};

#endif // RAYCASTHIT_H
