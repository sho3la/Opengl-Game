#include "EulerCamera.h"
using namespace GXProject;


EulerCamera::EulerCamera(void)
{
	_angle.x = 0;
	_angle.y = 0;
	this->Reset(0, 0, 0, 
		0, 0, -1, 
		0, 1, 0);

	setPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
}

EulerCamera::~EulerCamera(void)
{
}

glm::vec3 EulerCamera::getLookDirection()
{
	return -_direction;
}

void EulerCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void EulerCamera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	_position = eye;

	//still needs normalization
	_direction = center - _position;
	//i = j x k
	_right = glm::cross( _direction,up );
	//j = k x i
	_up = up;
	//normalize all
	_up = glm::normalize(_up);
	_right = glm::normalize(_right);
	_direction = glm::normalize(_direction);

	_view = glm::lookAt(_position,center,_up);
	//UpdateViewMatrix();
}

glm::mat4 EulerCamera::getViewMatrix()
{
	return _view;
}

void EulerCamera::updateViewMatrix()
{
	const float PI = 3.14f;
	_direction = glm::vec3(
		-cos(_angle.y)*sin(_angle.x), 
		sin(_angle.y), 
		-cos(_angle.y)*cos(_angle.x));


	_direction = glm::normalize(_direction);


	_right = glm::cross(_direction,glm::vec3(0,1,0));

	_up = glm::cross(_right,_direction);

	glm::vec3 center = _position + _direction;
	_view = glm::lookAt(_position,center,_up);

	//glm::mat4 view = glm::mat4(	mRight.x,		mRight.y,		mRight.z,		-glm::dot(mPosition,mRight),
	//	mUp.x,			mUp.y,			mUp.z,			-glm::dot(mPosition,mUp),
	//	mDirection.x,	mDirection.y,	mDirection.z,	-glm::dot(mPosition,mDirection),
	//	0,				0,				0,				1);
	//mViewMatrix = glm::transpose(view);
}

glm::mat4 EulerCamera::getProjectionMatrix()
{
	return _projection;
}

void EulerCamera::setPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	_projection = glm::perspective(FOV,aspectRatio,near,far);
}

void EulerCamera::Slide(float stepR, float stepU, float stepD)
{
	_position += stepR *_right;
	_position += stepU * _up;
	//next transition needs to be tested!!.
	_position += stepD * _direction;
}

void EulerCamera::Yaw(float angleDegrees)
{
	_angle.x +=angleDegrees;
}

void EulerCamera::Pitch(float angleDegrees)
{
	double PI = 3.14;
	if (_angle.y + angleDegrees < PI/2.0 && _angle.y + angleDegrees > - PI/2.0)
		_angle.y +=angleDegrees;
}

void EulerCamera::Roll(float angleDegrees)
{
	//no ROLL!!!
}

void EulerCamera::Walk(float dist)
{
	_position += dist * _direction;
}

void EulerCamera::Strafe(float dist)
{
	_position += dist *_right;
}

void EulerCamera::Fly(float dist)
{
	_position += dist * _up;
}
