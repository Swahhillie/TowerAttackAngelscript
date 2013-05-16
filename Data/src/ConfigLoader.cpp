#include "ConfigLoader.hpp"
#include <fstream>
#include <string>
#include <cerrno>
#include <assert.h>
#include <sstream>
#include "StringOperations.hpp"
ConfigLoader::ConfigLoader()
{
    //ctor
    std::cout << "about to parse " << getConfigPath() << std::endl;
    std::string configFileContent = get_file_contents(getConfigPath());

    //std::string configFileContent = StringOperations::readFile(std::string("scripts\\config.json"));


    bool parsingSuccessfull = reader.parse( configFileContent, root);
    if(parsingSuccessfull)
    {
    std::cout << "Parsing succesfull" << std::endl;

    }
    else{
		std::cout << "Failed to parse configuration \n"
                  << reader.getFormattedErrorMessages();

		sf::sleep(sf::seconds(5.0f));
		assert(parsingSuccessfull);
    }






}

ConfigLoader::~ConfigLoader()
{
    //dtor
}
bool ConfigLoader::getBoolSetting(std::string str)
{
    return root[str].asBool();
}
float ConfigLoader::getFloat(std::string path)
{
    return getObjectAtPath(path).asFloat();
}
std::string ConfigLoader::getString(std::string path)
{
    return getObjectAtPath(path).asString();
}
int ConfigLoader::getInt(std::string path)
{
    return getObjectAtPath(path).asInt();
}
std::vector<int> ConfigLoader::getIntArray(std::string path)
{
    Json::Value obj = getObjectAtPath(path);
    assert(obj.isArray());
    std::vector<int> ints(obj.size());
    for(unsigned int index = 0; index < obj.size(); index++)
    {
        assert(obj[index].isIntegral());
        ints[index] = obj[index].asInt();
    }
    return ints;

}

std::vector<float> ConfigLoader::getFloatArray(std::string path)
{
    Json::Value obj = getObjectAtPath(path);
    assert(obj.isArray());
    std::vector<float> floats(obj.size());
    for(unsigned int index = 0; index < obj.size(); index++)
    {
        assert(obj[index].isNumeric());
        floats[index] = obj[index].asFloat();
    }
    return floats;
}


std::vector<std::string> ConfigLoader::getStringArray(std::string path)
{
    Json::Value obj = getObjectAtPath(path);
    assert (obj.isArray());
    std::vector<std::string> strings(obj.size());
    for(unsigned int index = 0; index < obj.size(); index++)
    {
        assert(obj[index].isString());
        strings[index] = obj[index].asString();
    }
    return strings;
}


Json::Value ConfigLoader::getObjectAtPath(std::string path)
{
    assert(path.size() > 0);

    Json::Value obj = root;

    size_t last = 0;
    size_t found;

    while(true)
    {

        found = path.find(",", last);
        std::string test(path, last, found - last);
        last = found + 1;
        assert(obj.isMember(test));
        obj = obj[test];
        if(found == std::string::npos)break;
    }

    return obj;
}

std::string ConfigLoader::get_file_contents(const char *filename)
{
//http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}
