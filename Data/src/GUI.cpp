#include "GUI.hpp"
#include "Game.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Config.hpp"
#include "RobotComponent.hpp"
#include "RobotController.hpp"
#include "RobotInQ.hpp"
#include "Slideshow.hpp"
#include "Time.hpp"
#include <SFML/Graphics.hpp>
#include "WorldToGUI.hpp"
#include "WorldToGUIMessage.hpp"
#include "BudgetManager.hpp"
#include "GeneralFunctions.hpp"

GUI::GUI(sf::RenderWindow & window_, Game & game_):
menuState(menuClosed),
slideshow(new Slideshow(window_)),
helpOpen(true),
game(game_),
window(window_),
 requestFocus(false)
 {
 	std::cout << "----------------creating GUI-----------------"<<std::endl;
    window.setMouseCursorVisible(false);
    //construct elements
    std::string thisTex = "";


    //setting the robot tooltip strings


    Config::instance().getSetting("robotExplosiveString", explosiveRobotString);
    Config::instance().getSetting("robotLaserTurretString", laserTurretString);
    Config::instance().getSetting("robotWireCutterString", wireCutterString);

    Config::instance().getSetting("mainQbarTex", thisTex);
    mainQbarTex = new sf::Texture();
    mainQbarTex->loadFromFile(thisTex);

    mainQbarSprite = new sf::Sprite();
    mainQbarSprite->setTexture(*mainQbarTex);

    Config::instance().getSetting("mainMenuTex", thisTex);
    mainMenuTex = new sf::Texture();
    mainMenuTex->loadFromFile(thisTex);

    mainMenuSprite = new sf::Sprite();
    mainMenuSprite->setTexture(*mainMenuTex);

    Config::instance().getSetting("progressBarTex", thisTex);
    progressBarTex = new sf::Texture();
    progressBarTex->loadFromFile(thisTex);

    progressBarSprite = new sf::Sprite();
    progressBarSprite->setTexture(*progressBarTex);

    Config::instance().getSetting("buildOptionsTex", thisTex);
    buildOptionsTex = new sf::Texture();
    buildOptionsTex->loadFromFile(thisTex);


    buildOptionsSprite = new sf::Sprite();
    buildOptionsSprite->setTexture(*buildOptionsTex);

    Config::instance().getSetting("wireCutterIconTex", thisTex);
	wireCutterIconTex = new sf::Texture();
	wireCutterIconTex->loadFromFile(thisTex);

	wireCutterIconSprite = new sf::Sprite();
	wireCutterIconSprite->setTexture(*wireCutterIconTex);

	Config::instance().getSetting("explosiveIconTex", thisTex);
	explosiveIconTex = new sf::Texture();
	explosiveIconTex->loadFromFile(thisTex);

	explosiveIconSprite = new sf::Sprite();
	explosiveIconSprite->setTexture(*explosiveIconTex);

	Config::instance().getSetting("laserTurretIconTex", thisTex);
	laserTurretIconTex = new sf::Texture();
	laserTurretIconTex->loadFromFile(thisTex);

	laserTurretIconSprite = new sf::Sprite();
	laserTurretIconSprite->setTexture(*laserTurretIconTex);

	Config::instance().getSetting("helpTextTex", thisTex);
	helpTextTex = new sf::Texture();
	helpTextTex->loadFromFile(thisTex);

	helpTextSprite = new sf::Sprite();
	helpTextSprite->setTexture(*helpTextTex);

	Config::instance().getSetting("levelReplayTex", thisTex);
	levelReplayTex = new sf::Texture();
	levelReplayTex->loadFromFile(thisTex);

	levelReplaySprite = new sf::Sprite();
	levelReplaySprite->setTexture(*levelReplayTex);

	Config::instance().getSetting("helpIconTex", thisTex);
	helpIconTex = new sf::Texture();
	helpIconTex->loadFromFile(thisTex);

	helpIconSprite = new sf::Sprite();
	helpIconSprite->setTexture(*helpIconTex);

	Config::instance().getSetting("focusRequestTex", thisTex);
	focusRequestTex= new sf::Texture();
	focusRequestTex->loadFromFile(thisTex);


	focusRequestSprite = new sf::Sprite();
	focusRequestSprite->setTexture(*focusRequestTex);

    Config::instance().getSetting("mouseCursorTex", thisTex);
    mouseCursorTex = new sf::Texture();
    mouseCursorTex->loadFromFile(thisTex);

    mouseCursorSprite = new sf::Sprite();
    mouseCursorSprite->setTexture(*mouseCursorTex);

	Config::instance().getSetting("mainFrameTex", thisTex);
	mainFrameTex = new sf::Texture();
	mainFrameTex->loadFromFile(thisTex);

    mainFrameSprite = new sf::Sprite();
    mainFrameSprite->setTexture(*mainFrameTex);

	Config::instance().getSetting("gameFont", thisTex);
	if(!gameFont.loadFromFile(thisTex)){
		std::cout << "FAILED LOADING FONT" << std::endl;
	}
	else{
        std::cout << "Loaded font " << thisTex << std::endl;

    }










	//helpText = sf::Text("hello", gameFont, 30);
	helpText.setFont(gameFont);
	helpText.setString("Click a robot in the bottem right corner to start building it.");
	helpText.setCharacterSize(30);
	helpText.setPosition(0,0);
	//helpText.setFont(*gameFont);
	helpText.setStyle(sf::Text::Bold);
	helpText.setColor(sf::Color::White);

	tooltip.setFont(gameFont);

	tooltip.setCharacterSize(15);
	tooltip.setColor(sf::Color::White);


	std::cout << std::string(helpText.getString()) << std::endl;

	textbox = sf::RectangleShape(sf::Vector2f(helpText.getLocalBounds().width, helpText.getLocalBounds().height));
    textbox.setPosition(helpText.getGlobalBounds().left, helpText.getGlobalBounds().top);
    textbox.setFillColor(sf::Color::Transparent);
    textbox.setOutlineColor(sf::Color::White);
    textbox.setOutlineThickness(1);

	budgetText.setFont(gameFont);
	budgetText.setString( BudgetManager::instance().getMoneyString() );

	budgetText.setColor(sf::Color::White);

	worldUpdateText.setFont(gameFont);
	worldUpdateText.setString( "Blank ");
	worldUpdateText.setColor(sf::Color::White);
	worldUpdateText.setCharacterSize(12);

	levelReplaySprite->setPosition(topLeft().x, topLeft().y);
	//aligning the UI.
    float hudSize = 0;
    Config::instance().getSetting("hudSize", hudSize); //get hudSize setting from game settings file
    assert(hudSize > 0);

	// X scale is relative to the window width, if the hudSize is 1 the bottem interface has the same width as the windoww.
    float scaleX = (windowSize().x / ((float) mainQbarTex->getSize().x + buildOptionsTex->getSize().x)) * hudSize;
    mainQbarSprite->setScale(scaleX, scaleX);
    progressBarSprite->setScale(scaleX, scaleX);

    //float buildOptionsScale = (progressBarSprite->getGlobalBounds().height + mainQbarSprite->getGlobalBounds().height) / buildOptionsTex->getSize().x;
    buildOptionsSprite->setScale(scaleX, scaleX);

	glm::vec2 mainQbarPos = bottemCenter() - glm::vec2(mainQbarSprite->getGlobalBounds().width /2 + buildOptionsSprite->getGlobalBounds().width /2,
														 mainQbarSprite->getGlobalBounds().height + progressBarSprite->getGlobalBounds().height);

    mainQbarSprite->setPosition(mainQbarPos.x, mainQbarPos.y);

	mainMenuSprite->setScale(scaleX, scaleX);
    mainMenuSprite->setPosition(50,60);//top left

    mainFrameSprite->setScale(scaleX, scaleX);
    mainFrameSprite->setPosition(mainQbarPos.x - mainFrameSprite->getGlobalBounds().width /2, bottemCenter().y - mainFrameSprite->getGlobalBounds().height);


    progressBarSprite->setPosition(mainQbarPos.x, mainQbarPos.y + mainQbarSprite->getGlobalBounds().height);

    buildOptionsSprite->setPosition(mainQbarPos.x + mainQbarSprite->getGlobalBounds().width, mainQbarPos.y);
    budgetText.setPosition( buildOptionsSprite->getGlobalBounds().left, buildOptionsSprite->getGlobalBounds().top - budgetText.getGlobalBounds().height - 10);

	sf::FloatRect boPos = buildOptionsSprite->getGlobalBounds();
	float robotIconScale = 0;
	Config::instance().getSetting("robotIconScale", robotIconScale);

	wireCutterIconSprite->setScale(robotIconScale, robotIconScale);
	explosiveIconSprite->setScale(robotIconScale, robotIconScale);
	laserTurretIconSprite->setScale(robotIconScale, robotIconScale);


	wireCutterIconSprite->setPosition(boPos.left +boPos.width / 3 * 0, boPos.top);
	explosiveIconSprite->setPosition(boPos.left +boPos.width / 3 * 1, boPos.top);
	laserTurretIconSprite->setPosition(boPos.left +boPos.width / 3 * 2, boPos.top);

	helpIconSprite->setPosition(topRight().x - helpIconSprite->getGlobalBounds().width, topRight().y);
	helpTextSprite->setPosition(topRight().x - helpTextSprite->getGlobalBounds().width, topRight().y);


	typedef std::pair<sf::Sprite*, contextFunction> pairType; //shortcut to write this type

	//add the spirte to the map and add a function pointer to be called on click
    spriteClickEffects[mainQbarSprite] = &GUI::onQbarClick;//(pairType(mainQbarSprite, &GUI::onQbarClick));
    spriteClickEffects[progressBarSprite] = &GUI::onProgressbarClick; //.insert(pairType(progressBarSprite, &GUI::onProgressbarClick));
    spriteClickEffects[mainMenuSprite] = &GUI::onMainMenuClick; //.insert(pairType(mainMenuSprite, &GUI::onMainMenuClick));
    //spriteClickEffects[buildOptionsSprite] = &GUI::onBuildOptionsClick; //.insert(pairType(buildOptionsSprite, &GUI::onBuildOptionsClick));
	spriteClickEffects[helpIconSprite] = &GUI::onHelpClick;
	spriteClickEffects[helpTextSprite] = &GUI::onHelpClick;
	spriteClickEffects[focusRequestSprite] = &GUI::onFocusClick;
	spriteClickEffects[levelReplaySprite] = &GUI::onReplayButtonClick;
	spriteClickEffects[wireCutterIconSprite] = &GUI::onWireCutterClick;
	spriteClickEffects[laserTurretIconSprite] = &GUI::onLaserTurretClick;
	spriteClickEffects[explosiveIconSprite] = &GUI::onExplosiveRobotClick;

	//spriteTooltips[buildOptionsSprite] = &GUI::onBuildOptionsHover;
	spriteTooltips[mainQbarSprite] = &GUI::onQbarHover;
	spriteTooltips[wireCutterIconSprite] = &GUI::onWireCutterHover;
	spriteTooltips[laserTurretIconSprite] = &GUI::onLaserTurretHover;
	spriteTooltips[explosiveIconSprite] = &GUI::onExplosiveRobotHover;

    debugInfo.setColor(sf::Color::Red);
    debugInfo.setString(std::string("Hallo, hoe is het ermee"));
}

GUI::~GUI() {
    //dtor
}
void GUI::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind all the buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
	glDisable(GL_CULL_FACE);
	window.pushGLStates();

	switch(game.getState()){
		case Game::InMenu:
			drawMenu();
			break;
		case Game::InGame:
			drawHud();
			break;
		case Game::InSlideshow:
			if(slideshow->isInSlideShow()){
				slideshow->update();
			}
			else{
				game.endSlideshow();
			}
			break;
	}
	if(requestFocus){
		drawFocusRequest();
	}
	hover();




    //window->resetGLStates();

    window.popGLStates();
	glEnable(GL_CULL_FACE);

}
void GUI::drawHelpText(){

}
void GUI::requestUserFocus(){
	requestFocus = true;
}
void GUI::drawHud(){
	//window.clear();

	//Text
	//window.draw(textbox);
	//drawTextWithRect(helpText);

	budgetText.setString( BudgetManager::instance().getMoneyString() );
	drawTextWithRect(budgetText);
    window.draw(*levelReplaySprite);



//	helpText.setPosition( 400 * (Time::currentTime - (int)Time::currentTime),  400 * (Time::currentTime - (int)Time::currentTime));

//	std::cout << helpText.getStyle() << std::endl;
//	std::cout << helpText.getGlobalBounds().height << std::endl;


    window.draw(*mainFrameSprite);
	window.draw(*mainQbarSprite);
    window.draw(*progressBarSprite);

    sf::FloatRect boPos = buildOptionsSprite->getGlobalBounds();
    wireCutterIconSprite->setPosition(boPos.left +boPos.width / 3 * 0, boPos.top);
	explosiveIconSprite->setPosition(boPos.left +boPos.width / 3 * 1, boPos.top);
	laserTurretIconSprite->setPosition(boPos.left +boPos.width / 3 * 2, boPos.top);

    window.draw(*wireCutterIconSprite);
    window.draw(*explosiveIconSprite);
    window.draw(*laserTurretIconSprite);
    window.draw(*buildOptionsSprite);

    debugInfo.setString(game.getDebugInfo());
    //window.draw(debugInfo);


	//drawing the queue
    std::vector<RobotInQ * > queuedRobots = RobotController::instance().getRobotQueue();
    sf::FloatRect qbarDimensions = mainQbarSprite->getGlobalBounds();
    for(unsigned int i = 0; i < queuedRobots.size(); i++){
    	//drawing all elements in the Robotcontroller queue, they are sorted for time remaining.
    	glm::vec2 pos = glm::vec2(qbarDimensions.left + qbarDimensions.width / 7 * i, qbarDimensions.top);
		RobotInQ * qr = queuedRobots[i];
		sf::Sprite * spr;
		switch(qr->robotType){
			case RobotComponent::WireCutter: spr = wireCutterIconSprite; break;
			case RobotComponent::Explosive: spr = explosiveIconSprite; break;
			case RobotComponent::LaserTurret: spr = laserTurretIconSprite; break;
		}
		spr->setPosition(pos.x,pos.y);
		window.draw(*spr);
    }
    //drawing game notifications
    const std::vector<WorldToGUIMessage> & stringsToDraw = WorldToGUI::instance().getStringsToDraw();
	for(unsigned int i = 0; i < stringsToDraw.size(); i++){
		const WorldToGUIMessage & mssg = stringsToDraw[i];
		glm::vec2 screenPos = Camera::main->WorldPointToView(mssg.worldPos);
		//std::cout << "write " << stringsToDraw[i].second << " at " << stringsToDraw[i].first << std::endl;
		worldUpdateText.setString(mssg.message);
		worldUpdateText.setColor(mssg.color);
		worldUpdateText.setPosition(screenPos.x, windowSize().y - screenPos.y);
		worldUpdateText.setOrigin(worldUpdateText.getLocalBounds().width / 2, worldUpdateText.getLocalBounds().height / 2);
		worldUpdateText.setCharacterSize(mssg.characterSize);
		drawTextWithRect(worldUpdateText);
	}
    //std::cout << helpText->getGlobalBounds().width << std::endl;
    if(helpOpen){
		window.draw(*helpTextSprite);
    }
    else{
		window.draw(*helpIconSprite);
    }


    mouseCursorSprite->setPosition(Controller::mousePosition.x, Controller::mousePosition.y);
    window.draw(*mouseCursorSprite);

}
void GUI::drawFocusRequest(){
	window.draw(*focusRequestSprite);
}
void GUI::drawTextWithRect(const sf::Text & txt){
	textbox.setSize(sf::Vector2f(txt.getLocalBounds().width, txt.getLocalBounds().height));
    textbox.setPosition(txt.getGlobalBounds().left, txt.getGlobalBounds().top);
    window.draw(textbox);
	window.draw(txt);

}
void GUI::click(){
	//called by controller, through game
	//compare mouse pos with gui elements

	//if the mouse pos is within a gui rect activate the function it is stored with

	if(game.getState() == Game::InGame){
		spriteContextFuncMap::iterator it;
		for(it = spriteClickEffects.begin(); it != spriteClickEffects.end(); it++){
			if(pointIsIn(it->first->getGlobalBounds(), sf::Mouse::getPosition(window))){
				contextFunction func = it->second;
				(this->*func)();
			}
		}
	}
	else if(game.getState() == Game::InSlideshow){
		slideshow->onClick();
	}
}
void GUI::hover(){
	if(game.getState() == Game::InGame){
		tooltipMap::iterator it;
		for(it = spriteTooltips.begin(); it != spriteTooltips.end(); it++){
			if(pointIsIn(it->first->getGlobalBounds(), sf::Mouse::getPosition(window))){
				contextFunction func = it->second;
				(this->*func)();
			}
		}
	}
}
bool GUI::pointIsIn(const sf::FloatRect & rect, const sf::Vector2i mousePos){
	return mousePos.x > rect.left && mousePos.x < rect.width + rect.left && mousePos.y > rect.top && mousePos.y < rect.top + rect.height;
}
void GUI::drawMenu(){
	if(menuState == escapeMenu){
		window.draw(*mainMenuSprite);
	}
}
void GUI::openEscapeMenu(){
	menuState = escapeMenu;
}
void GUI::closeMenu(){
	menuState = menuClosed;
}
void GUI::openOptionsMenu(){
	menuState = optionsMenu;
}
void GUI::onFocusClick(){
	if(requestFocus){
		game.onRefocus();
		requestFocus = false;
	}
}
void GUI::onReplayButtonClick(){
    std::cout << " clicked replay " << std::endl;
    game.replayCurrentLevel();
}
void GUI::onBuildOptionsHover(){
	sf::FloatRect boPos = buildOptionsSprite->getGlobalBounds();
	tooltip.setString("Click a robot to build it");
	tooltip.setPosition(boPos.left, boPos.top - tooltip.getGlobalBounds().height - 40);
	drawTextWithRect(tooltip);
}
void GUI::onQbarHover(){
	sf::FloatRect boPos = mainQbarSprite->getGlobalBounds();
	tooltip.setString("This is the build queue");
	tooltip.setPosition(boPos.left, boPos.top - tooltip.getGlobalBounds().height - 40);
	drawTextWithRect(tooltip);
}
void GUI::previousMenu(){
	switch(menuState){
		case menuClosed: break;
		case escapeMenu: closeMenu(); break;
		case optionsMenu: menuState = escapeMenu; break;
	}
}

void GUI::onQbarClick(){
	std::cout << "clicked the q bar" << std::endl;
}
void GUI::onProgressbarClick(){
	std::cout << "clicked  the progress bar " << std::endl;
}
void GUI::onMainMenuClick(){
	std::cout << "clicked  main menu rect " << std::endl;
}
void GUI::onBuildOptionsClick(){
	//seperate the click in 3 blocks. left middle and right, wirecutter explosive and lasterturret
	std::cout << "clicked  buildoptions rect " << std::endl;
	sf::Vector2i clickPos = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = buildOptionsSprite->getGlobalBounds();
	RobotComponent::RobotType clickedType = RobotComponent::WireCutter;

	if(clickPos.x < bounds.left + bounds.width / 3.0){
		clickedType = RobotComponent::WireCutter;

	}
	else if(clickPos.x > bounds.left + bounds.width /3.0 * 2){
		clickedType = RobotComponent::LaserTurret;
	}
	else{
		clickedType = RobotComponent::Explosive;
	}

	RobotController & rbc = RobotController::instance();
	rbc.addToQ(clickedType);
}
void GUI::onWireCutterClick(){
    RobotController::instance().addToQ(RobotComponent::WireCutter);
}
void GUI::onLaserTurretClick(){
    RobotController::instance().addToQ(RobotComponent::LaserTurret);
}
void GUI::onExplosiveRobotClick(){
    RobotController::instance().addToQ(RobotComponent::Explosive);
}
void GUI::onWireCutterHover(){
    sf::FloatRect boPos = wireCutterIconSprite->getGlobalBounds();

	tooltip.setString(wireCutterString);
	tooltip.setPosition(boPos.left, boPos.top - tooltip.getGlobalBounds().height - 40);
	drawTextWithRect(tooltip);
}
void GUI::onLaserTurretHover(){
    sf::FloatRect boPos = mainQbarSprite->getGlobalBounds();
	tooltip.setString(laserTurretString);
	tooltip.setPosition(boPos.left, boPos.top - tooltip.getGlobalBounds().height - 40);
	drawTextWithRect(tooltip);
}
void GUI::onExplosiveRobotHover(){
    sf::FloatRect boPos = mainQbarSprite->getGlobalBounds();
	tooltip.setString(explosiveRobotString);
	tooltip.setPosition(boPos.left, boPos.top - tooltip.getGlobalBounds().height - 40);
	drawTextWithRect(tooltip);
}
void GUI::onHelpClick(){
	helpOpen = !helpOpen;
	if(helpOpen) std::cout << "help text ON" << std::endl;
	else std::cout << "help text OFF" << std::endl;
}
void GUI::startSlideshow(int setNumber){
	slideshow->startSet(setNumber);
}
glm::vec2 GUI::windowSize() {
    return glm::vec2(window.getSize().x, window.getSize().y);
}
glm::vec2 GUI::center() {
    return windowSize() * .5f;
}
glm::vec2 GUI::topLeft() {
    return glm::vec2(0, 0);
}
glm::vec2 GUI::topCenter() {
    return glm::vec2(windowSize().x /2,0);
}
glm::vec2 GUI::topRight() {
    return glm::vec2(windowSize().x,0);
}
glm::vec2 GUI::centerLeft() {
    return glm::vec2(0,windowSize().y /2);
}
glm::vec2 GUI::centerRight() {
    return glm::vec2(windowSize().x,windowSize().y/2);
}
glm::vec2 GUI::bottemLeft() {
    return glm::vec2(0,windowSize().y);
}
glm::vec2 GUI::bottemCenter() {
    return glm::vec2(windowSize().x /2,windowSize().y);
}
glm::vec2 GUI::bottemRight() {
    return windowSize();
}
