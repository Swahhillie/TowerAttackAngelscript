#include "LevelLoader.hpp"
#include <sstream>
#include <assert.h>

LevelLoader::LevelLoader():currentLevel_(0),levelsDirectory("assets\\levels\\"),loadedLevel(NULL)
{
	//ctor
	std::cout << "-------------------" << std::endl;
	readLevelsFile();
	readThemesFile();
	std::cout << "levels available = " << getLevelCount() << std::endl;
	for(int i = 0; i < getLevelCount(); i++){
		 std::cout << availableLevels[i].first << ", ";
	}
	std::cout << std::endl;

	std::cout << "themes available = " << getThemeCount() << std::endl;
	for(int i = 0; i < getThemeCount(); i++){
		 std::cout << availableThemes[i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "-------------------" << std::endl;
}

LevelLoader::~LevelLoader()
{
	//dtor
}
void LevelLoader::parseLevelString(std::string levelString){
	assert(availableThemes.size() > 0);
	size_t found = levelString.find("theme=");
	if(found != std::string::npos){
		//found an occurance of "theme="
		std::stringstream convert;
		convert << (levelString[found + 6]);//assume the number after "theme= "will be the theme number;
		convert >> loadedLevel->themeNumber; //write the number into an int on the loaded level.
		std::cout << "read the number " << loadedLevel->themeNumber << " theme" << std::endl;
		levelString.erase(found, found + 7);//erase theme and number from the string so it can be processed
		assert(loadedLevel->themeNumber < availableThemes.size() && loadedLevel->themeNumber >= 0);
		loadedLevel->themeName = availableThemes[loadedLevel->themeNumber];
	}
	else{
		std::cout << "no theme specified in filestring, using default " << std::endl;
		loadedLevel->themeNumber = 0;
		loadedLevel->themeName = availableThemes[0];
	}
	StringOperations::myReplace(levelString, "\n", ""); //delete line breaks

	//std::cout<<levelString << std::endl;


	std::vector<std::string> explodedLevelstring = StringOperations::split(levelString, ',');
	std::cout << "split "<< loadedLevel->levelName << " in " << explodedLevelstring.size() << " elements " << std::endl;
	assert(explodedLevelstring.size() == WIDTH * HEIGHT);
	for(int i = 0; i < WIDTH * HEIGHT; i++){
		int w = i / WIDTH;
		int h = i % WIDTH;
		std::stringstream converter(explodedLevelstring[i]);
		int value;
		converter >> value;
		loadedLevel->levelArray[w][h] = value;
		//assert(value >= 0 && value <= 15);
		//std::cout<< "[" << w << "," << h << "](" << value << ")";
	}
	std::cout << "parsed level " << loadedLevel->levelName << " with theme " << loadedLevel->themeName << std::endl;

}

int LevelLoader::getLevelCount()const{
	return availableLevels.size();
}
int LevelLoader::getCurrentLevel()const{
	return currentLevel_;
}
int LevelLoader::getThemeCount()const{
	return availableThemes.size();
}

const Level * LevelLoader::load(int levelToLoad){
    if(loadedLevel != NULL){
        delete loadedLevel;
        loadedLevel = NULL;
    }

	assert(levelToLoad >= 0 && levelToLoad < availableLevels.size());
	int levelTheme = 0;
	loadedLevel = new Level(availableLevels[levelToLoad].first, availableLevels[levelToLoad].second[0],levelToLoad,"",levelTheme,availableLevels[levelToLoad].second[1]);
	assert(loadedLevel != NULL);
	std::string levelString = getLevelString(levelToLoad);
	parseLevelString(levelString);
	currentLevel_ = levelToLoad;
	return loadedLevel;
}
std::string LevelLoader::getLevelString(int levelToLoad){
	std::string nameOfFile = availableLevels[levelToLoad].first;
	nameOfFile = levelsDirectory + nameOfFile + ".txt";
	std::string levelString = StringOperations::readFile(nameOfFile);
	return levelString;
}
void LevelLoader::readLevelsFile(){
	std::string toRead = levelsDirectory + "levelNames.txt";
	std::string levelNames = StringOperations::readFile(toRead);

	assert(levelNames.size() > 0);

	StringOperations::myReplace(levelNames, "\n", "");
	std::vector<std::string> levelsWithComic = StringOperations::split(levelNames, ';');
	for(unsigned int i = 0 ; i < levelsWithComic.size(); i++){
		std::vector<std::string> levelComicPair = StringOperations::split(levelsWithComic[i], ',');
		int comicInt = 0;
		int budget =  0;
		std::stringstream converter(levelComicPair[1]);
		converter >> comicInt;
        std::stringstream converter2(levelComicPair[2]);
        converter2 >> budget;
        //int settings[2] = {comicInt, budget};
        Ints settings(2, 0);
        settings[0] = comicInt;
        settings[1] = budget;
		availableLevels.push_back(LevelPair(levelComicPair[0],settings));
		std::cout << levelComicPair[0] << " has comic " << comicInt << " and budget " << budget << std::endl;
	}

}
void LevelLoader::readThemesFile(){
	std::string toRead = levelsDirectory + "themeNames.txt";
	std::string themeNames = StringOperations::readFile(toRead);

	assert(themeNames.size() > 0);

	StringOperations::myReplace(themeNames, "\n", "");
	availableThemes = StringOperations::split(themeNames, ';');
}
