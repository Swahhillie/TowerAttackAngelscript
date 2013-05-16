#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Level.hpp"
#include <vector>
#include <map>
#include <string>
#include "StringOperations.hpp"


class LevelLoader
{
	public:
		LevelLoader();
		virtual ~LevelLoader();
		static const int WIDTH = 20;
		static const int HEIGHT = 20;

		int getLevelCount() const;
		int getCurrentLevel()const;

		int getThemeCount()const;

		const Level * load(int levelNumber);

	protected:
	private:
		//levels stored by name
		typedef std::vector<int> Ints;
		typedef std::pair<std::string, Ints> LevelPair;
		typedef std::vector<LevelPair> LevelVec;

		LevelVec availableLevels;

		int currentLevel_;
		const std::string levelsDirectory;

		std::vector<std::string> availableThemes;

		Level * loadedLevel;
		std::string getLevelString(int levelNumber);
		void readLevelsFile();
		void readThemesFile();
		void parseLevelString(std::string levelString);


};

#endif // LEVELLOADER_H
