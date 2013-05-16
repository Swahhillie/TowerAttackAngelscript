#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "Component.hpp"

#include <glm/glm.hpp>
#include <vector>
class AnimData;

class Animator : public Component
{
	public:
		Animator();
		virtual ~Animator();


		enum AnimState{
			ANIMATING_SINGLE,
			ANIMATING_POSITIONS,
			INACTIVE
		};

		virtual const std::string getName(){return "Animator";}
		virtual void update();

		void animatePosition(const glm::vec3 & startPosition, const glm::vec3 & endPosition, const glm::vec3 & startLookAtPos, const glm::vec3 & endLookAtPos, float timeToTake);
		void animatePositions(const std::vector<glm::vec3> & positions, const glm::vec3 & startLookAtPos, const glm::vec3 & endLookAtPos, float timeToTake);
		void animatePositions(const AnimData & animData);

		AnimState getAnimState()const;
	protected:
	private:

		AnimState state;

		float startTime;
		float endTime;
		float duration;

		glm::vec3 startPos;
		glm::vec3 endPos;

		glm::vec3 startLookAtPos;
		glm::vec3 endLookAtPos;

		int currentPos;
		std::vector<glm::vec3> positions;
};

#endif // ANIMATOR_HPP
