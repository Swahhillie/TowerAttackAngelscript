#ifndef RENDERMATERIAL_H
#define RENDERMATERIAL_H

#include "Component.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Texture.hpp"
#include "Object.hpp"
#include "Body.hpp"

//class Body;

class RenderMaterial : public Component
{
	public:

		RenderMaterial();
		virtual ~RenderMaterial();

		void draw();

		glm::vec4 color;
		glm::vec3 reflectionColor;

		bool visible;
		float borderWidth;
		float progress;


		ShaderProgram * shaderProgram;
		Body * body;

		std::string usingShader;


		void addTexture(Texture * texture);
		void setShader(const std::string & shaderName);
		virtual const std::string getName(){return "RenderMaterial";}

	protected:
	private:
        std::vector<Texture *> textures;
};

#endif // RENDERMATERIAL_H
