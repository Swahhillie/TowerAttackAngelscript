#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <map>
class ShaderProgram;

class Texture
{
	public:
		Texture();
		virtual ~Texture();

		//void draw( ShaderProgram * shader );

		static Texture * load( const char * fileName );
		static Texture * loadCubemapTexture(const std::vector<std::string> & fileNames);
		static Texture * loadCubemapTexture(const std::string & right,
											const std::string & left,
											const std::string & up,
											const std::string & down,
											const std::string & front,
											const std::string & back);
	public:
		static Texture * loadedBefore(const char * fileName);
		GLuint textureId;
		bool cubeMap;

		static std::map<const char *, Texture *> loadedTextures;
};

#endif // TEXTURE_H
