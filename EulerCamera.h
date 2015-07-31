#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GXProject{
	class EulerCamera{
		glm::vec3 _position,_up,_right,_direction;
		glm::mat4 _view,_projection;

		glm::vec2 _angle;

		glm::vec3 getLookDirection();

	public:
		EulerCamera();
		~EulerCamera();

		void updateViewMatrix();
		void setPosition(glm::vec3 val){
			_position = val;
		}
		glm::mat4 getViewMatrix();
		void setPerspectiveProjection(float FOV, float ar, float near,float far);
		glm::mat4 getProjectionMatrix();

		void Reset(float eyeX,float eyeY, float eyeZ, float centerX,float centerY, float centerZ,float upX,float upY,float upZ);
		void Reset(const glm::vec3& eye,const glm::vec3&center,glm::vec3 &up);

		/// <summary>
		/// Rotates the axes (N, R) about the U-axis with the specified angle. This is equivalent to
		/// a left-turn.
		/// </summary>//y--->z--->x
		void Yaw(float angleDegrees);

		/// <summary>
		/// Rotates the axes (U, N) about the R-axis with the specified angle. This is equivalent
		/// to a look-up (up turn).
		/// </summary>//x--->y--->z
		void Pitch(float angleDegrees);

		/// <summary>
		/// Rotates the axes (R, U) about the N-axis with the specified angle.
		/// </summary>//z--->x--->y
		void Roll(float angleDegrees);

		/// <summary>
		/// Moves the eye point a distance dist forward == -dist * N
		/// Walk
		/// </summary>
		void Walk(float dist);

		/// <summary>
		/// Moves the eye point a distance dist to the right == +dist * R
		/// Strafe
		/// </summary>
		void Strafe(float dist);

		/// <summary>
		/// Moves the eye point a distance dist upward == +dist * U
		/// Fly
		/// </summary>
		void Fly(float dist);

		/// <summary>
		/// Moves the eye position a distance stepR along the vector R,
		/// a distance stepU along the vector U, and a distance stepD
		/// along the vector N.
		/// </summary>
		void Slide(float stepR, float stepU, float stepD);

		glm::vec3 getPosition(){
			return _position;
		}
	};
}