#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "Object.hpp"
#include "Transform.hpp"
#include "GeneralFunctions.hpp"
#include <sfml/graphics.hpp>

ShaderProgram * test;

Camera::Camera(sf::RenderWindow & window_):window(window_)
{
	projectionMatrix 	= glm::perspective( 45.0f, 4.0f/3.0f, 0.1f, 100.0f );
	viewMatrix = glm::mat4(1.0f);
	main = this;
	test = ShaderLoader::instance().getShader("Diffuse");

}

Camera::~Camera()
{
	//dtor
	if(Camera::main == this) main = NULL;
}
void Camera::update(){
	if(object->getTransform()->getParent()){

		Transform* tr = object->getTransform();
		glm::mat4 parentTransformation = tr->getParent()->getTransformation();
		glm::mat4 localTransformation = tr->getTransformation();

	    glm::mat4 mToView = glm::inverse(parentTransformation * localTransformation);

        viewMatrix = mToView;
//        viewMatrix = rotationOverX * viewMatrix;
//        viewMatrix 		= glm::lookAt( glm::vec3( 0.0f, 2.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
	}
	else{
        viewMatrix = glm::inverse(object->getTransform()->getTransformation());
    }
}


void Camera::draw()
{
	ShaderProgram::setProjectionMatrix( projectionMatrix ); // should be in camera
    ShaderProgram::setViewMatrix( viewMatrix ); // should be in camera
//    std::cout << "camera ::draw called " << std::endl;

}

void Camera::postDraw() {





	//std::cout << origin << std::endl;
	//std::cout << end << std::endl;
}
Ray Camera::ScreenPointToRay(const glm::vec2 & fromPos)const{

    //if the game window size is changed this will need to be updated
    sf::Vector2u windowSize = window.getSize();
    glm::vec2 screen = glm::vec2(windowSize.x,windowSize.y);



    //glm::mat4 inverseView = glm::inverse(viewMatrix);
    glm::mat4 inverseView = object->getTransform()->getTransformation();
    glm::vec3 point;
	point.x = -( 2.0f * fromPos.x / screen.x -1 ) / projectionMatrix[0][0];
	point.y =  ( 2.0f * fromPos.y / screen.y -1 ) / projectionMatrix[1][1];
	point.z =  1.0f;

    glm::vec3 origin = glm::vec3( inverseView * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) ); // get translation
    glm::vec3 direction = -glm::normalize( glm::vec3( inverseView * glm::vec4( point, 0.0f ) ) ); // get rotation and normalize dir
    Ray r = Ray(origin, direction);
    return r;
}
glm::vec2 Camera::WorldPointToView(const glm::vec3 & fromPos)const{
	//http://stackoverflow.com/questions/3792481/how-to-get-screen-coordinates-from-a-3d-point-opengl
	glm::vec2 p = glm::vec2(0,0);
	glm::vec4 homogeneous = projectionMatrix * viewMatrix * glm::vec4(fromPos, 1);
	homogeneous.x /= homogeneous.w; //projection divide
	homogeneous.y /= homogeneous.w; //projection divide
	homogeneous.z /= homogeneous.w; //projection divide
	// now it is in -1, 1 range
	sf::Vector2u windowSize = window.getSize();
    glm::vec2 screen = glm::vec2(windowSize.x,windowSize.y);

	p.x = screen.x * (homogeneous.x +1) /2;
	p.y = screen.y * (homogeneous.y +1) /2;
	return p;
}
Camera * Camera::main;
