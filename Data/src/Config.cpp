#include "Config.hpp"
#include "StringOperations.hpp"
#include <vector>
#include <sstream>
#include <assert.h>
#include <sstream>
#include "GeneralFunctions.hpp"

Config::Config()
{
	readSettings();//ctor
	readComicsSets();
	readComics();
	readAnimations();
}

Config::~Config()
{
	//dtor
	std::cout << "destoyed the config class, end of game " << std::endl;
}

void Config::readSettings(){
	settingsString = StringOperations::readFile("assets\\settings\\gameSettings.txt");
	parseSettings(settingsString);
}
void Config::readComicsSets(){
	comicSetsString = StringOperations::readFile("assets\\settings\\comicSets.txt");
	parseComicSets(comicSetsString);
}
void Config::readComics(){
    comicString = StringOperations::readFile("assets\\settings\\comics.txt");
    parseComics(comicString);
}
void Config::getSetting(const std::string & fieldName, std::string & value)const{
	std::map<const std::string, std::string>::const_iterator it = settings.find(fieldName);
	if(it == settings.end())std::cout <<" no setting with name " << fieldName << std::endl;
	assert(it != settings.end());
	value = it->second;
	StringOperations::myReplace(value, "_", " ");
}
void Config::getSetting(const std::string & fieldName, float & value)const{

	auto it = settings.find(fieldName);
	if(it == settings.end())std::cout <<" no setting with name " << fieldName << std::endl;
	assert(it != settings.end()); //key must be in the map

	std::string str = it->second;
	std::stringstream strStream(str);
	strStream >> value;
}
int Config::getSetting(const std::string & fieldName)const{
    int value = 0;
    std::map<const std::string, std::string>::const_iterator it = settings.find(fieldName);
	if(it == settings.end())std::cout <<" no setting with name " << fieldName << std::endl;
	assert(it != settings.end()); //key must be in the map

	std::string str = it->second;
	std::stringstream strStream(str);
	strStream >> value;
	return value;
}
void Config::getSetting(const std::string & fieldName, glm::vec3 & pos)const{
        std::map<const std::string, std::string>::const_iterator it = settings.find(fieldName);

        if(it == settings.end())std::cout <<" no setting with name " << fieldName << std::endl;
        assert(it != settings.end()); //key must be in the map

        std::string str = it->second;

        std::vector<std::string> xyz = StringOperations::split(str, '/');
        glm::vec3 point;
        assert(xyz.size() == 3);
        std::vector<float> aaa(3);
        for(unsigned int k = 0; k < xyz.size(); k++){
            std::stringstream sstream;
            sstream << xyz[k];
            sstream >> aaa[k];
        }
        point.x = aaa[0];
        point.y = aaa[1];
        point.z = aaa[2];
}
void Config::getSetting(const std::string & fieldName, unsigned int & value)const{
    std::map<const std::string, std::string>::const_iterator it = settings.find(fieldName);

    if(it == settings.end())std::cout <<" no setting with name " << fieldName << std::endl;
    assert(it != settings.end()); //key must be in the map


	std::string str = it->second;
	std::stringstream strStream(str);
	strStream >> value;

}
void Config::getSetting(const std::string & fieldName, bool & value)const{
    std::map<const std::string, std::string>::const_iterator it = settings.find(fieldName);
    if(it == settings.end())std::cout <<" no setting with name " << fieldName << std::endl;
    assert(it != settings.end()); //key must be in the map

	std::string str = it->second;
	std::stringstream strStream(str);
	strStream >> value;

}
void Config::parseSettings(const std::string & settingsText){
	std::string cleanString = settingsText;
	//remove all formatting
	StringOperations::myReplace(cleanString, " ", "");
	StringOperations::myReplace(cleanString, "\n", "");

	std::vector<std::string > settingsSplit = StringOperations::split(cleanString, ';');
	std::cout<< "settings read from file: " << std::endl;
	std::string::iterator it;
	for(unsigned int i = 0; i < settingsSplit.size(); i++){

		std::vector<std::string> thePair = StringOperations::split(settingsSplit[i], '=');
		settings.insert(std::pair<const std::string, std::string>(thePair[0],thePair[1]));
		std::cout << "\t->" <<thePair[0] << std::endl <<"\t\t= " << thePair[1] << std::endl;

	}
}
void Config::parseComics(const std::string & comicsString){
    std::string cleanString = comicsString;
	//remove all formatting
	StringOperations::myReplace(cleanString, " ", "");
	StringOperations::myReplace(cleanString, "\n", "");

	std::vector<std::string > settingsSplit = StringOperations::split(cleanString, ';');
	std::cout<< "comics read from file: " << std::endl;
	std::string::iterator it;
	for(unsigned int i = 0; i < settingsSplit.size(); i++){

		std::vector<std::string> thePair = StringOperations::split(settingsSplit[i], '=');
		//settings.insert(std::pair<const std::string, std::string>(thePair[0],thePair[1]));
		std::stringstream strStream(thePair[0]);
		int index = -1;
		strStream >> index;
		comicsOrdered.push_back(thePair[1]);
		std::cout << "comic " << index << " is " << comicsOrdered[index] << std::endl;
	}
}
void Config::parseComicSets(const std::string & comicsSetsString){
    std::string cleanString = comicsSetsString;
	//remove all formatting
	StringOperations::myReplace(cleanString, " ", "");
	StringOperations::myReplace(cleanString, "\n", "");

	std::vector<std::string > settingsSplit = StringOperations::split(cleanString, ';');
	std::cout<< "comics read from file: " << std::endl;
	std::string::iterator it;
	for(unsigned int i = 0; i < settingsSplit.size(); i++){

		std::vector<std::string> thePair = StringOperations::split(settingsSplit[i], '=');
		//settings.insert(std::pair<const std::string, std::string>(thePair[0],thePair[1]));

		std::vector<std::string> comicSetsStrings = StringOperations::split(thePair[1], ',');

		std::vector<int> ints;

		for(unsigned int j = 0; j < comicSetsStrings.size(); j ++){
            std::stringstream ss;

            ss << (comicSetsStrings[j]);
            int value = -1;
            ss >> value;
            ints.push_back(value);
            //std::cout << "set " << i << " val " << j << " = " << value << ", from string " << comicSetsStrings[j] << std::endl;
		}
		comicSets.push_back(ints);
	}
}
bool Config::getAnimation(const std::string & aniName, AnimData & data)const{
	for(unsigned int i = 0; i < animations.size(); i ++){
		if(animations[i].name == aniName){
			data = animations[i];
			return true;
		}
	}
	return false;
}
AnimData Config::getAnimation(const std::string & aniName)const{
	for(auto ani : animations){
		if(ani.name == aniName){
			return ani;
		}
	}
	AnimData blank;
	return  blank;
}
void Config::readAnimations(){
	std::string name = "";
	float time;
	std::string positionsString = "";
	glm::vec3 startLookAtPos;
	glm::vec3 endLookAtPos;

	std::vector<glm::vec3> positions;


	std::string animationsFullString = StringOperations::readFile("assets\\settings\\CameraAnimations.txt");
	StringOperations::myReplace(animationsFullString, " ", "");
	StringOperations::myReplace(animationsFullString, "\n", "");
	std::vector<std::string> lines = StringOperations::split(animationsFullString, ';');
	std::cout << "animation count = " << lines.size() << std::endl;
	for(unsigned int i = 0 ; i < lines.size(); i++){

		std::vector<std::string> positionsVsName = StringOperations::split(lines[i], '=');
		assert(positionsVsName.size() == 2);
		std::vector<std::string> nameAndTime = StringOperations::split(positionsVsName[0], ',');

		assert(nameAndTime.size() == 2);
		std::stringstream sstream2;
		sstream2 << nameAndTime[1];
		sstream2 >> time;
		name = nameAndTime[0];
		positionsString = "";
		positionsString = positionsVsName[1];
		std::vector<std::string> posses = StringOperations::split(positionsString, ',');
		for(unsigned int j = 0; j < posses.size(); j++){
			std::vector<std::string> xyz = StringOperations::split(posses[j], '/');
			glm::vec3 point;
			assert(xyz.size() == 3);
			std::vector<float> aaa(3);
			for(unsigned int k = 0; k < xyz.size(); k++){
				std::stringstream sstream;
				sstream << xyz[k];
				sstream >> aaa[k];
			}
			point.x = aaa[0];
			point.y = aaa[1];
			point.z = aaa[2];
			//std::cout << point << std::endl;
			positions.push_back(point);
		}
		startLookAtPos = positions[positions.size()-2];
		endLookAtPos = positions[positions.size()-1];
		std::cout << name << "animation has " << positions.size() << " elements" << std::endl;
		positions.pop_back();
		positions.pop_back();

		animations.push_back(AnimData(name, positions, startLookAtPos, endLookAtPos, time));
		positions.clear();

	}


}
std::string Config::getComicAdress(int index){
    assert(index >= 0 && index < comicsOrdered.size());
    return comicsOrdered[index];
}
int Config::getComicCount(){
    return comicsOrdered.size();
}
int Config::getComicSetCount(){
	return comicSets.size();
}
std::vector<int> & Config::getComicSet(int number){
    return comicSets[number];
}
