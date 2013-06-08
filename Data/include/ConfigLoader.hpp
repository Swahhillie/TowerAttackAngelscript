#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
#include <json/json.h>
#include <vector>
#include <sfml/System.hpp>

class ConfigLoader : sf::NonCopyable
{
	public:
		static ConfigLoader & instance(){
			static ConfigLoader INSTANCE;
			return INSTANCE;
		}

		bool getBoolSetting(std::string key);
		float getFloat(std::string path);
		int getInt(std::string path);
		std::string getString(std::string path);
		std::vector<int> getIntArray(std::string path);
		std::vector<float> getFloatArray(std::string path);
		std::vector<std::string> getStringArray(std::string path);


	protected:
	private:
		ConfigLoader();
		virtual ~ConfigLoader();

		static const char * getConfigPath(){
			return "scripts\\config.json";
		}

		Json::Value root;
		Json::Reader reader;
		std::string getAllSettings();

		//from http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
		std::string get_file_contents(const char * fileName);
		Json::Value getObjectAtPath(std::string path);
};

#endif // CONFIGLOADER_H
