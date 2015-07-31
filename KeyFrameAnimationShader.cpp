#include "KeyFrameAnimationShader.h"


KeyFrameAnimationShader::KeyFrameAnimationShader(void)
{
}


KeyFrameAnimationShader::~KeyFrameAnimationShader(void)
{
}

void KeyFrameAnimationShader::LoadProgram()
{
	programID = LoadShaders( "KeyframeAnimation.vertexshader", "TextureLighting.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");

	vpMatrixID = glGetUniformLocation(programID, "VP");

	interpolationID = glGetUniformLocation(programID, "Interpolation");
}

void KeyFrameAnimationShader::SetInterpolation(float interpolation)
{
	glUniform1f(interpolationID,interpolation);
}
