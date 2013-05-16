#include "RenderMaterial.hpp"
#include "Time.hpp"

RenderMaterial::RenderMaterial():color(glm::vec4(1,1,1,1)),visible(true), borderWidth(.1f), progress(.5f),shaderProgram(NULL), body(NULL)
{
	//ctor
	reflectionColor = glm::vec3(1,1,1);
	shaderProgram = ShaderLoader::instance().getShader("Specular");
	usingShader= "Specular";
}

RenderMaterial::~RenderMaterial()
{
	//texture class owns the texture pointers and is responsible for their memory
	// same for body and shaderprogram;
	//std::cout << "DEL RenMat, ";
}
void RenderMaterial::addTexture( Texture * aTexture ) {
	assert(aTexture != NULL);
	textures.push_back(aTexture);

}

void RenderMaterial::setShader(const std::string & shaderName){
	shaderProgram = ShaderLoader::instance().getShader(shaderName);
	usingShader = shaderName;
}

void RenderMaterial::draw(){
	//std::cout << usingShader << std::endl;
	if(!visible)return;
    if(body == NULL){
        if(object->getBody()){
            body = object->getBody();
        }
        else{
            return;
        }
    }
    //std::cout << " body = " << body << std::endl;
    shaderProgram->setTextures(textures);
    body->setMesh(shaderProgram, textures.size() > 0? true:false);

    shaderProgram->use();
	shaderProgram->setTime();
	shaderProgram->setColor(color);
	shaderProgram->setSpecularReflection(reflectionColor);
	shaderProgram->setBorderWidth(borderWidth);
	shaderProgram->setProgress(progress);
	shaderProgram->draw(body->verticesSize());
	shaderProgram->unsetTexture();
	body->unsetMesh(*shaderProgram);
}
