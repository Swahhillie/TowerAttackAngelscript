#include "Cell.hpp"

#include "Transform.hpp"
#include "GeneralFunctions.hpp"
#include "RenderMaterial.hpp"
#include "CellManager.hpp"
#include "Time.hpp"
#include <Time.h>
#include "Destructable.hpp"

Cell::Cell():distanceValue(99999), destructable(NULL),occupied(false), extraFloor(NULL),traversable_(false), theContent(NULL),row_(0), column_(0)
{
    //ctor
}

Cell::~Cell()
{
    //dtor

}
void Cell::initialize(Object * newContent){
	float width = 1;
	float height = 1;
	glm::vec3 newPos = glm::vec3(column_ * height, 0 , row_ * width);
	theContent = newContent;
	object->getTransform()->setPosition(newPos);
	Transform * tr = theContent->getTransform();
	tr->setParent(object->getTransform());
}

void Cell::setColumn(int c){
    column_ = c;

}

void Cell::setRow(int r){
    row_ = r;
}

int Cell::getColumn()const{
    return column_;
}
int  Cell::getRow()const{
    return row_;
}
glm::vec3 Cell::getPosition()const{
    return object->getTransform()->getPosition();
}
Object * Cell::getContent()const{
	return theContent;
}
void Cell::changeColor(glm::vec4 color){
	if(theContent){
		if(theContent->getRenderMaterial()){

		theContent->getRenderMaterial()->color = color;
		//std::cout << "changed color to " << color << std::endl;
		}
	}
    if(extraFloor){
        extraFloor->getRenderMaterial()->color = color;
    }
}
std::string Cell::getString()const{
    //-std::string stringetje;
	//Transform * tr = theContent->getTransform();
   std::stringstream out;
   out << "cell(";
   out << column_;
   out << ",";
   out << row_;
   out << ")";
   return out.str();
}

void Cell::setDistanceValue(int value){
	if(value < distanceValue){
		distanceValue = value;
		for(unsigned int i = 0; i < neighbours.size(); i++){
			if(neighbours[i]->getTraversable()){
				neighbours[i]->setDistanceValue(distanceValue+1);
			}

		}
	}


}
Destructable * Cell::getDestructable()const{
	return destructable;
}
void Cell::occupy(const bool value){
	occupied = value;

}
void Cell::debugColor(){

	if(!traversable_){
		changeColor(glm::vec4(1,0,0,1));

	}
	else{
        changeColor(glm::vec4(0,1,0,1));
	}
}
Cell * Cell::lowestNeighbour(){
	Cell * out = this;
	for(unsigned int i = 0 ; i < neighbours.size();i++){
	    Cell * neighbour = neighbours[i];
		if(neighbour->distanceValue <= out->distanceValue && neighbour->getTraversable() && neighbour->getOccupied() == false){
		    if(neighbour->distanceValue == out->distanceValue){

		        srand(time(NULL));
                if(rand() % 2 == 1 && out != this){ //randomize route but prefer staying over moving
                    out = neighbour;
                }
		    }
		    else{
                out = neighbour;
		    }

		}
//		else{
//			if(occupied) std::cout << "rejected because it is occupied" << std::endl;
//		}
	}
	return out;
}
void Cell::addExtraFloor(Object * floor){
    floor->getTransform()->setParent(object->getTransform());
}
