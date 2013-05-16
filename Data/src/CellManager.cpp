#include "CellManager.hpp"
#include "Cell.hpp"
#include "ObjectBank.hpp"
#include <sstream>
#include <assert.h>
#include "GeneralFunctions.hpp"
#include <math.h>
#include "Turret.hpp"
#include "RobotController.hpp"

CellManager::CellManager():levelComplete(false), initialized(false), cellPlane(NULL), currentLevel(NULL)
{
    //ctor
	std::cout << "----------------creating Cellmanager---------"<< std::endl;

	cells = std::vector<CellVector>(WIDTH);
	for(int i = 0; i < WIDTH; i++)
		cells[i] = std::vector<Cell *>(HEIGHT);

}

CellManager::~CellManager()
{
    //dtor
    delete cellPlane;
}

void CellManager::init(ObjectBank * objectBank, const Level * firstLevel){
	this->currentLevel = firstLevel;
	this->objectBank = objectBank;
	initialized = true;
	assert(currentLevel != NULL);
    cellPlane = new Plane(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0,0,0));
}

void CellManager::generate(){
    assert(currentLevel != NULL);
	std::cout<<"generating"<<std::endl;

	std::stringstream outstr;
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            Object * obj = new Object();
            obj->getTransform()->setParent(objectBank->getMainObject()->getTransform());
            std::stringstream stream;
            stream <<"cell x: "<< j << ", y: " << i;
            obj->name = stream.str();
        	Cell * c = new Cell();
        	obj->addComponent(c);
            cells[i][j] = c;
            c->setColumn(j);
            c->setRow(i);

            int k = getIntForCoordinate(i,j);
            if(k > 15 || k < 0){
                std::cout << "int for coord = " << k << ", is corrupted at coordinates " << i << "," << j << std::endl;
            }
            outstr << k << " , ";
            Object * objToInstantiate = getObjectForInt(k);

            //ringwall
            /*if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1){
            	Object * extraWall = objectBank->getWall_01();
				extraWall->getTransform()-> setParent(objToInstantiate->getTransform());
				extraWall->getTransform()->setPosition(glm::vec3(0,-1.02,0));

            }
            */
            c->initialize(objToInstantiate);
            setupCellForInt(k, *c);

        }
    }
    //std::cout << outstr.str() << std::endl;

    for(int i = 0; i < HEIGHT; i++){
        outstr << i;
        for(int j = 0; j < WIDTH; j++){
            //outstr << cells[i][j]->getString();
            if(i - 1 >= 0)cells[i][j]->neighbours.push_back(cells[i-1][j]);
			if(i + 1 < HEIGHT)cells[i][j]->neighbours.push_back(cells[i+1][j]);
            if(j - 1 >= 0)cells[i][j]->neighbours.push_back(cells[i][j-1]);
            if(j + 1 < WIDTH)cells[i][j]->neighbours.push_back(cells[i][j+1]);
        }

    }

    pathTo(*cells[2][2]);
    //std::cout << outstr.str();
}

void CellManager::initiatateCleanup(){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			cells[i][j]->object->onDestroy(); //mark content of cell for destroy
			cells[i][j] = NULL;
		}
	}


}
void CellManager::loadLevel(const Level * level){
	assert(initialized && level != NULL);
	currentLevel = level;
	generate();
	levelComplete = false;

}
const Level * CellManager::getCurrentLevel()const{
	return currentLevel;
}

const Plane * CellManager::getCellPlane()const{
	return cellPlane;
}

int CellManager::getIntForCoordinate(int i, int j) const{
	return currentLevel->levelArray[i][j];
}
void CellManager::setupCellForInt(const int i, Cell & cell){
	Destructable * destructable = NULL;
	bool addFloor = false;
    if(i > 15 || i < 0){
        std::cout << "int for coord = " << i <<  std::endl;
    }

	switch(i){
		case 0:
			//wall 1

			break;
		case 1:
			//wall 2

			break;
        case 2:
			//floor tile 1
            cell.setTraversable(true);
            break;
        case 3:
			//floor tile 2
            cell.setTraversable(true);
            break;
        case 4:
			//laser grid
			addFloor = true;


            break;
        case 5:
			//powernode main
			destructable = (Destructable*) cell.getContent()->getComponent("Powernode");
            cell.destructable = destructable;
            addFloor = true;
            break;
        case 6:
			//powernode turret
			destructable = (Destructable*) cell.getContent()->getComponent("Powernode");
            cell.destructable = destructable;
            addFloor = true;
            break;
        case 7:
			//powernode laser
			destructable = (Destructable*) cell.getContent()->getComponent("Powernode");
            cell.destructable = destructable;
            addFloor = true;
            break;
        case 8:
            //turret slow
            destructable = (Destructable*) cell.getContent()->getComponent("Turret");
            cell.destructable = destructable;
            addFloor = true;
            break;
        case 9:
            //turret medium
           destructable = (Destructable*) cell.getContent()->getComponent("Turret");
            cell.destructable = destructable;
            addFloor = true;
            break;
        case 10:
            //turret fast
            destructable = (Destructable*) cell.getContent()->getComponent("Turret");
            cell.destructable = destructable;
            addFloor = true;
            break;
        case 11:
            //empty object

            //std::cout << "Tried creating an empty object (Case 11)" << std::endl;
            break;
        case 12:
            //wall corner piece
            cell.getContent()->getTransform()->rotate(270, glm::vec3(0,1,0));
            addFloor = true;
            break;
        case 13:
            //wall corner piece
            cell.getContent()->getTransform()->rotate(180, glm::vec3(0,1,0));
            addFloor = true;

            break;
        case 14:
            cell.getContent()->getTransform()->rotate(90, glm::vec3(0,1,0));
            //wall corner piece
            addFloor = true;

            break;
        case 15:
            cell.getContent()->getTransform()->rotate(0, glm::vec3(0,1,0));
            //wall corner piece
            addFloor = true;

            break;

		default:
			std::cout << i << "is not known --------------------------------------" << std::endl;
			//assert(i == 0); //<-- throw an error here when a value is used that is not linked to an object
			addFloor = true;
			break;
	}
	if(addFloor){
        Object * floorTile = objectBank->getFloortile_01();
        //floorTile->getTransform()->setPosition(cell.getPosition());
        cell.addExtraFloor(floorTile);
	}
}
Object * CellManager::getObjectForInt(int i)const{
	Object * obj = NULL;
	//std::cout << "getting object for coordinate " << i << ", " << j << "wich should be " << currentLevel->levelArray[i][j]<<  std::endl;
    if(i > 15 || i < 0){
        std::cout << "int for coord = " << i << std::endl;// << ", is corrupted at coordinates " << i << "," << j << std::endl;
    }
	switch(i){
		case 0:
			obj = objectBank->getWall_01();
			break;
		case 1:
			obj = objectBank->getWall_02();
			break;
        case 2:
            obj = objectBank->getFloortile_01();
            break;
        case 3:
            obj = objectBank->getFloortile_02();
            break;
        case 4:
            obj = objectBank->getLasergrid();
            break;
        case 5:
            obj = objectBank->getPowerNode_main();
            break;
        case 6:
            obj = objectBank->getPowerNode_turret();
            break;
        case 7:
            obj = objectBank->getPowerNode_laser();
            break;
        case 8:
            obj = objectBank->getTurret_slow();
            break;
        case 9:
            obj = objectBank->getTurret_medium();
            break;
        case 10:
            obj = objectBank->getTurret_fast();
            break;
        case 11:
            obj = objectBank->getEmptyObject();
            obj->name = "empty";
            //std::cout << "Tried creating an empty object (Case 11)" << std::endl;
            break;
        case 12:
            obj = objectBank->getWallCorner();
            break;
        case 13:
            obj = objectBank->getWallCorner();
            break;
        case 14:
            obj = objectBank->getWallCorner();
            break;
        case 15:
            obj = objectBank->getWallCorner();
            break;

		default:
		std::cout << i << " is not known ----------------------- lasergrid placed" << std::endl;
            obj = objectBank->getLasergrid(); //debug to find the weird value
			//assert(i == 0); //<-- throw an error here when a value is used that is not linked to an object
			break;
	}

	assert(obj != NULL);
	return obj;
}
bool CellManager::getCell(const Ray & ray, Cell *& cell){

	assert(cellPlane != NULL); // << wtf

	float distance;
	if(cellPlane->raycast(ray, distance)){
		glm::vec3 hitpos = ray.getPoint(distance);
		if(isInBounds(hitpos)){
			int x = round(hitpos.x / CellManager::CELLSIZE);
			int z = round(hitpos.z / CellManager::CELLSIZE);
			//assert(cells[z] != NULL);
			cell = cells[z][x];
			//std::cout << hitpos << " hits " << cell << std::endl;
			return true;
		}
		else{
			//point is outside of the field of cells
			return false;
		}
	}

	//ray is perpendicular to the plane.
	return false;

}
Cell * CellManager::getCell(const Ray & ray){

    assert(cellPlane != NULL);

    Cell * out = NULL;
	float distance;
	if(cellPlane->raycast(ray, distance)){
		glm::vec3 hitpos = ray.getPoint(distance);
		if(isInBounds(hitpos)){
			int x = round(hitpos.x / CellManager::CELLSIZE);
			int z = round(hitpos.z / CellManager::CELLSIZE);
			out = cells[z][x];
			//std::cout << hitpos << " hits " << cell << std::endl;
		}
	}
	return out;
}
void CellManager::debugCells(){
	for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
			cells[i][j]->debugColor();
}
Cell * CellManager::getCell(const int x, const int z){
	if(x < 0 || x >= WIDTH || z < 0 || z >= HEIGHT) return false;
	else{
		return cells[x][z];
	}
}
bool CellManager::isInBounds(const glm::vec3 & toCheck) const{
	//make sure the position to check is within the limits of the map
	if(toCheck.x >= -(CELLSIZE /2) && toCheck.x <= CELLSIZE * WIDTH - CELLSIZE /2 && toCheck.z >= -(CELLSIZE /2) && toCheck.z <= CELLSIZE * HEIGHT - CELLSIZE / 2){
		return true;
	}
	return false;

}
void CellManager::onPowernodeMainDestroy(){
	std::cout << "level complete "<< std::endl;
	levelComplete = true;
}
void CellManager::pathTo(Cell & cell){
	for(int i = 0; i < HEIGHT; i ++){
		for(int j = 0 ;j < WIDTH; j++){
			cells[i][j]->distanceValue = 9999;
		}
	}
	cell.setDistanceValue(0);
}
void CellManager::resetCellColors(){
    for(int i = 0; i < WIDTH; i ++){
        for(int j = 0; j < HEIGHT; j++){
            cells[i][j]->changeColor(glm::vec4(1,1,1,1));
        }
    }
}

