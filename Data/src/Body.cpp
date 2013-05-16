#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GL/gl.h>


#include "Body.hpp"
#include "ShaderProgram.hpp"
#include "GeneralFunctions.hpp"

Body::Body()
    :	useBuffers(true)//           <--------------------------- SET THIS TO TRUE TO USE BUFFERS
    {

}

Body::~Body() {
    //dtor
    //crash the party, this should never be destroyed
    int a = 1;
    assert(a == 0);
    std::cout << " body destroyed " << std::endl;
}
void Body::setMesh(ShaderProgram * shaderProgram, bool withTexture){
    if(withTexture){
        if(!useBuffers)shaderProgram->setUvs(uvs);
        else shaderProgram->bindUvs(vertexBuffers[2]);
    }
    if(useBuffers){
        shaderProgram->bindVertexVbo(vertexBuffers[0]);
		shaderProgram->bindNormalVbo(vertexBuffers[1]);
    }
    else{
        shaderProgram->setVertices( vertices );
		shaderProgram->setNormals( normals );
    }
}
void Body::unsetMesh(ShaderProgram & shaderProgram){
    shaderProgram.unsetVertices();
    shaderProgram.unsetNormals();
    shaderProgram.unsetUvs();
}


Body * Body::load( const char * fileName) {
	/*
	loadedObjects contains a body pointer for every file name that is loaded.
	this prevents reading the files multiple times.
	the map is a static local variable, this means that it cannot be accessed from outside this function.

	*/
    //static std::map<const char *, Body *> loadedObjects;
    std::map<const char *, Body*>::iterator it= Body::bodies.find(fileName);
    //if(loadedObjects.find(fileName)->second) {
    if(it != Body::bodies.end()){
        //std::cout<<fileName << " has been loaded before " << std::endl;

        return Body::bodies.find(fileName)->second;

    } else {

        //std::cout <<"added " << fileName << "to map" << std::endl;
    }
    //std::cout << "Loading body from obj " << fileName << std::endl;


    std::ifstream file ( fileName, std::ios::in );

    if( file.is_open() ) { // file opened succesfully
        Body * body = new Body(); // the new body to be read into

        std::vector<glm::vec3> vertices; // for the indexed data
        std::vector<glm::vec3> normals; // for the indexed data
        std::vector<glm::vec2> uvs; // for the indexed data

        std::string line; // to store each line in
        while( getline( file, line ) ) { // as long as there are lines to be read
            char cmd[10]; // c-type string to store cmd
            sscanf ( line.c_str(), "%10s", cmd ); // get the first string in the line of max 5 chars (c-style)
            if ( strcmp ( cmd, "v" ) == 0 ) { // line with vertex
                glm::vec3 vertex;
                sscanf( line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z );
                vertices.push_back( vertex );
            } else if ( strcmp ( cmd, "vn" ) == 0 ) { // line with normal
                glm::vec3 normal;
                sscanf( line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z );
                normals.push_back( normal );
            } else if ( strcmp ( cmd, "vt" ) == 0 ) { // line with uv
                glm::vec2 uv;
                sscanf( line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y );
                uv.y = 1-uv.y;
                uvs.push_back( uv );
            } else if ( strcmp ( cmd, "f" ) == 0 ) { // line with face
                glm::ivec3 vertexIndex; // to store the indices
                glm::ivec3 uvIndex;
                glm::ivec3 normalIndex;
                int count = sscanf( line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if ( count == 10 ) { // there should be 10 args to be read
                    for ( int index = 0; index < 3; index++ ) { // make verticesArray out of indexed array
                        body->vertices.push_back( vertices[ vertexIndex[index]-1 ] ); //get the vertex according to index
                        body->uvs.push_back( uvs[ uvIndex[index]-1 ] ); //get the uv according to index
                        body->normals.push_back( normals[ normalIndex[index]-1 ] ); //get the normal according to index
                    }
                } else { // something is wrong
                    std::cout << "Error reading obj, needing v,vn,vt, in file"<< fileName << std::endl;
                    delete body; // free the mem from created body
                    return NULL; // no body read
                }
            }
        }
        file.close();
        //std::cout << "Done loading " << fileName << std::endl;
		bufferBody(body);
		Body::bodies[fileName] =body;
        return body;
    } else {
        std::cout << "Could not read " << fileName << std::endl;
        return NULL; // no body read
    }
}
void Body::bufferBody(Body*body){

	glGenBuffers(3, body->vertexBuffers);
	//std::cout << "buffer names used  " << body->vertexBuffers[0] << ", " << body->vertexBuffers[1] << ", "<< body->vertexBuffers[2]<< std::endl;
	//positions
	glBindBuffer(GL_ARRAY_BUFFER, body->vertexBuffers[0]);//bind the position buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * body->vertices.size(), &body->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//std::cout << "buffer for positions made" <<std::endl;
	//normals
	glBindBuffer(GL_ARRAY_BUFFER, body->vertexBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * body->normals.size(), &body->normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//std::cout << "buffer for normals made" <<std::endl;
	//uvs
	glBindBuffer(GL_ARRAY_BUFFER, body->vertexBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * body->uvs.size(), &body->uvs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//std::cout <<"buffers for uvs made" << std::endl;



}
unsigned int Body::verticesSize(){
    return vertices.size();
}
std::map<const char *, Body * > Body::bodies;
