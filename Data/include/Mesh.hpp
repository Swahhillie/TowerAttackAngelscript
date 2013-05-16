#ifndef MESH_H
#define MESH_H


#include <map>
#include <vector>
#include <GL/glew.h>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

class Mesh
{
	public:
		Mesh();
		virtual ~Mesh();

		bool LoadMesh(const std::string& FileName);

		void Render();
	protected:

	private:
		bool InitFromScene(const aiScene * pScene, const std::string& FileName);
		void InitMesh(unsigend int Index, const aiMesh* paiMesh);
		bool InitMaterials(const aiScene* pScene, const std::string& FileName);
		void Clear();

	#define INVALID_MATERIAL_ 0xFFFFFFFF

		struct MeshEntry{
				MeshEntry();
				~MeshEntry();

				bool Init(const std::vector& Vertices, const std::vector& Indices);

				GLuint VB;
				GLuint IB;

				unsigned int NumIndices;
				unsigned int MaterialIndex;
		};

		std::vector m_Entries;
		std::vector m_Textures;


};

#endif // MESH_H
