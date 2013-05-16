#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <vector>
#include "AnimData.hpp"
#include <glm/glm.hpp>

class Config
{
	public:
		static Config& instance(){
			static Config INSTANCE;
			return INSTANCE;
		}
		virtual ~Config();
		void readSettings();
		/*
			look for setting in setting file and read it as a specific value;

			for example: get the amount of health of a wireCutterRobot from the settings file;
			-> robot.health = Config::instance.getSetting("wireCutterRobotHealth", float");

			if there is no field by that name, the program will be terminated.
		*/
		void getSetting(const std::string & fieldName, float & setting)const;
		void getSetting(const std::string & fieldName, std::string & text)const;
		void getSetting(const std::string & fieldName, glm::vec3 & pos)const;
		void getSetting(const std::string & fieldName, unsigned int & value)const;
		void getSetting(const std::string & fieldName, bool & value)const;
		int getSetting(const std::string & fieldName)const;

		bool getAnimation(const std::string & name, AnimData & data)const;
		AnimData getAnimation(const std::string & name)const;

		std::vector<int> & getComicSet(int setNumber);
        std::string getComicAdress(int index);

		int getComicCount();
		int getComicSetCount();
	protected:
	private:
        void readComics();
        void readComicsSets();
		void parseComics(const std::string & comicString);
		void parseComicSets(const std::string & comicSetsString);
		void readAnimations();
		std::string comicSetsString;
		std::string comicString;
		//std::map<const std::string, const std::string> comics;
		std::vector<std::string> comicsOrdered;
		typedef std::vector<int> intVec;
		std::vector<intVec> comicSets;
		std::vector<AnimData> animations;

		void parseSettings(const std::string & settingsString);
		std::string settingsString;
		std::map<const std::string, std::string> settings;


		Config();
};

#endif // CONFIG_H
