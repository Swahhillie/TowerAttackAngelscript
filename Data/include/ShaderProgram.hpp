#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include "ShaderLoader.hpp"

class Texture;

class ShaderProgram
{


	public: // functions
		ShaderProgram(GLuint programId);
		virtual ~ShaderProgram();

		void load( const char * vertexFileName, const char * fragmentFileName );
		void use();
		static void setProjectionMatrix( const glm::mat4 & aProjectionMatrix );
		static void setViewMatrix( const glm::mat4 & aProjectionMatrix );
		static void setModelMatrix( const glm::mat4 & aProjectionMatrix );
		static void setLightDirection( const glm::vec3 & lightDirection );
		void setTextures( const std::vector<Texture *> & textures );
		void setVertices( std::vector<glm::vec3> & vertices );
		void setNormals( std::vector<glm::vec3> & normals );
		void setUvs( std::vector<glm::vec2> & uvs );
		void unsetTexture();
		void setTime();
		void setColor(glm::vec4 & theColor);

		void setProgress(const float & progress);
		void setBorderWidth(const float & borderWidth);

		void setSpecularReflection(glm::vec3 & theColor);

		void bindVertexVbo(GLuint & vbo);
		void bindNormalVbo(GLuint & vbo);
		void bindUvs(GLuint & vbo);

		void unbindVertexVao();
		void unbindNormalVao();

		void draw( unsigned int count );
		void unsetVertices();
		void unsetNormals();
		void unsetUvs();

		GLuint getShader(std::string shaderName);

		static glm::vec3 lightPosition;
		static glm::mat4 modelMatrix;
		static glm::mat4 projectionMatrix;
		static glm::mat4 viewMatrix;
		static glm::vec3 lightDirection;
		static glm::vec3 ambientLight;



		static float shininess;

	private: // functions

		void getVariableLocations();


	private: // var locations
		GLuint programId;

		ShaderLoader * shaderLoader;
		// shader vars uniform
		GLuint modelLocation;
		GLuint viewLocation;
		GLuint projectionLocation;
		GLuint colorLocation;
		GLuint lightDirectionLocation;
		int lightPositionLocation;
		int ambientLightLocation;
		int specularColorLocation;
		int specularLightLocation;
		int shininessLocation;
		int borderWidthLocation;
		int progressLocation;
		std::vector<int> texLocations;

		//shader vars in
		GLuint vertexLocation; // programs location of shader in var vertex
		GLuint normalLocation; // programs location of shader in var normal
		GLuint uvLocation; // programs location of shader in var uv
		int timeLocation;

};
#endif // SHADERPROGRAM_H
