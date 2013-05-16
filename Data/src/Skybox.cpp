#include "Skybox.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <assert.h>

Skybox::Skybox()
{
	//ctor
	textures = std::vector<Texture *> (6);
	sidesSet = std::vector<bool>(6);



}

Skybox::~Skybox()
{
	//dtor

}

Skybox::Skybox(const Skybox& other)
{
	//copy ctor
}

Skybox& Skybox::operator=(const Skybox& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	return *this;
}
void Skybox::draw(){
	if(checkComplete()){
//set uvs
//set vertices
//set normals

	}
	else{
		std::cout << "skybox is not complete" << std::endl;
	}
}
void Skybox::setTexture(Side side, Texture * tex){
	assert(tex != NULL);

	textures[side] = tex;
	sidesSet[side] = true;

}
bool Skybox::checkComplete(){
	for(unsigned int i = 0; i < sidesSet.size(); i++)
		if(sidesSet[i] == false) return false;

	return true;
}
