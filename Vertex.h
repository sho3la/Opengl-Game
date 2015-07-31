#pragma once
#include <glm/glm.hpp>
namespace GXProject{
	class Vertex{
	public:
		glm::vec3 position,color,normal;
		glm::vec2 texCoord;
		glm::vec3 tangent;
		Vertex(glm::vec3 pos = glm::vec3(),glm::vec3 co = glm::vec3(0,0,0),glm::vec2 tex = glm::vec2(),glm::vec3 norm = glm::vec3(0,0,0),glm::vec3 t = glm::vec3(0)){
			position = pos;
			normal = norm;
			color = co;
			texCoord = tex;
			tangent = t;
		}
	};
}