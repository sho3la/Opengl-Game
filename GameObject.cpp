#include "GameObject.h"
#include "Material.h"
#include "Shader.h"
using namespace GXProject;

void GameObject::update(double delta){

}
void GameObject::draw(glm::mat4 vp,int is_Instancing){
	//do the shader binding stuff outside so we can access the lights
	//mesh->getMaterial()->shader->bind();
	mesh->getMaterial()->shader->setUniform("MVP",vp*getModel());
	mesh->getMaterial()->shader->setUniform("ModelMatrix",getModel());
	mesh->draw(is_Instancing);
}