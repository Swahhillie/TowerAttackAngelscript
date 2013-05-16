#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Component.hpp"
#include <sfml/graphics.hpp>
#include "Ray.hpp"

class ShaderProgram;

class Camera : public Component
{
	public:
		Camera(sf::RenderWindow & window);
		virtual ~Camera();
		void update();
		void draw();
		Ray ScreenPointToRay(const glm::vec2 & fromPos)const;
		glm::vec2 WorldPointToView(const glm::vec3 & fromPos)const;
		static Camera * main;
		virtual const std::string getName(){return "Camera";}
		void postDraw();

		//Ray getPickingRay();

	private:
		glm::mat4 projectionMatrix; // stores the projection
		glm::mat4 viewMatrix; // stores the lookat info
		sf::RenderWindow & window;
};

#endif // CAMERA_H
