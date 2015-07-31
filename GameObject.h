#pragma once
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <memory>
namespace GXProject{
	class GameObject{
	public:
		MeshPtr mesh;
		glm::vec3 position,rotation,scale;
		GameObject(MeshPtr m,glm::vec3 pos=glm::vec3(0),glm::vec3 rot=glm::vec3(0),glm::vec3 scl=glm::vec3(1)){
			mesh = m;
			position = pos;
			rotation = rot;
			scale = scl;
		}

		virtual ~GameObject(){
			mesh = nullptr;
		}

		glm::mat4 getModel(){
			glm::mat4 tm = glm::translate(glm::mat4(1),position);
			glm::mat4 rotx = glm::rotate(glm::mat4(1),rotation.x,glm::vec3(1,0,0));
			glm::mat4 roty = glm::rotate(glm::mat4(1),rotation.y,glm::vec3(0,1,0));
			glm::mat4 rotz = glm::rotate(glm::mat4(1),rotation.z,glm::vec3(0,0,1));
			glm::mat4 grot = rotx*roty*rotz;
			glm::mat4 sclMat = glm::scale(glm::mat4(1),scale);

			return tm * grot * sclMat;
		}

		virtual void update(double delta);
		virtual void draw(glm::mat4 vp,int is_Instancing = -1);
	};
	typedef std::shared_ptr<GameObject> GameObjectPtr;
}