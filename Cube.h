#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "GameObject.h"
namespace GXProject{
	class Cube{
	public:
		GameObjectPtr _cube;
		Cube();
		~Cube();

		void walk(glm::vec3,float);
	};
}