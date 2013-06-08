#ifndef GAME_H
#define GAME_H

#include <sfml/graphics.hpp>
#include <glm/ext.hpp>
#include "ObjectBank.hpp"
#include "CellManager.hpp"
#include "LevelLoader.hpp"
#include "Controller.hpp"
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
//#include <Text.hpp>

class Stage;
class Object;
class Body;
class GUI;

class Game
{
	public:
		enum GameState{
			InSlideshow,
			InGame,
			InMenu
		};
		Game();
		virtual ~Game();

		void build(); // builds the content of the game on stage
		void run(); // the gameloop
		void stop(); // ends the game and clean up

		void onMouseLeftClick();//activate the click function in the gui
		Game::GameState getState()const;
		void endSlideshow();
		void loadNextLevel();
		void replayCurrentLevel();
		void onLoseFocus();
		void onRefocus();
		std::string getDebugInfo()const;
		bool getFocussed();


	private: //functions
		void startSlideshow(int setNumber);
		void loadLevel(int levelNumber);
		bool control(); // empties the event que from the window and evt other sources
		void update(); // do the update: physics & control and collision detection
		void draw(); // render the whole thing
		void createPlanes();
		void createCamera();

	private:
		bool focussed;
		int state; // the gamestate determines the current activity. menu, plaing, game over etc
		Stage * stage; // current stage
		Object * mainObject;
		ObjectBank * objectBank;
		CellManager * cellManager;
		LevelLoader * levelLoader;
		Controller * controller;
		GUI * gui;
		asIScriptEngine * engine;
		GameState gameState;

		sf::RenderWindow * window; // the window to run the game in
		//sf::Text debugText;
		std::vector<Object*>gates;


};

#endif // GAME_H
