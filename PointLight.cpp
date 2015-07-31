#include "PointLight.h"
using namespace GXProject;
using namespace glm;

PointLight::PointLight(void):GameObject(NULL)
{
	color = vec3(1);
	intensity = 1;
}


PointLight::~PointLight(void)
{
}
