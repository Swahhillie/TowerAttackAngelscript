#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


#include "Time.hpp"
#include "ShaderProgram.hpp"
#include "ShaderLoader.hpp"
#include "Texture.hpp"

#include "GeneralFunctions.hpp"


ShaderProgram::ShaderProgram(GLuint programId_):programId(programId_) {
	getVariableLocations();
	lightPosition = glm::vec3(10,10,10);
	ambientLight = glm::vec3(.30f,0.30f,.30f);
	shininess = 1.0f;
}

ShaderProgram::~ShaderProgram() {
    //glUseProgram ( 0 );
    //glDeleteProgram( programId );
    std::cout << "destructed shader " << std::endl;
}

void ShaderProgram::use() {
    glUseProgram (programId);
	glUniformMatrix4fv ( projectionLocation, 1, GL_FALSE, glm::value_ptr( projectionMatrix ) );
	glUniformMatrix4fv (viewLocation, 1, GL_FALSE, glm::value_ptr( viewMatrix ) );
	glUniformMatrix4fv ( modelLocation, 1, GL_FALSE, glm::value_ptr( modelMatrix ) );
    glUniform3fv ( lightDirectionLocation, 1, glm::value_ptr( lightDirection ) );
    glUniform3fv (lightPositionLocation, 1, glm::value_ptr(lightPosition));
    glUniform3fv(ambientLightLocation, 1, glm::value_ptr(ambientLight));
    glUniform1f(shininessLocation, shininess);
}

void ShaderProgram::getVariableLocations() {
    modelLocation 			= glGetUniformLocation( programId, "modelMatrix" );
    viewLocation 			= glGetUniformLocation( programId, "viewMatrix" );
    projectionLocation 		= glGetUniformLocation( programId, "projectionMatrix" );

    lightDirectionLocation 	= glGetUniformLocation( programId, "lightDirection" );
    lightPositionLocation   = glGetUniformLocation(programId, "_LightPosition");

    texLocations.push_back(glGetUniformLocation( programId, "_mainTex" ));

    texLocations.push_back(glGetUniformLocation( programId, "_altTex" ));



	colorLocation			= glGetUniformLocation(programId, "_Color");
    vertexLocation			= glGetAttribLocation( programId, "vertex" );
    uvLocation 				= glGetAttribLocation( programId, "uv" );
    normalLocation 			= glGetAttribLocation( programId, "normal" );
    timeLocation 			= glGetUniformLocation( programId, "time");
    ambientLightLocation	= glGetUniformLocation(programId, "_AmbientLight");
    specularColorLocation 	= glGetUniformLocation(programId, "_SpecularReflection");
    specularLightLocation 	= glGetUniformLocation(programId, "_SpecularLight");
    shininessLocation       = glGetUniformLocation(programId, "_Shininess");
    borderWidthLocation		= glGetUniformLocation(programId, "borderWidth");
	progressLocation		= glGetUniformLocation(programId, "progress");

    //offsetLocation			= glGetUniformLocation(programId, "offset");
    //std::cout << vertexLocation << ", " << uvLocation << " , "  << normalLocation << ", " << texLocation << ", <- v, vt, vn, tex locations";
}

void ShaderProgram::setProjectionMatrix( const glm::mat4 & projectionMatrix_ ) {
	projectionMatrix = projectionMatrix_;

}

void ShaderProgram::setViewMatrix( const glm::mat4 & viewMatrix_ ) {
	viewMatrix = viewMatrix_;

}

void ShaderProgram::setModelMatrix( const glm::mat4 & modelMatrix_ ) {
	modelMatrix = modelMatrix_;
}

void ShaderProgram::setLightDirection( const glm::vec3 & lightDirection_ ) {
	lightDirection = lightDirection_;
}
void ShaderProgram::setBorderWidth(const float & borderWidth){
	glUniform1f(borderWidthLocation, borderWidth);
}
void ShaderProgram::setProgress(const float & progress){
	glUniform1f(progressLocation, progress);
}
void ShaderProgram::setColor(glm::vec4 & theColor){
	glUniform4fv(colorLocation,  1, glm::value_ptr(theColor));
}
void ShaderProgram::setSpecularReflection(glm::vec3 & theColor){
	glUniform3fv(specularColorLocation, 1, glm::value_ptr(theColor));
	glUniform3fv(specularLightLocation, 1, glm::value_ptr(theColor));
}
void ShaderProgram::setTime(){
	glUniform1f(timeLocation, Time::currentTime);
	//glUniform2fv(offsetLocation, 1)
}
void ShaderProgram::setTextures(const std::vector<Texture *> & textures ) {
    int texZero = (int)(GL_TEXTURE0);
    assert(textures.size() <= texLocations.size()); // cant allocate more textures than there are tex locations available
    for(unsigned int i = 0 ; i < textures.size(); i++ ){

        glActiveTexture(texZero + i);

        Texture * t = textures[i];

        int textureType = t->cubeMap? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
        glBindTexture( textureType, t->textureId );
        glUniform1i ( texLocations[i], i );
       //if(textures.size() == 2)
       //std::cout << texLocations[i]<< " id " << textures[i]->textureId << std::endl;

    }
	glActiveTexture(texZero);

}

void ShaderProgram::setVertices( std::vector<glm::vec3> & vertices ) {
    glEnableVertexAttribArray( vertexLocation );
    glVertexAttribPointer( vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0][0] );
}

void ShaderProgram::setNormals( std::vector<glm::vec3> & normals ) {
    glEnableVertexAttribArray( normalLocation );
    glVertexAttribPointer( normalLocation, 3, GL_FLOAT, GL_FALSE, 0, &normals[0][0] );
}
void ShaderProgram::setUvs( std::vector<glm::vec2> & uvs ) {
    glEnableVertexAttribArray( uvLocation );
    glVertexAttribPointer( uvLocation, 2, GL_FLOAT, GL_FALSE, 0, &uvs[0][0] );
}
void ShaderProgram::bindVertexVbo(GLuint & vboHandle){
	//std::cout << "binding the vertex vao "<< vaoHandle << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glEnableVertexAttribArray( vertexLocation );
	glVertexAttribPointer(vertexLocation,3,GL_FLOAT, GL_FALSE, 0, 0);
}
void ShaderProgram::bindNormalVbo(GLuint & vboHandle){

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glEnableVertexAttribArray( normalLocation );
	glVertexAttribPointer(normalLocation,3,GL_FLOAT, GL_FALSE, 0, 0);
}
void ShaderProgram::bindUvs(GLuint & vboHandle){
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glEnableVertexAttribArray( uvLocation );
	glVertexAttribPointer(uvLocation,2,GL_FLOAT, GL_FALSE, 0, 0);
}
void ShaderProgram::unbindVertexVao(){
	glBindVertexArray(0);
}
void ShaderProgram::unbindNormalVao(){
	glBindVertexArray(0);
}
void ShaderProgram::unsetVertices() {
    glDisableVertexAttribArray( vertexLocation );
}
void ShaderProgram::unsetNormals() {
    glDisableVertexAttribArray( normalLocation );
}
void ShaderProgram::unsetUvs() {
    glDisableVertexAttribArray( uvLocation );
}
void ShaderProgram::unsetTexture(){
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture( GL_TEXTURE_2D, 0 );
//	glUniform1i ( 0 , 0 );

}
void ShaderProgram::draw( unsigned int count ) {
    glDrawArrays( GL_TRIANGLES, 0, count );
}
glm::vec3 ShaderProgram::lightPosition;
glm::mat4 ShaderProgram::modelMatrix;
glm::mat4 ShaderProgram::projectionMatrix;
glm::mat4 ShaderProgram::viewMatrix;
glm::vec3 ShaderProgram::lightDirection;
glm::vec3 ShaderProgram::ambientLight;
float ShaderProgram::shininess;
