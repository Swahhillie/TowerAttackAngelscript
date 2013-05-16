#include "ShaderLoader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "StringOperations.hpp"
#include "ShaderProgram.hpp"

ShaderLoader::ShaderLoader()
{
	//ctor
	//this will find the names of all the shaders that need to be compiled and look for its code.
	//it will then generate the shader objects and store them in a map.

	std::vector<std::string> shaderNames; //vector of strings where the individual shader names will sit.

	std::string directory = "shaders\\"; //directory where to find the shadernames text file
	std::string shaderNameFilePath = directory + "shaderNames.txt";
	std::string rawShaderNames = StringOperations::readFile(shaderNameFilePath);
	parseShaders(shaderNames, rawShaderNames);//splits the shader names up by ';' and puts them in the vector.
	for(unsigned int i = 0; i < shaderNames.size(); i++){
		std::string vertexShader = directory + shaderNames[i] + ".VertexShader";
		std::string fragmentShader = directory + shaderNames[i] + ".FragmentShader";
		std::cout << "vertex = " << vertexShader << ", " << "fragment =" << fragmentShader << std::endl;
		GLuint programId = load(vertexShader.c_str(), fragmentShader.c_str());
		ShaderProgram * theShader = new ShaderProgram(programId);
		shaderObjects.insert(std::pair<std::string, ShaderProgram *>(shaderNames[i], theShader));
	}
	std::map<std::string, ShaderProgram *>::iterator it = shaderObjects.begin();
	std::cout << "stored " << shaderObjects.size() << " shaders " << std::endl;
	for( ;it != shaderObjects.end(); ++it){
		std::cout << it->first << " has number " << it->second << std::endl;
	}
}

ShaderLoader::~ShaderLoader()
{
	//dtor

}

ShaderProgram * ShaderLoader::getShader(const std::string & shaderName){
	//get the shader pointer out of the map by name
	std::map<std::string, ShaderProgram *>::iterator it = shaderObjects.find(shaderName);
	if(it != shaderObjects.end()){
		//std::cout << "found shader with name " << shaderName << ", with number " << it->second << std::endl;
		return it->second;
	}
	else{
		std::cout << "There is no shader object with the name "<< shaderName << std::endl;
		return 0;
	}
}
void ShaderLoader::parseShaders(std::vector<std::string> &shaderNamesOut, std::string shaderNames){
	StringOperations::myReplace(shaderNames, "\n", "");
    shaderNamesOut = StringOperations::split(shaderNames, ';');

	std::cout << "shaders to be compiled : " <<std::endl;
	for(unsigned int i = 0; i < shaderNamesOut.size(); i ++){
		std::cout << "->" << shaderNamesOut[i] << std::endl;
	}
}


GLuint ShaderLoader::load(  const char * vertexFileName, const char * fragmentFileName ) {

    std::string vertexCode   = StringOperations::readFile ( vertexFileName );
    GLuint vertexShaderId   = compileShader( GL_VERTEX_SHADER, vertexCode );

    std::string fragmentCode = StringOperations::readFile ( fragmentFileName );
    GLuint fragmentShaderId = compileShader( GL_FRAGMENT_SHADER, fragmentCode );

	GLuint programId = 0;
    if ( vertexShaderId && fragmentShaderId ) { // all is ok

        programId = linkProgram( vertexShaderId, fragmentShaderId ); // remember program by id


        glDeleteShader( vertexShaderId );	// free shader resources
        glDeleteShader( fragmentShaderId );	// free shader resources
    } else {
        programId = 0; // no program on error
    }
    return programId;
}
// compile the code, and detect errors.
GLuint ShaderLoader::compileShader( GLenum type, std::string & shaderCode) {
    //std::cout << "Compiling shader " << std::endl;

    // Compile Vertex Shader
    const char * codePointer = shaderCode.c_str();
    GLuint shaderId = glCreateShader( type  ); // get shader id
    glShaderSource( shaderId, 1, &codePointer , NULL );
    glCompileShader( shaderId );

    // Check compiler result
    GLint result = GL_FALSE;
    glGetShaderiv( shaderId, GL_COMPILE_STATUS, &result);
    //std::cout << "Tried " << result << std::endl;


    if ( result ) {
        //std::cout << "Shader compiled ok" << std::endl;
        return shaderId;
    } else { // get error message
        int count;
        glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &count);
        //std::vector<char> errorMessage( count+1 );
        char errorMessage[ count+1 ];
        glGetShaderInfoLog( shaderId, count, NULL, errorMessage);
        std::cout << errorMessage << std::endl;
        return 0; // no shader id
    }
}


// link the two shaders and return the program id
GLuint ShaderLoader::linkProgram ( GLuint vertexShaderId, GLuint fragmentShaderId ) {
    // Link the program
    GLuint programId = glCreateProgram();
    glAttachShader( programId, vertexShaderId);
    glAttachShader( programId, fragmentShaderId);
    glLinkProgram( programId);

    // Check the program
    GLint result = GL_FALSE;
    glGetProgramiv( programId, GL_LINK_STATUS, &result );
    if ( result ) {
        std::cout << "program linked ok" << std::endl;
        return programId;
    } else { // error, show message
        int count;
        glGetProgramiv( programId, GL_INFO_LOG_LENGTH, &count );
        //std::vector<char> ProgramErrorMessage( max(count, int(1)) );
        char errorMessage[ count+1 ];
        glGetProgramInfoLog( programId, count, NULL, errorMessage );
        std::cout << errorMessage << std::endl;
        return 0;
    }
}




