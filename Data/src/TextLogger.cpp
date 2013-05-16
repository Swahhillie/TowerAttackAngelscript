#include "TextLogger.hpp"
#include <iostream>
#include <fstream>
#include "GeneralFunctions.hpp"

using namespace std;

TextLogger::TextLogger()

{
	//ctor

		checkpointPositions.open("checkpointPositions.txt", ios::out | ios::app);
		checkpointPositions << std::endl << "---" <<std::endl;
}

TextLogger::~TextLogger()
{
	//dtor
}
void TextLogger::addToLog(std::string str){
	checkpointPositions << str << std::endl;
}

void TextLogger::addToLog(glm::vec3 pos){
	checkpointPositions << pos.x << "/" << pos.y << "/" << pos.z << ",\t";
}
