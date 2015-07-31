#pragma once
#pragma once
#include "Cube.h"
#include "TextureCube.h"
#include <memory>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;
namespace GXProject{
	class Skybox{
		bool inRange(float val){
			if(val <= size && val >= -size)
				return true;
			return false;
		}
	public:
		Cube _cube;
		TextureCube* _textureCube;
		int size;
		int offset;
		Skybox(){
			size = 20;
			offset = 2.5;
			_cube._cube->scale = vec3(size+offset,size+offset,size+offset);
			vector<string> files;
			files.push_back("res\\ely_cloudtop\\cloudtop_rt.jpg");
			files.push_back("res\\ely_cloudtop\\cloudtop_lf.jpg");
			files.push_back("res\\ely_cloudtop\\cloudtop_up.jpg");
			files.push_back("res\\ely_cloudtop\\cloudtop_dn.jpg");
			files.push_back("res\\ely_cloudtop\\cloudtop_bk.jpg");
			files.push_back("res\\ely_cloudtop\\cloudtop_ft.jpg");
			_textureCube = new TextureCube(files,0);
		}
		~Skybox(){
			delete _textureCube;
		}

		void setShader(ShaderPtr val){
			_cube._cube->mesh->setShader(val);
		}

		void draw(mat4 vp){
			_cube._cube->mesh->getMaterial()->shader->bind();
			_textureCube->bind();
			_cube._cube->draw(vp);
			glBindTexture(GL_TEXTURE_CUBE_MAP,0);
		}

		bool within(vec3 pos){
			if(inRange(pos.x) && inRange(pos.y) && inRange(pos.z))
				return true;
			return false;
		}

		vec3 adjust(vec3 pos){
			if(!inRange(pos.x))
				if(pos.x<0)
					pos.x = -size;
				else
					pos.x = size;
			if(!inRange(pos.y))
				if(pos.y<0)
					pos.y = -size;
				else
					pos.y = size;
			if(!inRange(pos.z))
				if(pos.z<0)
					pos.z = -size;
				else
					pos.z = size;
			return pos;
		}

	};
}