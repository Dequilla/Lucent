#pragma once

#include "Core/Application.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ce { namespace graphics {

	class Camera
	{
	protected:
		glm::vec3 m_position;
		glm::quat m_orientation;

		glm::mat4 m_projection;

		float m_fov = 80.f;
		float m_near = 0.1f;
		float m_far = 100.f;
		float m_aspectRatio = 0.0f;

	public:

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;

		void setFOV(float fov);
		void setNearFar(float near, float far);
		void setAspectRatio(float ratio);
		void setProjection(float fov, float aspectRatio, float near, float far);

		glm::vec3 getPosition() const;
		glm::vec3 getForwardVector() const;
		glm::vec3 getLeftVector() const;

		// Resets the orientation of the camera
		void resetOriantation();

		// Rotate relative to its current oriantation
		void rotate(float angle, const glm::vec3 &axis);
		void rotate(float angle, float x, float y, float z);

		// Disregards oriantation and moves along world coordinates
		void move(const glm::vec3 &vec);
		void move(float x, float y, float z);

		// Translates relative to camera orientation
		void translate(const glm::vec3 &vec);
		void translate(float x, float y, float z);

		// Relative to current oriantation
		void pitch(float angle);
		void yaw(float angle);
		void roll(float angle);

		void setPosition(glm::vec3 pos);
		void setPosition(float x, float y, float z);
	};

} }