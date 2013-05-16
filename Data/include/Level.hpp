#ifndef LEVEL_H
#define LEVEL_H


#include <string>
#include <vector>

class Level
{
	public:
		Level(std::string levelName, int comicInt, int levelNumber,std::string themeName, int themeNumber, int budget);
		virtual ~Level();
		static const int WIDTH = 20;
		static const int HEIGHT = 20;

		std::string levelName;
		int comicInt;
		int levelNumber;

		std::string themeName;
		int themeNumber;

		typedef std::vector<int> IntVec;

		std::vector<IntVec> levelArray;

		//int levelArray[WIDTH][HEIGHT];
		int budget;

	protected:
	private:
		Level(const Level& other){}
		Level& operator = (const Level& other){return *this;}
};

#endif // LEVEL_H
