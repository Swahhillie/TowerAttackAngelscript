#include <iostream>
#include <SFML/Graphics.hpp>

#include "Texture.hpp"
#include "ShaderProgram.hpp"
#include <map>

Texture::Texture():cubeMap(false)
{
}

Texture::~Texture()
{
	//dtor
}

Texture * Texture::load( const char * fileName )
{

	//Texture * tex = loadedBefore(fileName);
	//if(tex)return tex;
	std::map<const char *, Texture *>::iterator it = loadedTextures.find(fileName);
    if(it != loadedTextures.end()) {
//    	Texture * loadedTex  = loadedTextures.find(fileName)->second;
		//std::cout<<fileName << " has been loaded before " << std::endl;
        return loadedTextures.find(fileName)->second;
        //this prevents reading the files multiple times.
    }

	std::cout << "Loading Texture: " << fileName <<std::endl;
	sf::Image image;
	if ( image.loadFromFile( fileName ) ) {
		Texture * texture = new Texture();

		glGenTextures( 1, &texture->textureId ); // assign texture id
		glBindTexture( GL_TEXTURE_2D, texture->textureId );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glGenerateMipmap( GL_TEXTURE_2D );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4 );
		//std::cout << "Done loading Texture" << std::endl;

		loadedTextures[fileName] = texture;
		return texture;
	} else {
		std::cout << "Error loading texture image " << fileName << std::endl;
		return NULL;
	}

}
Texture * Texture::loadCubemapTexture(const std::vector<std::string> & fileNames){
	int type1 = GL_TEXTURE_CUBE_MAP_POSITIVE_X;

	Texture * texture = new Texture();

	glGenTextures(1, &texture->textureId); //generate a var
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->textureId); //bind a cube map to the var

	sf::Image * image = NULL;

	sf::Vector2u prevSize = sf::Vector2u(0,0);
	for(unsigned int i = 0 ; i < fileNames.size(); i++){
		image = new sf::Image();

		if(image->loadFromFile(fileNames[i])){
			//if textures are not the same size they will be displayed as black
			if(prevSize == sf::Vector2u(0,0)) prevSize = image->getSize();
			else assert(prevSize == image->getSize()); //make sure all textures are the same size

			glTexImage2D(type1 + i, 0, GL_RGB, image->getSize().x, image->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());

		}
		else{
			std::cout << "Error loading cubemap image " << fileNames[i] << std::endl;
			delete texture;
			texture = NULL;
			delete image;
			image = NULL;
			return NULL;
		}
		delete image;
		image = NULL;
	}
	//set proper texture parameters for a skybox
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	texture->cubeMap = true;
	return texture;

}
//convenience function
Texture * Texture::loadCubemapTexture(
	const std::string & posXFilename,
	const std::string & negXFilename,
	const std::string & posYFilename,
	const std::string & negYFilename,
	const std::string & posZFilename,
	const std::string & negZFilename
	){
	std::vector<std::string> fileNames;
	fileNames.push_back(posXFilename);
	fileNames.push_back(negXFilename);
	fileNames.push_back(posYFilename);
	fileNames.push_back(negYFilename);
	fileNames.push_back(posZFilename);
	fileNames.push_back(negZFilename);
	return loadCubemapTexture(fileNames);

}
Texture * Texture::loadedBefore(const char * fileName){
	std::map<const char *, Texture *>::iterator it = loadedTextures.find(fileName);
    if(it != loadedTextures.end()) {
//    	Texture * loadedTex  = loadedTextures.find(fileName)->second;
		//std::cout<<fileName << " has been loaded before " << std::endl;
        return loadedTextures.find(fileName)->second;
        //this prevents reading the files multiple times.
    } else {
		return NULL;

    }
}
std::map<const char *, Texture *> Texture::loadedTextures;

