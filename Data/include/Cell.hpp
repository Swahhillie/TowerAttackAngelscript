#ifndef CELL_H
#define CELL_H
#include <string>
#include <sstream>
#include "Object.hpp"
#include <glm/glm.hpp>
#include "Component.hpp"
class Destructable;

class Cell : public Component
{
    public:
        Cell();
        virtual ~Cell();
		int distanceValue;
		virtual const std::string getName(){return "Cell";}
		std::vector<Cell *> neighbours;
		void setDistanceValue(int value);
        int getColumn()const;
        int getRow()const;
        glm::vec3 getPosition()const;
        Object * getContent()const;
        void setColumn(int c);
        void setRow(int r);
		void changeColor(glm::vec4 theColor);
		void initialize(Object* theContent);
        std::string getString()const;

		void occupy(const bool value);
		bool getOccupied()const{return occupied;}


        bool getTraversable()const{return traversable_;}
        void setTraversable(bool value){traversable_ = value;}

        Cell * lowestNeighbour();
        void addExtraFloor(Object * floor);

		void debugColor();
        Destructable * getDestructable()const;

		Destructable * destructable;

    protected:

    private:
		Cell(const Cell & other){/*NO*/}
		Cell& operator = (const Cell & other){/*NO*/return *this;}
		bool occupied;
		Object * extraFloor;
        bool traversable_;
		Object * theContent;
        int row_;
        int column_;
};

#endif // CELL_H
