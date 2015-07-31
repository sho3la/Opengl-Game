#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"
namespace GXProject{
	class PointLight : public GameObject
	{
	public:
		glm::vec3 color;
		float intensity;
		
		PointLight(void);
		~PointLight(void);

	};
}

