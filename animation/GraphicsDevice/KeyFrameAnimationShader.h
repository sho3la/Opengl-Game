#ifndef KeyFrameAnimationShader_h__
#define KeyFrameAnimationShader_h__


#include "ShaderProgram.h"

class KeyFrameAnimationShader :
	public ShaderProgram
{
	GLuint interpolationID;
public:
	 virtual void LoadProgram();
	 void SetInterpolation(float interpolation);
	KeyFrameAnimationShader(void);
	~KeyFrameAnimationShader(void);
};

#endif // KeyFrameAnimationShader_h__
