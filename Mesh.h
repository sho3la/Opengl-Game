#pragma once
#include <gl/glew.h>
#include <memory>
#include "Geometry.h"
#include "Material.h"
#include "Shader.h"
#include <vector>
namespace GXProject{
	class GameObject;
	class Mesh
	{
		friend class GameObject;
	public:
		Mesh(GeometryPtr g,MaterialPtr m);
		Mesh();
		~Mesh();

		GeometryPtr getGeometry();
		void setGeometry(GeometryPtr val);

		MaterialPtr getMaterial(){
			return material;
		}
		void setMaterial(MaterialPtr m){
			material = m;
		}

		void draw(int is_instancing = -1);

		void addSubMesh(std::shared_ptr<Mesh> val);
		void setShader(ShaderPtr val);

	private:
		std::vector<std::shared_ptr<Mesh> > _subMeshes;
		GeometryPtr geometry;
		MaterialPtr material;
		GLuint VAO;
		GLuint VBO;
		GLuint IBO;

	};
	typedef std::shared_ptr<Mesh> MeshPtr;
}