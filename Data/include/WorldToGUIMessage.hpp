#ifndef WORLDTOGUIMESSAGE_H
#define WORLDTOGUIMESSAGE_H

#include <string>
#include <sfml/graphics.hpp>
#include <glm/glm.hpp>

class WorldToGUIMessage
{
	public:
		WorldToGUIMessage();
		WorldToGUIMessage(std::string message_, glm::vec3 pos_ ,sf::Color color_ = sf::Color::White, int characterSize = 12);
		virtual ~WorldToGUIMessage();

		std::string message;
		sf::Color color;
		glm::vec3 worldPos;
		int characterSize;

	protected:
	private:
};

#endif // WORLDTOGUIMESSAGE_H
