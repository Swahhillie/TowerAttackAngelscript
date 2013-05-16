#ifndef SHADERPROGRAMLOADER_H
#define SHADERPROGRAMLOADER_H

#include <vector>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class ShaderProgram;

class ShaderLoader
{
	public:

		virtual ~ShaderLoader();
		static ShaderLoader& instance(){
			static ShaderLoader INSTANCE;
			return INSTANCE;
		}
		ShaderProgram * getShader(const std::string & shaderName);
	protected:
	private:
	//this map contains the used shaders
	ShaderLoader(); // <- - ctor. this is a singleton

	std::map<std::string, ShaderProgram *> shaderObjects;



	//get the shadernames from the attached file
	void getShadersToLoad(std::vector<std::string> & shaderNames);
	void parseShaders(std::vector<std::string>& seperatedShaders, std::string originalString);

	//load the files.
	GLuint load(const char * vertexFilename, const char * fragmentFileName);
	//read the files

	//compile the string
	GLuint compileShader( GLenum type, std::string & shaderCode);
	//link the strings as shader programs
	GLuint linkProgram ( GLuint vertexShaderId, GLuint fragmentShaderId );

	//some string manipulation to read the shader name file


};
#endif // SHADERPROGRAMLOADER_H
