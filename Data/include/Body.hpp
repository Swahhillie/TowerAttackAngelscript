#ifndef BODY_H
#define BODY_H

#include <iostream>
#include <vector>
#include "Component.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include "RenderMaterial.hpp"
#include <map>
class ShaderProgram;
class Texture;

class Body : public Component
{
	public:
		Body();
		virtual ~Body();
        void setMesh(ShaderProgram * shaderProgram, bool withTexture);
        void unsetMesh(ShaderProgram & shaderProgram);
		//void draw(RenderMaterial * renderMaterial, bool withTexture);
		static Body * load( const char * fileName );
		unsigned int verticesSize();

		virtual const std::string getName(){return "Body";}


	private:
		static std::map<const char *, Body*> bodies;
		glm::vec4 color;
		std::vector< glm::vec3 > vertices; // alle the vertices
		std::vector< glm::vec3 > normals;
		std::vector< glm::vec2 > uvs;
		static void bufferBody(Body * body);
		GLuint vertexBuffers[3];
		GLuint theVao;
		bool useBuffers;

	friend class ObjLoader; // lets obj access private vars.
};

#endif // BODY_H
