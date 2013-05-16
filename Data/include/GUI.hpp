#ifndef GUI_H
#define GUI_H

#include <sfml/graphics.hpp>
#include <glm/glm.hpp>
#include <string>

class Slideshow;
class Game;

class GUI
{
	public:
		GUI(sf::RenderWindow  & window, Game & game);
		virtual ~GUI();
		void draw();

		enum GUIState{
			menuClosed,
			escapeMenu,
			optionsMenu
		};

		void startSlideshow(int setNumber);
		void requestUserFocus();
		void openEscapeMenu();
		void closeMenu();
		void openOptionsMenu();
		void previousMenu();
		void click();
		void hover();




	protected:

		GUIState menuState;
		Slideshow *  slideshow;

		bool helpOpen;

		typedef void (GUI::*contextFunction)();
		typedef std::map<sf::Sprite*, contextFunction> spriteContextFuncMap;

		spriteContextFuncMap spriteClickEffects;


		typedef std::map<sf::Sprite*, contextFunction> tooltipMap;
		tooltipMap spriteTooltips;

		void drawMenu();
		void drawHud();
		void drawFocusRequest();
		void drawHelpText();
		void drawTextWithRect(const sf::Text & txt);

		Game & game;

	private://textures and sprites
		sf::RenderWindow & window;

		sf::Texture * mainQbarTex;
		sf::Sprite * mainQbarSprite;

		sf::Texture * mainMenuTex;
		sf::Sprite * mainMenuSprite;

		sf::Texture * progressBarTex;
		sf::Sprite * progressBarSprite;

		sf::Texture * buildOptionsTex;
		sf::Sprite * buildOptionsSprite;

		sf::Texture * wireCutterIconTex;
		sf::Sprite * wireCutterIconSprite;

		sf::Texture * explosiveIconTex;
		sf::Sprite * explosiveIconSprite;

		sf::Texture * laserTurretIconTex;
		sf::Sprite * laserTurretIconSprite;

        sf::Texture * levelReplayTex;
        sf::Sprite * levelReplaySprite;

		sf::Texture * helpIconTex;
		sf::Sprite * helpIconSprite;

		sf::Texture * mouseCursorTex;
		sf::Sprite * mouseCursorSprite;

		sf::RectangleShape  textbox;
		sf::Font gameFont;
		sf::Text helpText;


		sf::Text tooltip;
		sf::Text budgetText;
		sf::Text worldUpdateText;

		sf::Texture * helpTextTex;
		sf::Sprite * helpTextSprite;

		sf::Texture * focusRequestTex;
		sf::Sprite * focusRequestSprite;

		sf::Texture * mainFrameTex;
		sf::Sprite * mainFrameSprite;

		sf::Text debugInfo;

	private: //functions
		//on click sprite functions
		std::string wireCutterString;
		std::string laserTurretString;
		std::string explosiveRobotString;

		bool requestFocus;
		void onQbarClick();
		void onMainMenuClick();
		void onProgressbarClick();
		void onBuildOptionsClick();
		void onHelpClick();
		void onFocusClick();
		void onReplayButtonClick();
		void onExplosiveRobotClick();
		void onLaserTurretClick();
		void onWireCutterClick();
		void onBuildOptionsHover();
		void onQbarHover();
		void onExplosiveRobotHover();
		void onWireCutterHover();
		void onLaserTurretHover();
		bool pointIsIn(const sf::FloatRect & rect, const sf::Vector2i mousePos);


		//get the relative position on the screen
		inline glm::vec2 windowSize();

		inline glm::vec2 center();
		inline glm::vec2 topLeft();
		inline glm::vec2 topCenter();
		inline glm::vec2 topRight();
		inline glm::vec2 centerLeft();
		inline glm::vec2 centerRight();
		inline glm::vec2 bottemLeft();
		inline glm::vec2 bottemCenter();
		inline glm::vec2 bottemRight();
};

#endif // GUI_H
