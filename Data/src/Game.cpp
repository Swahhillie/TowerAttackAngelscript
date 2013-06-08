#include <iostream>
#include "Time.hpp"
#include "FPS.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Stage.hpp"
#include "Object.hpp"
#include "Body.hpp"
#include "Texture.hpp"
#include "Component.hpp"
#include "Collider.hpp"
#include "CellManager.hpp"
#include "SkyboxRotation.hpp"
#include "Plane.hpp"
#include "GUI.hpp"
#include "Controller.hpp"
#include "Level.hpp"
#include <Math.h>
#include "Sound.hpp"
#include "BudgetManager.hpp"
#include "RobotComponent.hpp"
#include "RobotController.hpp"
#include "Cell.hpp"
#include "GeneralFunctions.hpp"
#include "Config.hpp"
#include "WorldToGUI.hpp"
#include "Animator.hpp"
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include "ScriptGlobal.h"
#include <GL/glew.h>


Game::Game():engine(NULL) {
    unsigned int resX = 1024;
    unsigned int resY = 700;
    bool fullScreen = false;

    Config::instance().getSetting("resX", resX);
    Config::instance().getSetting("resY", resY);
    Config::instance().getSetting("fullScreen", fullScreen);

    if(fullScreen)window = new sf::RenderWindow( sf::VideoMode( resX, resY), "Tower ATTACK" , sf::Style::Fullscreen   );
    else window = new sf::RenderWindow( sf::VideoMode( resX, resY), "Tower ATTACK" /*, sf::Style::Fullscreen */  );
    //window->setVerticalSyncEnabled( true );
    //sf::Style::Fullscreen

    // init and check glew for opengl > 1.5
    std::cout << glGetString( GL_VERSION ) << std::endl;
    std::cout << "GlewInit : " << (glewInit() == GLEW_OK) << " (should be 1) " << std::endl; //init extended opengl functionality after creating window

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
    gameState = InGame;
    focussed = true;

}

Game::~Game() {
    //thomaskillsdaviddestructor
}
void Game::build() {
    // building game content: stage
    //shader = new ShaderProgram( "SimpleShading.VertexShader", "SimpleShading.FragmentShader" );
    window->setVerticalSyncEnabled(false);
    std::cout << "Loading Game" << std::endl;
    levelLoader = new LevelLoader();
    stage = Stage::getInstance();
    mainObject = new Object();
    mainObject->name = "MAIN OBJECT";
    objectBank = &ObjectBank::instance();
    objectBank->init(mainObject);

    RobotController::instance().objectBank = objectBank;
    mainObject->addComponent(&WorldToGUI::instance());
    createPlanes();
    createCamera();
    stage->add(mainObject);
    gui = new GUI(*window, *this);
    startSlideshow(cellManager->getCurrentLevel()->comicInt);
    BudgetManager::instance().setBudget(cellManager->getCurrentLevel()->budget);
    controller = new Controller(*window, cellManager, *this);
    mainObject->addComponent(new Sound());

}
/*
void Game::setupScripting(){

	int r = 0;

    engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

    r = engine->SetMessageCallback(asFUNCTION(Scripting::MessageCallback), 0, asCALL_CDECL);
    assert( r >= 0 );

    RegisterStdString(engine);

    r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(Scripting::print), asCALL_CDECL);
    assert( r >= 0 );


	CompileScript scriptCompiler;
	scriptCompiler.build(engine);

	runner.run(engine);
}
*/
void Game::createPlanes() {

    const Level * firstLevel = levelLoader->load(levelLoader->getCurrentLevel());
    cellManager = &CellManager::instance();
    cellManager->init(objectBank, firstLevel);
    mainObject->addComponent(cellManager);
    cellManager->generate();
    //loadLevel(0);

    int amount = 0;
    for(int i = 0; i < amount; i ++) {
        for(int j = 0; j < amount; j++) {
            for (int k = 0 ; k < amount; k++) {
                Object * testObject =objectBank->getTestObject();
                testObject->getTransform()->setPosition(glm::vec3(i,j,k));
            }
        }
    }

//ROBOT WITH BEHAVIOUR
//    std::cout << "about to load robots " << std::endl;
    //Object * robotWithBehaviour = objectBank->getBehaviourRobot(cellManager);
    //RobotComponent * roboBehave = robotWithBehaviour->getRobotComponent();;
//    Cell * cell = new Cell();

//    if(cellManager->getCell(6, 12,*cell)) {
//        std::cout << "moving robot component" << std::endl;
//        roboBehave->followMapPath();
//        std::cout << *cell << std::endl;
//
//    }






}
void Game::replayCurrentLevel(){
    int current = levelLoader->getCurrentLevel();
    loadLevel(current);
}
void Game::loadNextLevel(){
	int current = levelLoader->getCurrentLevel();
	std::cout << levelLoader->getLevelCount() << std::endl;
	current = current + 1 == levelLoader->getLevelCount()? 0: current + 1;
	std::cout << "loading level number " << current << std::endl;
	loadLevel(current);

}
void Game::loadLevel(int levelNumber){
	RobotController::instance().markRobotsForDestroy();
	RobotController::instance().clearQueue();
	cellManager->initiatateCleanup();
	stage->cleanup();
	std::cout << "LEVEL CLEANED UP"<< std::endl;
	std::cout << "------------------loading level ------------------- " << std::endl;
	assert(levelNumber >= 0 && levelNumber < levelLoader->getLevelCount());
	const Level * levelToLoad = levelLoader->load(levelNumber);

	cellManager->loadLevel(levelToLoad);

	assert(levelToLoad->comicInt < Config::instance().getComicSetCount());

	if(levelToLoad->comicInt >= 0)startSlideshow(levelToLoad->comicInt);
	BudgetManager & budgetManager = BudgetManager::instance();
	budgetManager.setBudget(levelToLoad->budget);

	std::cout << "-------------------loaded " << levelToLoad->levelName << ", number " << levelToLoad->levelNumber << "-------------"<< std::endl;

}
void Game::createCamera() {
    Object * camObject = new Object();
    Camera * cam = new Camera(*window);
    camObject->addCamera(cam);
    camObject->addComponent(new Animator());

    stage->set(camObject->getCamera());
    Transform * tr = camObject->getTransform();
    tr->setParent(mainObject->getTransform());
    //tr->setPosition(glm::vec3(-5.0f,12.0f,-5.0f));
    tr->setPosition(glm::vec3(10.0f,12.0f,30.0f));
    tr->rotate(-0.0f, glm::vec3(0, 1, 0));
    tr->rotate(-0.0f, glm::vec3(1, 0, 0));

	Object * skybox = objectBank->getSkybox();

    skybox->addComponent(new SkyboxRotation(camObject->getTransform()));

}
void Game::onMouseLeftClick(){
	gui->click();
}
void Game::run() {
    std::cout << "--------------begin update loop--------------" << std::endl;
    bool running = true;
    while ( running ) {
        Time::update();
//		std::cout<<"running"<<std::endl;
        running = control();
        RobotController::instance().update();
        update();
        draw();

        FPS::update();
    }
}

void Game::stop() {
}

bool Game::control() {
    sf::Event event;

    while ( window->pollEvent(event) ) {

        if ( event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) ) { // Close window : exit
            window->close();
            return false;
        }

        else{

			controller->handleEvent(event);
        }
    }
    return true;
}
void Game::update() {
	if(!focussed){
		gui->requestUserFocus();
	}
	switch(gameState){
		case InGame:
			controller->update();
			if(focussed){
				stage->update();

			}
			if(cellManager->levelComplete)loadNextLevel();
			stage->cleanup();
			break;
		case InMenu: break;

		case InSlideshow:
			controller->update();
			break;
	}




}
void Game::draw() {
    // init


    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  ); // clear color buffer

	switch(gameState){
		case InGame:
			stage->draw();

			gui->draw();

			break;
		case InMenu:

			gui->draw();
			break;
		case InSlideshow:

			gui->draw();
			break;
	}
    window->display();

}
void Game::onLoseFocus(){
	focussed = false;
}
void Game::onRefocus(){
	focussed = true;
}
bool Game::getFocussed(){
	return focussed;
}
Game::GameState Game::getState()const{
	return gameState;
}
void Game::startSlideshow(int setNumber){
	assert(setNumber >= 0 && setNumber < Config::instance().getComicSetCount());
	gui->startSlideshow(setNumber);
	gameState = InSlideshow;
}
void Game::endSlideshow(){
	gameState = InGame;

//    if(levelLoader->getCurrentLevel() == 0){
//        Animator * animator = (Animator*) Camera::main->object->getComponent("Animator");
//        AnimData aniData =Config::instance().getAnimation("FlyStraight");
//
//        animator->animatePositions(aniData);
//    }
    //animator->animatePosition(glm::vec3(0,10,0), glm::vec3(20, 20, 20), glm::vec3(10,0,10), glm::vec3(10,0,10), 10.0f);
}
std::string Game::getDebugInfo()const{
    unsigned int objectCount = 0;
    const std::vector<Object*> objects = stage->getObjects();
    for(unsigned int i = 0 ; i < objects.size(); i++){
        const Transform * tr = objects[i]->getTransform();
        objectCount += tr->getChildCountTotal();
    }
    std::stringstream stream;
    stream << objectCount;
    std::string objectCountStr = stream.str();
    //std::cout << " total objects " << objectCountStr << std::endl;
    return objectCountStr;
}

