#include "WorldToGUIMessage.hpp"

WorldToGUIMessage::WorldToGUIMessage():
message(std::string("no message")),
 color(sf::Color::White),
 worldPos(glm::vec3(0,0,0))
{
	//ctor
}
WorldToGUIMessage::WorldToGUIMessage(std::string message_, glm::vec3 pos_ ,sf::Color color_, int characterSize_):
message(message_),
color(color_),
 worldPos(pos_),
  characterSize(characterSize_)
{

}
WorldToGUIMessage::~WorldToGUIMessage()
{
	//dtor
}
