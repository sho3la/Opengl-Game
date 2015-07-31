#include "Helper.h"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

using namespace GXProject;
using namespace std;

std::string Helper::getDirectory(std::string path){
	string dir = "";
	for(int i=path.size();i>=0;i--){
		if(path[i]=='\\' || path[i] == '/'){
			dir = path.substr(0,i+1);
			break;
		}
	}
	return dir;
}
MeshPtr Helper::loadMesh(std::string path){
	MeshPtr res = nullptr;


	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.c_str(),aiProcess_Triangulate|aiProcess_GenSmoothNormals|aiProcess_GenUVCoords|aiProcess_CalcTangentSpace);
	scene = importer.ApplyPostProcessing(aiProcess_CalcTangentSpace);
	if(!scene){
		cout<<"ERROR LOADING MESH: "<<path<<endl;
		return nullptr;
	}

	for(int i=0;i<scene->mNumMeshes;i++){
		GeometryPtr meshGEO = GeometryPtr(new Geometry());
		MaterialPtr meshMAT = MaterialPtr(new Material());

		const aiMesh* mesh = scene->mMeshes[i];
		const aiVector3D Zero3D(0.0f,0.0f,0.0f);
		const aiColor4D EmptyColor(0.0f,0.0f,0.0f,0.0f);

		for(unsigned int i=0;i<mesh->mNumVertices;i++){

		
			const aiVector3D* pPos = &(mesh->mVertices[i]);
			const aiVector3D* pNormal = mesh->HasNormals()? &(mesh->mNormals[i]):&Zero3D;
			const aiColor4D* pColor =mesh->HasVertexColors(0)? (mesh->mColors[i]):&EmptyColor;
			const aiVector3D* pTexCoord = mesh->HasTextureCoords(0)? &(mesh->mTextureCoords[0][i]):&Zero3D;
			const aiVector3D* pTangent = mesh->HasTangentsAndBitangents()? &(mesh->mTangents[i]):&Zero3D;

			cout<<pTangent->x<<" | "<<pTangent->y<<" | "<<pTangent->z<<endl;

			glm::vec3 pos = glm::vec3(pPos->x,pPos->y,pPos->z);
			glm::vec3 norm = glm::vec3(pNormal->x,pNormal->y,pNormal->z);
			glm::vec3 col = glm::vec3(pColor->r,pColor->g,pColor->b);
			glm::vec2 tex = glm::vec2(pTexCoord->x,pTexCoord->y);
			glm::vec3 tan = glm::vec3(pTangent->x,pTangent->y,pTangent->z);

			meshGEO->pushVertex(Vertex(pos,col,tex,norm,tan));
		}

		for(unsigned int i=0;i<mesh->mNumFaces;i++){
			const aiFace& face = mesh->mFaces[i];
			meshGEO->pushFace(face.mIndices[0],face.mIndices[1],face.mIndices[2]);
		}

		string Dir = Helper::getDirectory(path);
		aiString texPath;
		if(AI_SUCCESS == scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE,0,&texPath)){
			meshMAT->diffuse = TexturePtr(new Texture(Dir+texPath.data,0));
		}
		if(AI_SUCCESS == scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_HEIGHT,0,&texPath)){
			meshMAT->normal = TexturePtr(new Texture(Dir+texPath.data,0));
		}
		if(res == nullptr){
			res = MeshPtr(new Mesh(meshGEO,meshMAT));
		}else{
			res->addSubMesh(MeshPtr(new Mesh(meshGEO,meshMAT)));
		}
	}

	return res;
}