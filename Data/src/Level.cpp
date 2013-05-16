#include "Level.hpp"
#include <iostream>
Level::Level(std::string levelName_, int comicInt_, int levelNumber_, std::string themeName_,int themeNumber_, int budget_):
	levelName(levelName_),
	comicInt(comicInt_),
	levelNumber(levelNumber_),
	themeName(themeName_),
	themeNumber(themeNumber_),
	budget(budget_)

{
	//ctor
	levelArray = std::vector<IntVec>(WIDTH);
	for(int i = 0; i < WIDTH; i++){
		levelArray[i] = IntVec(HEIGHT);
		for(int j = 0; j < HEIGHT; j++)
            levelArray[i][j] = -1;
	}
}

Level::~Level()
{
	//dtor
	//delete[] levelArray;
}
