/**
* \file Camera.h
* \brief A simple freemoving camera
*/
#pragma once

#include "Core/Application.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ce { namespace graphics {

	/**
	* \breif A free camera that uses quaternion
	*/
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
		/**
		* \brief Constructor
		* @param position The position in the scene to spawn the camera at
		*/
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

		/**
		* \brief Retrieve the view matrix for this camera
		* @return glm::mat4 view matrix
		*/
		glm::mat4 getViewMatrix() const;

		/**
		* \brief Retrieve the projection matrix for this camera
		* @return glm::mat4 projection matrix
		*/
		glm::mat4 getProjectionMatrix() const;

		/**
		* \brief Set the fov of this camera
		* @param fov Fov in degrees
		*/
		void setFOV(float fov);

		/**
		* \brief Set the clip space for this camera
		* @param n Clip near
		* @param f Clip far
		*/
		void setNearFar(float n, float f);

		/**
		* \brief Set the aspect ratio of this camera
		* @param ratio example: 1280/720 (16:9)
		*/
		void setAspectRatio(float ratio);

		/**
		* \brief Set the projection matrix for this camera
		* @param fov Fov in degrees
		* @param ration example: 1280/720 (16:9)
		* @param n Clip near
		* @param f Clip far
		*/
		void setProjection(float fov, float aspectRatio, float n, float f);

		/**
		* \brief Get the camera position
		* @return glm::vec3 A 3 component vector of a 3D position
		*/
		glm::vec3 getPosition() const;

		/**
		* \brief Get the camera forward vector
		* @return glm::vec3 A 3 component vector of the direction the camera is pointing
		*/
		glm::vec3 getForwardVector() const;

		/**
		* \brief Get the camera left vector
		* @return glm::vec3 A 3 component vector of the direction the cameras left side is pointing towards
		*/
		glm::vec3 getLeftVector() const;

		/**
		* \brief Resets the oriantation of the camera
		*/
		void resetOriantation();
		
		/**
		* \brief Rotate relative to its current oriantation
		* @param angle An angle in degrees
		* @param axis A 3 component vector of which axis to rotate on
		*/
		void rotate(float angle, const glm::vec3 &axis);

		/**
		* \brief Rotate relative to its current oriantation
		* @param angle An angle in degrees
		* @param x,y,z Which axis to rotate on
		*/
		void rotate(float angle, float x, float y, float z);

		
		/**
		* \brief Move relative to position only
		* @param vec 3 component vector representing how much to move on each axis
		*/
		void move(const glm::vec3 &vec);

		/**
		* \brief Move relative to position only
		* @param x,y,z floats representing how much to move on each axis
		*/
		void move(float x, float y, float z);

		/**
		* \brief Translate relative to position and orientation
		* @param vec 3 component vector representing how much to move on each axis
		*/
		void translate(const glm::vec3 &vec);

		/**
		* \brief Translate relative to position and orientation
		* @param x,y,z floats representing how much to move on each axis
		*/
		void translate(float x, float y, float z);

		/**
		* \brief Pitch relative to orientation
		* @param angle Angle in degrees
		*/
		void pitch(float angle);

		/**
		* \brief Yaw relative to orientation
		* @param angle Angle in degrees
		*/
		void yaw(float angle);

		/**
		* \brief Roll relative to orientation
		* @param angle Angle in degrees
		*/
		void roll(float angle);

		/**
		* \brief Set position in the scene
		* @param pos 3 component vector representing a 3D coordinate
		*/
		void setPosition(glm::vec3 pos);

		/**
		* \brief Set position in the scene
		* @param x,y,z 3 components representing a 3D coordinate
		*/
		void setPosition(float x, float y, float z);
	};

} }