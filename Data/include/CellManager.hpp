#ifndef CELLMANAGER_HPP
#define CELLMANAGER_HPP

#include "Component.hpp"
#include <vector>
#include "Cell.hpp"
#include "ObjectBank.hpp"
#include "Level.hpp"
#include "Ray.hpp"
#include "Plane.hpp"


class CellManager : public Component
{
    public:
        static CellManager & instance(){
        	static CellManager INSTANCE;
			return INSTANCE;
        }
        void init(ObjectBank * objectBank,const Level * firstLevel);
        virtual ~CellManager();

        static const int WIDTH = 20;
        static const int HEIGHT = 20;
        static const float CELLSIZE = 1.0f;
        void resetCellColors();
        void debugCells();
        const Plane * getCellPlane()const;

		const Level * getCurrentLevel()const;
		void initiatateCleanup(); //mark cell content for delete
		void loadLevel(const Level * level);
        void generate();


		bool levelComplete;
		void onPowernodeMainDestroy();
        void pathTo(Cell & cell);
        bool getCell(const Ray & ray, Cell *& foundCell);
        Cell * getCell(const int x, const int z);
        Cell * getCell(const Ray & ray);
        virtual const std::string getName(){return "CellManager";}


    protected:
    private:

		bool initialized;
		CellManager();
		Plane* cellPlane;
		bool isInBounds(const glm::vec3 & toCheck)const;
		ObjectBank * objectBank;
		const Level * currentLevel;

		Object * getObjectForInt(int i)const;
		int getIntForCoordinate(int i, int j)const;
		void setupCellForInt(int i, Cell & cell);

		typedef std::vector<Cell *> CellVector;

		std::vector<CellVector> cells;

		//Cell* cells [WIDTH][HEIGHT] ;

};
#endif // CELLMANAGER_HPP
