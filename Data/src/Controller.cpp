#include "Controller.hpp"
#include "ShaderProgram.hpp"
#include "GeneralFunctions.hpp"
#include <assert.h>
#include "Time.hpp"
#include "Stage.hpp"
#include "Game.hpp"
#include "Config.hpp"
#include "RaycastHit.hpp"
#include <algorithm>
#include "TextLogger.hpp"


Controller::Controller(sf::RenderWindow & window_, CellManager * manager_, Game & game_):window(window_),game(game_),manager(manager_), focalPoint(glm::vec3(10,0,10)) {
    //ctor
    debuggingColors = false;
    mousePressed = false;
    rotateAround(.0f);

    Config::instance().getSetting("zoomSpeed", zoomSpeed);
    Config::instance().getSetting("rotateSpeed", rotateSpeed);
	Config::instance().getSetting("camSpeed", camSpeed);

}

Controller::~Controller() {
    //dtor
}
void Controller::handleEvent(const sf::Event & event) {
	if(event.type == sf::Event::LostFocus){
		game.onLoseFocus();
    }

	if(game.getFocussed()){
		if(event.type == sf::Event::KeyPressed) {

			int keyCodeInt = (int)event.key.code;
			keyBoolMap::iterator it = pressedKeys.find(keyCodeInt);

			if(it == pressedKeys.end()) {
				//first time this button is pressed, assign it and call its function
				onKeyDown(event.key.code);
				pressedKeys.insert(keyBoolPair(keyCodeInt, true));

				//std::cout << "pressed a button for the first time " << std::endl;
			} else if(it->second == false) {

				onKeyDown(event.key.code);
				it->second = true;

				//std::cout << "pressed a button down " << std::endl;
			}
		} else if(event.type == sf::Event::KeyReleased) {

			int keyCodeInt = (int)event.key.code;
			keyBoolMap::iterator it = pressedKeys.find(keyCodeInt);

			if(it != pressedKeys.end()) { //in case the program is started with a key already down
				it->second = false;
				onKeyUp(event.key.code);

				//std::cout << "released a button " << std::endl;
			}
		}
    }


}
void Controller::update() {
	if(debuggingColors)manager->debugCells();
    mouseControl();
    if(game.getFocussed())keyboardControl();
    //update is used for continuos events suchs when a key is held down.

    moveLight();

}
void Controller::moveLight(){
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	float out = 0;
	const Plane * pl = manager->getCellPlane();
	Ray ray = Camera::main->ScreenPointToRay(glm::vec2(mousePos.x, mousePos.y));
	if(pl->raycast(ray, out)) {
		ShaderProgram::lightPosition = ray.getPoint(out) + glm::vec3(0,3.5,0);
	}
}
void Controller::keyboardControl(){
	//called while key is held down

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        getCell();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rotateAround(-rotateSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rotateAround(rotateSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        rotateAround(0.f, -zoomSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        rotateAround(0.f, zoomSpeed);
    }
}
void Controller::mouseControl() {
	mousePosition = glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if(!mousePressed) onMouseDown();
        mousePressed = true;
        onMouseHold();

    }
    if(mousePressed) {
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            onMouseUp();
            mousePressed = false;
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        ShaderProgram::shininess = ((float)mousePos.x / (float)window.getSize().x) *10; // range [0,10]
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		float out = 0;
		const Plane * pl = manager->getCellPlane();
		Ray ray = Camera::main->ScreenPointToRay(glm::vec2(mousePos.x, mousePos.y));
		if(pl->raycast(ray, out)) {
			glm::vec3 dest = ray.getPoint(out);
			glm::vec3 dir = dest - focalPoint;
			dir = glm::normalize(dir);
			focalPoint += dir * camSpeed * Time::deltaTime;
			focalPoint.x = focalPoint.x > 20? 20 : focalPoint.x;
			focalPoint.x = focalPoint.x < 0? 0 : focalPoint.x;

			focalPoint.y = 0;

			focalPoint.z = focalPoint.z > 20? 20 : focalPoint.z;
			focalPoint.z = focalPoint.z < 0? 0 : focalPoint.z;
		}
//    	float cameraMovespeedFactor = .1;
//    	glm::vec2 deltaMousePos = mousePosition - lastMousePosition;
//    	glm::vec3 move = glm::vec3(deltaMousePos * cameraMovespeedFactor, 0.f);
//    	move.z = move.y;
//    	move.y = 0;
//    	std::cout << focalPoint << std::endl;
//    	move = glm::vec3(Camera::main->object->getTransform()->getTransformation() * glm::vec4(move, 0));
//		focalPoint += move;

    }
    Camera::main->object->getTransform()->lookAt(focalPoint);
    lastMousePosition = mousePosition;
}
void Controller::onMouseUp() {
    //on mouse up
    game.onMouseLeftClick();
}
void Controller::onMouseDown() {
    //on mouse up
    if(game.getFocussed()){
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		Ray ray = Camera::main->ScreenPointToRay(glm::vec2(mousePos.x, mousePos.y));
		Cell * cell = NULL;
		if(manager->getCell(ray, cell)) {
			manager->pathTo(*cell);
			std::cout << " calculated a path " << std::endl;
		}
    }
}
void Controller::onMouseHold(){

//	if(game.getFocussed()){
//		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//		Ray ray = Camera::main->ScreenPointToRay(glm::vec2(mousePos.x, mousePos.y));
//		RaycastHit hitInfo;
//		if(Stage::getInstance()->raycast( ray, hitInfo)){
//			//std::cout << "world position" << hitInfo.point << std::endl;
//
//			glm::vec2 screenPos = Camera::main->WorldPointToView(hitInfo.point);
//		}
//
//    }
}
void Controller::rotateAround(float angle, float zoom) {
    static float currentAngle;
    static float currentZoom = 1;

    currentAngle += angle * Time::deltaTime;
    currentZoom += zoom * Time::deltaTime;

    Transform * tr = Camera::main->object->getTransform();
    float out = 0;
    const Plane * pl = manager->getCellPlane();
    sf::Vector2u windowSize= window.getSize();
    Ray ray = Camera::main->ScreenPointToRay(glm::vec2(windowSize.x, windowSize.y));
    //std::cout <<ray <<std::endl;
    if(pl->raycast(ray, out)) {

        //std::cout << dirToCenter << std::endl;
        //tr->translate(dirToCenter);
        //tr->rotate(angle * Time::deltaTime, glm::normalize(glm::vec3(0,1,1)));
        //tr->translate(-dirToCenter);

        tr->setTransformation(glm::mat4(1.0f));
        tr->setPosition(focalPoint);

        tr->rotate(currentAngle, glm::vec3(0,1,0));//angle = [0..2PI]
        tr->translate(glm::vec3(0,12 * currentZoom,20 * currentZoom)); //move back
        //tr->rotate(-40.0f, glm::vec3(1,0,0));
		Camera::main->object->getTransform()->lookAt(focalPoint);

    }

}

void Controller::resetCellColors() {
    manager->resetCellColors();
}
void Controller::getCell() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //glm::vec2 mousePos = glm::vec2(400,400);
    assert(Camera::main != NULL);
    Ray ray = Camera::main->ScreenPointToRay(glm::vec2(mousePos.x, mousePos.y));
    Cell * cell = NULL;
    if(manager->getCell(ray, cell)) {
        std::cout<< "got a cell " << std::endl;
        cell->changeColor(glm::vec4(1,0,0,1));
    }
}
void Controller::onKeyDown(sf::Keyboard::Key keyCode) {
	if(keyCode == (sf::Keyboard::R)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        Ray ray = Camera::main->ScreenPointToRay(glm::vec2(mousePos.x, mousePos.y));
        Cell * cell = NULL;
        if(manager->getCell(ray, cell)) {
            manager->pathTo(*cell);
            std::cout << " calculated a path " << std::endl;
        }

    }
}
void Controller::onKeyUp(sf::Keyboard::Key keyCode) {
	if(keyCode == (sf::Keyboard::V)) {
        resetCellColors();
    }
    if(keyCode == (sf::Keyboard::B)){
		debuggingColors = !debuggingColors;
		resetCellColors();
    }
    if(keyCode == (sf::Keyboard::N)){
		game.loadNextLevel();
    }
    if(keyCode == (sf::Keyboard::G)){
		TextLogger::instance().addToLog(Camera::main->object->getTransform()->getPosition());
		std::cout << "added pos to log" << std::endl;
	}
}
glm::vec2 Controller::mousePosition;
glm::vec2 Controller::lastMousePosition;
