#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sfml/graphics.hpp>
#include "Camera.hpp"
#include "CellManager.hpp"
#include <map>
#include <glm/glm.hpp>

class Game;

class Controller
{
	public:
		Controller(sf::RenderWindow & window, CellManager * manager, Game & game);
		virtual ~Controller();
		void update();
		virtual const std::string getName(){return "Controller";}
		void handleEvent(const sf::Event & event);

		static glm::vec2 mousePosition;
		static glm::vec2 lastMousePosition;

	protected:
	private:
		void rotateAround(float angle, float zoom = 0.0f);
		sf::RenderWindow & window;
		Game & game;
		CellManager * manager;
		void getCell();
		void resetCellColors();


		void onKeyDown(sf::Keyboard::Key keyCode);
		void onKeyUp(sf::Keyboard::Key keyCode);
		void moveLight();


	private:
		glm::vec3 focalPoint;
		bool debuggingColors;
		float camSpeed;
        float zoomSpeed;
        float rotateSpeed;
		typedef std::map<int, bool> keyBoolMap;
		typedef keyBoolMap::value_type keyBoolPair;
		keyBoolMap pressedKeys;


		void mouseControl();
		void keyboardControl();
		void onMouseDown();
		void onMouseUp();
		void onMouseHold();

		bool mousePressed;
};

#endif // CONTROLLER_H
