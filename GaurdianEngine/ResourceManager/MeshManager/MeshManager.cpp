#include "MeshManager.h"
#include <iostream>
#include <assimp/postprocess.h>
#include "../../Headers/Global.h"
#include "../ShaderManager/ShaderManager.h"

MeshManager* MeshManager::instance = nullptr;

MeshManager* MeshManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new MeshManager();
	}
	return instance;
}

MeshManager::MeshManager()
{
	Init();
}

MeshManager::~MeshManager()
{
	
}

void MeshManager::Init()
{
	program = shaderManager->GetShaderProgram();
	vpos_location = glGetAttribLocation(program, "vPosition");
	vcol_location = glGetAttribLocation(program, "vColour");
	vnorm_location = glGetAttribLocation(program, "vNormal");
	vuv_location = glGetAttribLocation(program, "vUV_x2");
}

bool MeshManager::LoadResource(Resource* resource)
{
	Mesh* mesh = static_cast<Mesh*>(resource);
	const aiScene* scene = import.ReadFile(mesh->filePath, aiProcess_Triangulate); //load mesh from file
	if (scene != nullptr)
	{
		if (scene->HasMeshes()) //ensures that what we loaded actually has meshes in it
		{
			//Need to rethink this based on the new system. for now will just assume the model only has 1 mesh
			//for (int i = 0; i < scene->mNumMeshes; ++i)
			//{
				for (int n = 0; n < scene->mMeshes[0]->mNumVertices; ++n) //load all vertices from the first mesh in the scene (will eventually look into supporting multiple meshes)
				{
					Vertex myVertex;
					myVertex.position.x = scene->mMeshes[0]->mVertices[n].x;
					myVertex.position.y = scene->mMeshes[0]->mVertices[n].y;
					myVertex.position.z = scene->mMeshes[0]->mVertices[n].z;
					myVertex.colour.r = 1;
					myVertex.colour.g = 1;
					myVertex.colour.b = 1;
					
					if (scene->mMeshes[0]->HasVertexColors(0)) //currently causes some issues when loading in ply files with vertex colours
					{
						if (scene->mMeshes[0]->mColors[n] != nullptr)
						{
							myVertex.colour.r = scene->mMeshes[0]->mColors[n]->r;
							myVertex.colour.g = scene->mMeshes[0]->mColors[n]->g;
							myVertex.colour.b = scene->mMeshes[0]->mColors[n]->b;
						}
					}
					else //if the vertex doesn't have colours it defaults to white
					{
						myVertex.colour.r = 1.0f;
						myVertex.colour.g = 1.0f;
						myVertex.colour.b = 1.0f;
					}
					
					if (scene->mMeshes[0]->HasNormals()) //if it has normals they're loaded into the vertex
					{
						myVertex.normalPosition.x = scene->mMeshes[0]->mNormals[n].x;
						myVertex.normalPosition.y = scene->mMeshes[0]->mNormals[n].y;
						myVertex.normalPosition.z = scene->mMeshes[0]->mNormals[n].z;
					}

					if (scene->mMeshes[0]->HasTextureCoords(0))
					{
						myVertex.uv.x = scene->mMeshes[0]->mTextureCoords[0][n].x;
						myVertex.uv.y = scene->mMeshes[0]->mTextureCoords[0][n].y;
					}
					else
					{
						myVertex.uv.x = 0;
						myVertex.uv.y = 0;
					}
					
					mesh->vertices.push_back(myVertex);
				}

				//adds all the triangle indices
				for (int n = 0; n < scene->mMeshes[0]->mNumFaces; ++n)
				{
					for (int j = 0; j < scene->mMeshes[0]->mFaces[n].mNumIndices; ++j)
					{
						unsigned int index = scene->mMeshes[0]->mFaces[n].mIndices[j];
						mesh->indices.push_back(index);
					}
				}
				resources[mesh->friendlyName] = mesh; //adds the mesh to the resource map
				loadMeshIntoGPU(mesh->friendlyName); //loads the mesh into the gpu
			//}
		}
	}
	else
	{
		std::cout << "Couldn't load file: " << mesh->filePath << ". Error: " << import.GetErrorString() << std::endl;
		return false;
	}
}


void MeshManager::loadMeshIntoGPU(std::string meshName)
{
	if (resources[meshName] != nullptr)
	{
		Mesh* mesh = static_cast<Mesh*>(resources[meshName]);
		glGenVertexArrays(1, &mesh->vao_id);
		glBindVertexArray(mesh->vao_id);

		//load the vertices into the gpu
		glGenBuffers(1, &mesh->vbo_id);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_id);
		glBufferData(GL_ARRAY_BUFFER,
			mesh->vertices.size() * sizeof(Vertex),	// sizeof(vertices), 
			&mesh->vertices[0],			// vertices, 
			GL_STATIC_DRAW);

		//load the indices into the gpu
		glGenBuffers(1, &mesh->ebo_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			mesh->indices.size() * sizeof(unsigned int),
			&mesh->indices[0],
			GL_STATIC_DRAW);

		

		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(vpos_location,	// "vPosition"
			3,				//  vec3 (xyz)
			GL_FLOAT,
			GL_FALSE,		// DON'T "normalize"
			sizeof(Vertex),
			(void*)0);

		glEnableVertexAttribArray(vcol_location);
		glVertexAttribPointer(vcol_location,		// cColour
			3,					// vec3 (rgb)
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(offsetof(Vertex, colour)));

		glEnableVertexAttribArray(vnorm_location);
		glVertexAttribPointer(vnorm_location,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(offsetof(Vertex, normalPosition)));

		glEnableVertexAttribArray(vuv_location);
		glVertexAttribPointer(vuv_location,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(offsetof(Vertex, uv)));

		glBindVertexArray(0);

		glDisableVertexAttribArray(vpos_location);
		glDisableVertexAttribArray(vcol_location);
		glDisableVertexAttribArray(vnorm_location);
		glDisableVertexAttribArray(vuv_location);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		std::cout << "Could not find mesh: " << meshName << " are you sure you loaded it?" << std::endl;
	}
}