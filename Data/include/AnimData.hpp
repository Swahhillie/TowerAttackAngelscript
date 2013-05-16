#ifndef ANIMDATA_H
#define ANIMDATA_H

#include <vector>
#include <glm/glm.hpp>
#include <string>

class AnimData
{
	public:
		AnimData();
		AnimData(const std::string & name, const std::vector<glm::vec3> & positions, const glm::vec3 & startLookAtPos, const glm::vec3 & endLookAtPos, float timeToTake);
		virtual ~AnimData();
		std::string name;
		std::vector<glm::vec3> positions;
		glm::vec3 startLookAtPos;
		glm::vec3 endLookAtPos;
		float timeToTake;
	protected:
	private:
};

#endif // ANIMDATA_H
