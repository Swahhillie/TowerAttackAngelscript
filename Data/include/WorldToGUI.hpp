#ifndef WORLDTOGUI_H
#define WORLDTOGUI_H

#include <vector>
#include <glm/glm.hpp>
#include "Component.hpp"

class WorldToGUIMessage;
class RobotController;
class Defender;

class WorldToGUI : public Component
{
	public:
		static WorldToGUI & instance(){
			static WorldToGUI INSTANCE;
			return INSTANCE;
		}


		virtual void update();

		const std::vector<WorldToGUIMessage> & getStringsToDraw()const;

		virtual const std::string getName(){return "WorldToGUI";}
		virtual ~WorldToGUI();
	protected:
	private:
		WorldToGUI();
		std::vector<WorldToGUIMessage> toDraw;
		glm::vec3 offset;
		void addPowernodeMessage(const Defender * def);
		RobotController & robotController;
		void pointAtTooltip();
		void levelSpecific();
};

#endif // WORLDTOGUI_H
